#ifndef CONNECTION_LIST__HPP
#define CONNECTION_LIST__HPP

#include "AbstractConnection.hpp"

class anySender {};
class anyReciever {};

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

	size_t connectionCount() const;
	size_t connectionCount(anySender, anyReciever) const { return connectionCount(); }
	size_t connectionCount(anySender, AbstractObjectRef reciever) const;
	size_t connectionCount(anySender, AbstractDelegate const & deleg) const;
	size_t connectionCount(AbstractObjectRef sender, anyReciever) const;
	size_t connectionCount(AbstractObjectRef sender, AbstractObjectRef reciever) const;
	size_t connectionCount(AbstractObjectRef sender, AbstractDelegate const & deleg) const;
	size_t connectionCount(AbstractEventRef const & ev, anyReciever) const;
	size_t connectionCount(AbstractEventRef const & ev, AbstractObjectRef reciever) const;
	size_t connectionCount(AbstractEventRef const & ev, AbstractDelegate const & deleg) const;

	bool hasConnections() const;
	bool hasConnections(anySender, anyReciever) const { return hasConnections(); }
	bool hasConnections(anySender, AbstractObjectRef reciever) const;
	bool hasConnections(anySender, AbstractDelegate const & deleg) const;
	bool hasConnections(AbstractObjectRef sender, anyReciever) const;
	bool hasConnections(AbstractObjectRef sender, AbstractObjectRef reciever) const;
	bool hasConnections(AbstractObjectRef sender, AbstractDelegate const & deleg) const;
	bool hasConnections(AbstractEventRef const & ev, anyReciever) const;
	bool hasConnections(AbstractEventRef const & ev, AbstractObjectRef reciever) const;
	bool hasConnections(AbstractEventRef const & ev, AbstractDelegate const & deleg) const;

	size_t disconnectAll();
	size_t disconnect(anySender, anyReciever) { return disconnectAll(); }
	size_t disconnect(anySender, AbstractObjectRef reciever);
	size_t disconnect(anySender, AbstractDelegate const & deleg);
	size_t disconnect(AbstractObjectRef sender, anyReciever);
	size_t disconnect(AbstractObjectRef sender, AbstractObjectRef reciever);
	size_t disconnect(AbstractObjectRef sender, AbstractDelegate const & deleg);
	size_t disconnect(AbstractEventRef const & ev, anyReciever);
	size_t disconnect(AbstractEventRef const & ev, AbstractObjectRef reciever);
	size_t disconnect(AbstractEventRef const & ev, AbstractDelegate const & deleg);
	bool disconnectOne(AbstractEventRef const & ev, AbstractDelegate const & deleg);

	template<class T, class Y> size_t connectionCount(anySender, T * obj, Y pMemberFunc) const
	{
		return connectionCount(anySender(), AbstractDelegate(obj, pMemberFunc));
	}
	template<class T, class Y> size_t connectionCount(AbstractObjectRef sender, T * obj, Y pMemberFunc) const
	{
		return connectionCount(sender, AbstractDelegate(obj, pMemberFunc));
	}
	template<class T, class Y> size_t connectionCount(AbstractEventRef const & ev, T * obj, Y pMemberFunc) const
	{
		return connectionCount(ev, AbstractDelegate(obj, pMemberFunc));
	}

	template<class T, class Y> bool hasConnections(anySender, T * obj, Y pMemberFunc) const
	{
		return hasConnections(anySender(), AbstractDelegate(obj, pMemberFunc));
	}
	template<class T, class Y> bool hasConnections(AbstractObjectRef sender, T * obj, Y pMemberFunc) const
	{
		return hasConnections(sender, AbstractDelegate(obj, pMemberFunc));
	}
	template<class T, class Y> bool hasConnections(AbstractEventRef const & ev, T * obj, Y pMemberFunc) const
	{
		return hasConnections(ev, AbstractDelegate(obj, pMemberFunc));
	}

	template<class T, class Y> size_t disconnect(anySender, T * obj, Y pMemberFunc)
	{
		return disconnect(anySender(), AbstractDelegate(obj, pMemberFunc));
	}
	template<class T, class Y> size_t disconnect(AbstractObjectRef sender, T * obj, Y pMemberFunc)
	{
		return disconnect(sender, AbstractDelegate(obj, pMemberFunc));
	}
	template<class T, class Y> size_t disconnect(AbstractEventRef const & ev, T * obj, Y pMemberFunc)
	{
		return disconnect(ev, AbstractDelegate(obj, pMemberFunc));
	}
private:
	typedef std::vector<AbstractConnection*> ConnectionsVector;
	mutable ThreadDataRef lock_;
	ConnectionsVector connections_;
};

#endif //CONNECTION_LIST__HPP