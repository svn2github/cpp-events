#include "ConnectionList.hpp"

ConnectionList::ConnectionList()
	: lock_(ThreadDataRef::current())
{
}

ConnectionList::~ConnectionList()
{
	disconnectAll();
}

void ConnectionList::connect(ConnectionList * peer, AbstractDelegate const & deleg, ExtraDelegateData * data)
{
	OrderedThreadDataLocker locker(lock_, peer->lock_);
	size_t const thisIndex = this->connections_.size();
	size_t const peerIndex = peer->connections_.size();
	{
		connections_.resize(thisIndex + 1);
		ConnectionData * d = &connections_[thisIndex];
		d->ref_.retain();
		d->peerLock_ = peer->lock_;
		d->peer_ = peer;
		d->indexInPeer_ = peerIndex;
		d->extraData_ = data;
		if(data) data->retain();
		d->delegate_ = deleg;
	}
	{
		peer->connections_.resize(peerIndex + 1);
		ConnectionData * d = &peer->connections_[peerIndex];
		d->ref_.retain();
		d->peerLock_ = this->lock_;
		d->peer_ = this;
		d->indexInPeer_ = thisIndex;
		d->extraData_ = data;
		if(data) data->retain();
		d->delegate_ = deleg;
	}
}

#define mutable_iterate(it, container) \
	ConnectionsVector::iterator it = (container).begin(); it != (container).end(); ++it

#define const_iterate(it, container) \
	ConnectionsVector::const_iterator it = (container).begin(); it != (container).end(); ++it

class ConnectionList::NullComparer
{
public:
	bool operator()(ConnectionData const & conn) const { (void)conn; return true; }
};

class ConnectionList::DelegateComparer
{
public:
	DelegateComparer(AbstractDelegate const & deleg) : deleg_(deleg) {}
	bool operator()(ConnectionData const & conn) const { return conn.targetDelegate() == deleg_; }
private:
	AbstractDelegate const & deleg_;
};

class ConnectionList::PeerComparer
{
public:
	PeerComparer(ConnectionList * peer) : peer_(peer) {}
	bool operator()(ConnectionData const & conn) const { return conn.peer_ == peer_; }
private:
	ConnectionList * const peer_;
};

class ConnectionList::FullComparer
{
public:
	FullComparer(ConnectionList * peer, AbstractDelegate const & deleg) : e_(peer), d_(deleg) {}
	bool operator()(ConnectionData const & conn) const { return e_(conn) && d_(conn); }
private:
	PeerComparer e_;
	DelegateComparer d_;
};

size_t ConnectionList::connectionCount() const
{
	ThreadDataLocker lock(lock_);
	return connections_.size();
}

template<class Comparer> inline size_t ConnectionList::getConnectionCount(Comparer const & comp) const
{
	ThreadDataLocker lock(lock_);
	size_t retVal = 0;
	for(const_iterate(it, connections_))
	{
		ConnectionData const & conn = *it;
		if(comp(conn)) ++retVal;
	}
	return retVal;
}

size_t ConnectionList::connectionCount(AbstractDelegate const & deleg) const
{
	DelegateComparer comp(deleg);
	return getConnectionCount(comp);
}

size_t ConnectionList::connectionCount(ConnectionList * peer) const
{
	PeerComparer comp(peer);
	return getConnectionCount(comp);
}

size_t ConnectionList::connectionCount(ConnectionList * peer, AbstractDelegate const & deleg) const
{
	FullComparer comp(peer, deleg);
	return getConnectionCount(comp);
}

bool ConnectionList::hasConnections() const
{
	ThreadDataLocker lock(lock_);
	return !connections_.empty();
}

template<class Comparer> inline bool ConnectionList::getHasConnections(Comparer const & comp) const
{
	ThreadDataLocker lock(lock_);
	for(const_iterate(it, connections_))
	{
		ConnectionData const & conn = *it;
		if(comp(conn)) return true;
	}
	return false;
}

