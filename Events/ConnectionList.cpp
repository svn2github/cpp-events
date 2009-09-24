#include "AbstractEvent.hpp"

#define mutable_iterate(it, container) \
	ConnectionsVector::iterator it = (container).begin(); it != (container).end(); ++it

#define const_iterate(it, container) \
	ConnectionsVector::const_iterator it = (container).begin(); it != (container).end(); ++it

AbstractConnection * ConnectionList::addConnection(AbstractConnection * conn)
{
	conn->addDisconnectListener(this, &ConnectionList::connectionBroken);
	connections_.push_back(conn);
	return conn;
}

bool ConnectionList::removeConnection(AbstractConnection * conn)
{
	conn->removeDisconnectListener(this, &ConnectionList::connectionBroken);
	return doRemoveConnection(conn);
}

bool ConnectionList::doRemoveConnection(AbstractConnection const * conn)
{
	for(mutable_iterate(it, connections_))
	{
		if(conn == *it)
		{
			*it = connections_.back();
			connections_.pop_back();
			return true;
		}
	}
	return false;
}

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

void ConnectionList::disconnectAll()
{
	ConnectionsVector tmp;
	tmp.swap(connections_);

	for(const_iterate(it, tmp))
	{
		(*it)->disconnect();
	}
}

#define DISCONNECT_CONNECTIONS(Test) \
	ConnectionsVector before, after; \
	before.swap(connections_); \
	after.reserve(before.capacity()); \
	bool retVal = false; \
	for(const_iterate(it, before)) \
	{ \
		AbstractConnection * conn = *it; \
		if(Test) \
		{ \
			conn->disconnect(); \
			retVal = true; \
		} \
		else \
		{ \
			after.push_back(conn); \
		} \
	} \
	connections_.swap(after); \
	return retVal;

bool ConnectionList::disconnectFromSender(AbstractObjectRef sender)
{
	DISCONNECT_CONNECTIONS(conn->senderObject() == sender);
}

bool ConnectionList::disconnectFromReciver(AbstractObjectRef reciever)
{
	DISCONNECT_CONNECTIONS(conn->recieverObject() == reciever);
}

bool ConnectionList::disconnectFromEvent(AbstractEventRef const & ev)
{
	DISCONNECT_CONNECTIONS(conn->senderEventRef() == ev);
}

bool ConnectionList::disconnectFromDelegate(AbstractDelegate const & deleg)
{
	DISCONNECT_CONNECTIONS(conn->recieverDelegate() == deleg);
}

bool ConnectionList::disconnectObjects(AbstractObjectRef sender, AbstractObjectRef reciever)
{
	DISCONNECT_CONNECTIONS((conn->senderObject() == sender) && (conn->recieverObject() == reciever));
}

#undef DISCONNECT_CONNECTIONS

bool ConnectionList::disconnectConnection(AbstractEventRef const & ev, AbstractDelegate const & deleg)
{
	for(const_iterate(it, connections_))
	{
		AbstractConnection * conn = *it;
		if(conn->senderEventRef() == ev && conn->recieverDelegate() == deleg)
		{
			conn->disconnect();
			return true;
		}
	}
	return false;
}

void ConnectionList::connectionBroken(AbstractConnection const * conn)
{
	(void)doRemoveConnection(conn);
}

