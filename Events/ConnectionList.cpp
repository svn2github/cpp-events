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

#define A_COND conn->senderEventRef() == ev
#define A_ARG AbstractEventRef const & ev
#define B_COND conn->recieverDelegate() == deleg
#define B_ARG AbstractDelegate const & deleg

#define MAKE_OVERLOADS(GENERATOR) \
GENERATOR((A_ARG), (A_COND)) \
GENERATOR((B_ARG), (B_COND)) \
GENERATOR((A_ARG, B_ARG), ((A_COND) && (B_COND))) \


size_t ConnectionList::connectionCount() const
{
	ThreadDataLocker lock(lock_);
	return connections_.size();
}

#define CONNECTION_COUNT_GENERATOR(Sign, Test) \
size_t ConnectionList::connectionCount Sign const \
{ \
	ThreadDataLocker lock(lock_); \
	size_t retVal = 0; \
	for(const_iterate(it, connections_)) \
	{ \
		AbstractConnection * conn = *it; \
		if(Test) ++retVal; \
	} \
	return retVal; \
} \

MAKE_OVERLOADS(CONNECTION_COUNT_GENERATOR)

#undef CONNECTION_COUNT_GENERATOR

bool ConnectionList::hasConnections() const
{
	ThreadDataLocker lock(lock_);
	return !connections_.empty();
}

#define HAS_CONNECTIONS_GENERATOR(Sign, Test) \
bool ConnectionList::hasConnections Sign const \
{ \
	ThreadDataLocker lock(lock_); \
	for(const_iterate(it, connections_)) \
	{ \
		AbstractConnection * conn = *it; \
		if(Test) return true; \
	} \
	return false; \
} \

MAKE_OVERLOADS(HAS_CONNECTIONS_GENERATOR)

#undef HAS_CONNECTIONS_GENERATOR

#define DISCONNECT_BODY_GENERATOR(Test) \
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

#define DISCONNECT_GENERATOR(Sign, Test) \
size_t ConnectionList::disconnectAll Sign \
{ \
	DISCONNECT_BODY_GENERATOR(Test) \
} \

size_t ConnectionList::disconnectAll()
{
	DISCONNECT_BODY_GENERATOR(true);
}

MAKE_OVERLOADS(DISCONNECT_GENERATOR)

#undef DISCONNECT_GENERATOR
#undef DISCONNECT_BODY_GENERATOR

bool ConnectionList::disconnectOne(AbstractEventRef const & ev, AbstractDelegate const & deleg)
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

#undef MAKE_OVERLOADS

#undef A_COND
#undef B_COND
#undef C_COND

#undef A_ARG
#undef B_ARG
#undef C_ARG

#undef X_COND
#undef Y_COND
#undef Z_COND

#undef X_ARG
#undef Y_ARG
#undef Z_ARG

