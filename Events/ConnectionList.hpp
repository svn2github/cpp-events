#ifndef CONNECTION_LIST__HPP
#define CONNECTION_LIST__HPP

#include "AbstractConnection.hpp"
#include "normalize_cast.hpp"

class ConnectionList
{
	friend class AbstractEvent;
private:
	ConnectionList(ConnectionList const & other);
	ConnectionList & operator=(ConnectionList const & other);
public:
	ConnectionList() {}
	~ConnectionList() { disconnectAll(); }

	AbstractConnection * addConnection(AbstractConnection * conn);
	bool removeConnection(AbstractConnection * conn);

	bool hasAnyConnections() const { return !connections_.empty(); }	
	bool hasConnectionsWithSender(void const * sender) const;
	bool hasConnectionsWithReciever(void const * reciever) const;
	bool hasConnectionsWithEvent(AbstractEventRef const & ev) const;
	bool hasConnectionsWithDelegate(fastdelegate::DelegateMemento const & deleg) const;

	void disconnectAll();
	bool disconnectFromSender(void const * sender);
	bool disconnectFromReciver(void const * reciver);
	bool disconnectFromEvent(AbstractEventRef const & ev);
	bool disconnectFromDelegate(fastdelegate::DelegateMemento const & deleg);

	ConnectionList & operator += (AbstractConnection * conn)
	{
		addConnection(conn);
		return *this;
	}

	ConnectionList & operator -= (AbstractConnection * conn)
	{
		removeConnection(conn);
		return *this;
	}
	
	template<class T> bool hasConnectionsWithSender(T * sender) const
	{
		return hasConnectionsWithSender(normalize_cast(sender));
	}

	template<class T> bool hasConnectionsWithReciever(T * reciever) const
	{
		return hasConnectionsWithReciever(normalize_cast(reciever));
	}

	template<class T, class Y> bool hasConnectionsWithDelegate(T * obj, Y pMemberFunc) const
	{
		return hasConnectionsWithDelegate(fastdelegate::MakeDelegate(obj, pMemberFunc).GetMemento());
	}

	template<class T> bool disconnectFromSender(T * sender)
	{
		return disconnectFromSender(normalize_cast(sender));
	}

	template<class T> bool disconnectFromReciver(T * reciver)
	{
		return disconnectFromReciver(normalize_cast(reciver));
	}

	template<class T, class Y> bool disconnectFromDelegate(T * obj, Y pmf)
	{
		return disconnectFromDelegate(fastdelegate::MakeDelegate(obj, pmf).GetMemento());
	}
private:
	typedef std::vector<AbstractConnection*> ConnectionsVector;
	ConnectionsVector connections_;

	void connectionBroken(AbstractConnection const * conn);
	bool doRemoveConnection(AbstractConnection const * conn);
};

#endif //CONNECTION_LIST__HPP