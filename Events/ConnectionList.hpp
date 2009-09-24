#ifndef CONNECTION_LIST__HPP
#define CONNECTION_LIST__HPP

#include "AbstractConnection.hpp"

class ConnectionList
{
	friend class AbstractEvent;
	friend void AbstractConnection::doDisconnect();
private:
	ConnectionList(ConnectionList const & other);
	ConnectionList & operator=(ConnectionList const & other);
public:
	ConnectionList();
	~ConnectionList();

	void connect(ConnectionList * tracker, AbstractConnection * conn);

	bool hasAnyConnections() const { return !connections_.empty(); }	
	bool hasConnectionsWithSender(AbstractObjectRef sender) const;
	bool hasConnectionsWithReciever(AbstractObjectRef reciever) const;
	bool hasConnectionsWithEvent(AbstractEventRef const & ev) const;
	bool hasConnectionsWithDelegate(AbstractDelegate const & deleg) const;

	size_t disconnectAll();
	size_t disconnectFromSender(AbstractObjectRef sender);
	size_t disconnectFromReciver(AbstractObjectRef reciver);
	size_t disconnectFromEvent(AbstractEventRef const & ev);
	size_t disconnectFromDelegate(AbstractDelegate const & deleg);
	size_t disconnectObjects(AbstractObjectRef sender, AbstractObjectRef reciever);
	bool disconnectConnection(AbstractEventRef const & ev, AbstractDelegate const & deleg);

	template<class T, class Y> bool hasConnectionsWithDelegate(T * obj, Y pMemberFunc) const
	{
		return hasConnectionsWithDelegate(AbstractDelegate(obj, pMemberFunc));
	}

	template<class T, class Y> bool disconnectFromDelegate(T * obj, Y pmf)
	{
		return disconnectFromDelegate(AbstractDelegate(obj, pmf));
	}
		
	template<class T, class Y> bool disconnectConnection(AbstractEventRef const & ev, T * obj, Y pmf)
	{
		return disconnectConnection(ev, AbstractDelegate(obj, pmf));
	}
private:
	typedef std::vector<AbstractConnection*> ConnectionsVector;
	ThreadDataRef lock_;
	ConnectionsVector connections_;
};

#endif //CONNECTION_LIST__HPP