bool ConnectionList::hasConnections(AbstractDelegate const & deleg) const
{
	DelegateComparer comp(deleg);
	return getHasConnections(comp);
}

bool ConnectionList::hasConnections(ConnectionList * peer) const
{
	PeerComparer comp(peer);
	return getHasConnections(comp);
}

bool ConnectionList::hasConnections(ConnectionList * peer, AbstractDelegate const & deleg) const
{
	FullComparer comp(peer, deleg);
	return getHasConnections(comp);
}

template<class Comparer> inline size_t ConnectionList::doDisconnectAll(Comparer const & comp)
{
	std::vector<size_t> needRelock;
	size_t retVal = 0;
	{
		ThreadDataLocker lock(lock_);
		for(size_t i=0; i<connections_.size(); )
		{
			ConnectionData const & conn = connections_[i];
			if(!comp(conn))
			{
				++i;
				continue;
			}
			++retVal;
			bool done = tryDisconnectWithLock(i);
			if(!done)
			{
				retainConn(i);
				needRelock.push_back(i);
				++i;
			}
		}
	}
	for(std::vector<size_t>::const_iterator it = needRelock.begin(); it != needRelock.end(); ++it)
	{
		size_t index = *it;
		disconnectAt(index);
		releaseConn(index);
	}
	return retVal;
}

size_t ConnectionList::disconnectAll()
{
	NullComparer comp;
	return doDisconnectAll(comp);
}

size_t ConnectionList::disconnectAll(AbstractDelegate const & deleg)
{
	DelegateComparer comp(deleg);
	return doDisconnectAll(comp);
}

size_t ConnectionList::disconnectAll(ConnectionList * peer, AbstractDelegate const & deleg)
{
	FullComparer comp(peer, deleg);
	return doDisconnectAll(comp);
}

size_t ConnectionList::disconnectAll(ConnectionList * peer)
{
	PeerComparer comp(peer);
	return doDisconnectAll(comp);
}

bool ConnectionList::disconnectOne(ConnectionList * peer, AbstractDelegate const & deleg)
{
	FullComparer comp(peer, deleg);
	size_t needRelock = ConnectionData::npos;
	{
		ThreadDataLocker lock(lock_);
		for(size_t i=0; i<connections_.size(); )
		{
			ConnectionData & conn = connections_[i];
			if(!comp(conn))
			{
				++i;
				continue;
			}
			bool done = tryDisconnectWithLock(i);
			if(done) return true;
			needRelock = i;
			retainConn(i);
			break;
		}
	}

	if(needRelock == ConnectionData::npos) return false;
	disconnectAt(needRelock);
	releaseConn(needRelock);
	return true;
}

void ConnectionList::disconnectAt(size_t index)
{
	ConnectionData * thisConn = &connections_[index];
	OrderedThreadDataLocker locker(lock_, thisConn->peerLock_);
	doDisconnect(index);
}

bool ConnectionList::tryDisconnectWithLock(size_t index)
{
	ConnectionData * thisConn = &connections_[index];
	if(thisConn->peerLock_.isBefore(lock_)) return false;
	ThreadDataLocker locker(thisConn->peerLock_);
	doDisconnect(index);
	return true;
}

void ConnectionList::doDisconnect(size_t index)
{
	ConnectionData * thisConn = &connections_[index];
	if(thisConn->peer_)
	{
		ConnectionData * peerConn = thisConn->peerData();
		peerConn->clear();
		thisConn->peer_->releaseConn(thisConn->indexInPeer_);
		thisConn->clear();
	}
	releaseConn(index);
}

void ConnectionList::retainConn(size_t index)
{
	connections_[index].ref_.retain();
}

void ConnectionList::releaseConn(size_t index)
{
	ConnectionData * conn = &connections_[index];
	bool const isDead = conn->ref_.release();
	
	if(isDead)
	{
		if(index != connections_.size() - 1)
		{
			*conn = connections_.back();
			if(conn->peer_)
			{
				conn->peerData()->indexInPeer_ = index;
			}
		}
		connections_.pop_back();
	}
}