#ifndef CONNECTION_LIST__HPP
#define CONNECTION_LIST__HPP

#include "AbstractConnection.hpp"

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
	bool hasConnectionsWithSender(AbstractObjectRef sender) const;
	bool hasConnectionsWithReciever(AbstractObjectRef reciever) const;
	bool hasConnectionsWithEvent(AbstractEventRef const & ev) const;
	bool hasConnectionsWithDelegate(AbstractDelegate const & deleg) const;

	void disconnectAll();
	bool disconnectFromSender(AbstractObjectRef sender);
	bool disconnectFromReciver(AbstractObjectRef reciver);
	bool disconnectFromEvent(AbstractEventRef const & ev);
	bool disconnectFromDelegate(AbstractDelegate const & deleg);
	bool disconnectObjects(AbstractObjectRef sender, AbstractObjectRef reciever);
	bool disconnectConnection(AbstractEventRef const & ev, AbstractDelegate const & deleg);

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

	template<class T, class Y> bool hasConnectionsWithDelegate(T * obj, Y pMemberFunc) const
	{
		return hasConnectionsWithDelegate(fastdelegate::MakeDelegate(obj, pMemberFunc).GetMemento());
	}

	template<class T, class Y> bool disconnectFromDelegate(T * obj, Y pmf)
	{
		return disconnectFromDelegate(fastdelegate::MakeDelegate(obj, pmf).GetMemento());
	}
		
	template<class T, class Y> bool disconnectConnection(AbstractEventRef const & ev, T * obj, Y pmf)
	{
		return disconnectConnection(ev, AbstractDelegate(obj, pmf));
	}
private:
	typedef std::vector<AbstractConnection*> ConnectionsVector;
	ConnectionsVector connections_;

	void connectionBroken(AbstractConnection const * conn);
	bool doRemoveConnection(AbstractConnection const * conn);
};

#endif //CONNECTION_LIST__HPP