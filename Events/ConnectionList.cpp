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
		sourceIndex_ = npos; sourceList_ = 0;
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

#define CHECK_FOR_CONNECTIONS(Test) \
	for(const_iterate(it, connections_)) \
	{ if(Test) return true; } \
	return false;

bool ConnectionList::hasConnectionsWithSender(AbstractObjectRef sender) const
{
	CHECK_FOR_CONNECTIONS((*it)->senderObject() == sender);
}

bool ConnectionList::hasConnectionsWithReciever(AbstractObjectRef reciever) const
{
	CHECK_FOR_CONNECTIONS((*it)->recieverObject() == reciever);
}

bool ConnectionList::hasConnectionsWithEvent(AbstractEventRef const & ev) const
{
	CHECK_FOR_CONNECTIONS((*it)->senderEventRef() == ev);
}

bool ConnectionList::hasConnectionsWithDelegate(AbstractDelegate const & deleg) const
{
	CHECK_FOR_CONNECTIONS((*it)->recieverDelegate() == deleg);
}

#undef CHECK_FOR_CONNECTIONS

#define DISCONNECT_CONNECTIONS(Test) \
	ConnectionsVector needRelock; \
	size_t retVal = 0; \
	{ \
		ThreadDataLocker lock(lock_); \
		for(size_t i=0; i<connections_.size(); ) \
		{ \
			AbstractConnection * conn = connections_.at(i); \
			if(!(Test)) \
			{ \
				++i; \
				continue; \
			} \
			++retVal; \
			bool done = conn->tryDisconnectWithLock(lock_); \
			if(!done) \
			{ \
				conn->retain(); \
				needRelock.push_back(conn); \
				++i; \
			} \
		} \
	} \
	for(const_iterate(it, needRelock)) \
	{ \
		AbstractConnection * conn = *it; \
		conn->disconnect(); \
		conn->release(); \
	} \
	return retVal;


size_t ConnectionList::disconnectAll()
{
	DISCONNECT_CONNECTIONS(true);
}

size_t ConnectionList::disconnectFromSender(AbstractObjectRef sender)
{
	DISCONNECT_CONNECTIONS(conn->senderObject() == sender);
}

size_t ConnectionList::disconnectFromReciver(AbstractObjectRef reciever)
{
	DISCONNECT_CONNECTIONS(conn->recieverObject() == reciever);
}

size_t ConnectionList::disconnectFromEvent(AbstractEventRef const & ev)
{
	DISCONNECT_CONNECTIONS(conn->senderEventRef() == ev);
}

size_t ConnectionList::disconnectFromDelegate(AbstractDelegate const & deleg)
{
	DISCONNECT_CONNECTIONS(conn->recieverDelegate() == deleg);
}

size_t ConnectionList::disconnectObjects(AbstractObjectRef sender, AbstractObjectRef reciever)
{
	DISCONNECT_CONNECTIONS((conn->senderObject() == sender) && (conn->recieverObject() == reciever));
}

#undef DISCONNECT_CONNECTIONS

bool ConnectionList::disconnectConnection(AbstractEventRef const & ev, AbstractDelegate const & deleg)
{
	AbstractConnection * needRelock = 0;
	{
		ThreadDataLocker lock(lock_);
		for(size_t i=0; i<connections_.size(); )
		{
			AbstractConnection * conn = connections_.at(i);
			if(!(conn->senderEventRef() == ev && conn->recieverDelegate() == deleg)) \
			{
				++i;
				continue;
			}
			bool done = conn->tryDisconnectWithLock(lock_); \
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

