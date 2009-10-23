#include "AbstractEvent.hpp"

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
{
}

ConnectionList::~ConnectionList()
{
	disconnectAll();
}

void ConnectionList::connect(ConnectionList * tracker, AbstractConnection * conn)
{
	conn->outerLock_ = this->lock_;
	conn->innerLock_ = tracker->lock_;
	conn->outerLock_.order(conn->innerLock_);

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
		conn->targetList_ = tracker;
		conn->targetIndex_ = tracker->connections_.size();
		tracker->connections_.push_back(conn);
		conn->retain();
	}
}

#define mutable_iterate(it, container) \
	ConnectionsVector::iterator it = (container).begin(); it != (container).end(); ++it

#define const_iterate(it, container) \
	ConnectionsVector::const_iterator it = (container).begin(); it != (container).end(); ++it

class NullComparer
{
public:
	bool operator()(AbstractConnection const * conn) const { (void)conn; return true; }
};

class DelegateComparer
{
public:
	DelegateComparer(AbstractDelegate const & deleg) : deleg_(deleg) {}
	bool operator()(AbstractConnection const * conn) const { return conn->recieverDelegate() == deleg_; }
private:
	AbstractDelegate const & deleg_;
};

class EventComparer
{
public:
	EventComparer(AbstractEventRef const & ev) : ev_(ev) {}
	bool operator()(AbstractConnection const * conn) const { return conn->senderEventRef() == ev_; }
private:
	AbstractEventRef const & ev_;
};

class FullComparer
{
public:
	FullComparer(AbstractEventRef const & ev, AbstractDelegate const & deleg) : e_(ev), d_(deleg) {}
	bool operator()(AbstractConnection const * conn) const { return e_(conn) && d_(conn); }
private:
	EventComparer e_;
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
		AbstractConnection * conn = *it;
		if(comp(conn)) ++retVal;
	}
	return retVal;
}

size_t ConnectionList::connectionCount(AbstractDelegate const & deleg) const
{
	DelegateComparer comp(deleg);
	return getConnectionCount(comp);
}

size_t ConnectionList::connectionCount(AbstractEventRef const & deleg) const
{
	EventComparer comp(deleg);
	return getConnectionCount(comp);
}

size_t ConnectionList::connectionCount(AbstractEventRef const & ev, AbstractDelegate const & deleg) const
{
	FullComparer comp(ev, deleg);
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
		AbstractConnection * conn = *it;
		if(comp(conn)) return true;
	}
	return false;
}

bool ConnectionList::hasConnections(AbstractDelegate const & deleg) const
{
	DelegateComparer comp(deleg);
	return getHasConnections(comp);
}

bool ConnectionList::hasConnections(AbstractEventRef const & deleg) const
{
	EventComparer comp(deleg);
	return getHasConnections(comp);
}

bool ConnectionList::hasConnections(AbstractEventRef const & ev, AbstractDelegate const & deleg) const
{
	FullComparer comp(ev, deleg);
	return getHasConnections(comp);
}

template<class Comparer> inline size_t ConnectionList::doDisconnect(Comparer const & comp)
{
	ConnectionsVector needRelock;
	size_t retVal = 0;
	{
		ThreadDataLocker lock(lock_);
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
	return doDisconnect(comp);
}

size_t ConnectionList::disconnectAll(AbstractDelegate const & deleg)
{
	DelegateComparer comp(deleg);
	return doDisconnect(comp);
}

size_t ConnectionList::disconnectAll(AbstractEventRef const & ev, AbstractDelegate const & deleg)
{
	FullComparer comp(ev, deleg);
	return doDisconnect(comp);
}

size_t ConnectionList::disconnectAll(AbstractEventRef const & ev)
{
	EventComparer comp(ev);
	return doDisconnect(comp);
}

bool ConnectionList::disconnectOne(AbstractEventRef const & ev, AbstractDelegate const & deleg)
{
	FullComparer comp(ev, deleg);
	AbstractConnection * needRelock = 0;
	{
		ThreadDataLocker lock(lock_);
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
