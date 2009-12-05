#include "ConnectionList.hpp"

void AbstractConnection::disconnect()
{
	ThreadDataLocker lock1(outerLock_);
	ThreadDataLocker lock2(innerLock_);
	doDisconnect();
}

bool AbstractConnection::tryDisconnectWithLock(ThreadDataRef const & lock)
{
	if(lock != outerLock_) return false;
	ThreadDataLocker lock2(innerLock_);
	doDisconnect();
	return true;
}

void AbstractConnection::doDisconnect()
{
	if(!sourceList_ && !targetList_) return;
	assert(sourceList_ && targetList_);

	{
		AbstractConnection * & xs = sourceList_->connections_[sourceIndex_];
		assert(xs == this);
		xs = sourceList_->connections_.back();
		xs->sourceIndex_ = sourceIndex_;
		sourceList_->connections_.pop_back();
		sourceIndex_ = npos; sourceList_ = 0;
		release();
	}
	{
		AbstractConnection * & xt = targetList_->connections_[targetIndex_];
		assert(xt == this);
		xt = targetList_->connections_.back();
		xt->targetIndex_ = targetIndex_;
		targetList_->connections_.pop_back();
		targetIndex_ = npos; targetList_ = 0;
		release();
	}
}

ConnectionList::ConnectionList()
	: lock_(ThreadDataRef::current())
	, connections_()
	, stolenConnections_()
{
}

ConnectionList::~ConnectionList()
{
	disconnectAll();
}

void ConnectionList::connect(ConnectionList * peer, AbstractConnection * conn)
{
	conn->outerLock_ = this->lock_;
	conn->innerLock_ = peer->lock_;
	conn->outerLock_.makeBefore(conn->innerLock_);

	ThreadDataLocker lock1(conn->outerLock_);
	ThreadDataLocker lock2(conn->innerLock_);

	{
		assert(!conn->sourceList_ && conn->sourceIndex_ == AbstractConnection::npos);
		conn->sourceList_ = this;
		conn->sourceIndex_ = connections_.size();
		connections_.push_back(conn);
		conn->retain();
	}
	{
		assert(!conn->targetList_ && conn->targetIndex_ == AbstractConnection::npos);
		conn->targetList_ = peer;
		conn->targetIndex_ = peer->connections_.size();
		peer->connections_.push_back(conn);
		conn->retain();
	}
}

#define mutable_iterate(it, container) \
	ConnectionsVector::iterator it = (container).begin(); it != (container).end(); ++it

#define const_iterate(it, container) \
	ConnectionsVector::const_iterator it = (container).begin(); it != (container).end(); ++it

class ConnectionList::NullComparer
{
public:
	bool operator()(AbstractConnection const * conn) const { (void)conn; return true; }
};

class ConnectionList::DelegateComparer
{
public:
	DelegateComparer(AbstractDelegate const & deleg) : deleg_(deleg) {}
	bool operator()(AbstractConnection const * conn) const { return conn->recieverDelegate() == deleg_; }
private:
	AbstractDelegate const & deleg_;
};

class ConnectionList::PeerComparer
{
public:
	PeerComparer(ConnectionList * peer) : peer_(peer) {}
	bool operator()(AbstractConnection const * conn) const { return conn->hasPeer(peer_); }
private:
	ConnectionList * const peer_;
};

class ConnectionList::FullComparer
{
public:
	FullComparer(ConnectionList * peer, AbstractDelegate const & deleg) : e_(peer), d_(deleg) {}
	bool operator()(AbstractConnection const * conn) const { return e_(conn) && d_(conn); }
private:
	PeerComparer e_;
	DelegateComparer d_;
};

size_t ConnectionList::connectionCount() const
{
	ThreadDataLocker lock(lock_);
	return constRef().size();
}

template<class Comparer> inline size_t ConnectionList::getConnectionCount(Comparer const & comp) const
{
	ThreadDataLocker lock(lock_);
	ConnectionsVector const & conns = constRef();
	size_t retVal = 0;
	for(const_iterate(it, conns))
	{
		AbstractConnection const * conn = *it;
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
	return !constRef().empty();
}

template<class Comparer> inline bool ConnectionList::getHasConnections(Comparer const & comp) const
{
	ThreadDataLocker lock(lock_);
	ConnectionsVector const & conns = constRef();	
	for(const_iterate(it, conns))
	{
		AbstractConnection const * conn = *it;
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
	ConnectionsVector needRelock;
	size_t retVal = 0;
	{
		ThreadDataLocker lock(lock_);
		detach();
		for(size_t i=0; i<connections_.size(); )
		{
			AbstractConnection * conn = connections_.at(i);
			if(!comp(conn))
			{
				++i;
				continue;
			}
			++retVal;
			bool done = conn->tryDisconnectWithLock(lock_);
			if(!done)
			{
				conn->retain();
				needRelock.push_back(conn);
				++i;
			}
		}
	}
	for(const_iterate(it, needRelock))
	{
		AbstractConnection * conn = *it;
		conn->disconnect();
		conn->release();
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

template<class Comparer> inline bool ConnectionList::doDisconnectOne(Comparer const & comp)
{
	AbstractConnection * needRelock = 0;
	{
		ThreadDataLocker lock(lock_);
		detach();
		for(size_t i=0; i<connections_.size(); )
		{
			AbstractConnection * conn = connections_.at(i);
			if(!comp(conn))
			{
				++i;
				continue;
			}
			bool done = conn->tryDisconnectWithLock(lock_);
			if(done) return true;
			needRelock = conn;
			conn->retain();
			break;
		}
	}

	if(!needRelock) return false;

	needRelock->disconnect();
	needRelock->release();
	return true;
}

bool ConnectionList::disconnectOne(AbstractDelegate const & deleg)
{
	DelegateComparer comp(deleg);
	return doDisconnectOne(comp);
}

bool ConnectionList::disconnectOne(ConnectionList * peer)
{
	PeerComparer comp(peer);
	return doDisconnectOne(comp);
}

bool ConnectionList::disconnectOne(ConnectionList * peer, AbstractDelegate const & deleg)
{
	FullComparer comp(peer, deleg);
	return doDisconnectOne(comp);
}
ConnectionList::ConnectionsVector const & ConnectionList::constRef() const
{
	if(stolenConnections_)
	{
		assert(connections_.empty());
		return *stolenConnections_;
	}
	return connections_;
}

void ConnectionList::detach()
{
	if(stolenConnections_)
	{
		assert(connections_.empty());
		ConnectionList * _this = const_cast<ConnectionList*>(this);
		_this->connections_ = *(_this->stolenConnections_);
		_this->stolenConnections_ = 0;
	}
}
