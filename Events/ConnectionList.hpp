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

	size_t connectionCount() const;
	size_t connectionCount(AbstractDelegate const & deleg) const;
	size_t connectionCount(AbstractEventRef const & ev) const;
	size_t connectionCount(AbstractEventRef const & ev, AbstractDelegate const & deleg) const;

	bool hasConnections() const;
	bool hasConnections(AbstractDelegate const & deleg) const;
	bool hasConnections(AbstractEventRef const & ev) const;
	bool hasConnections(AbstractEventRef const & ev, AbstractDelegate const & deleg) const;

	size_t disconnectAll();
	size_t disconnectAll(AbstractDelegate const & deleg);
	size_t disconnectAll(AbstractEventRef const & ev);
	size_t disconnectAll(AbstractEventRef const & ev, AbstractDelegate const & deleg);
	bool disconnectOne(AbstractEventRef const & ev, AbstractDelegate const & deleg);

	template<class T, class Y> size_t connectionCount(T * obj, Y pMemberFunc) const
	{
		return connectionCount(AbstractDelegate(obj, pMemberFunc));
	}
	template<class T, class Y> size_t connectionCount(AbstractEventRef const & ev, T * obj, Y pMemberFunc) const
	{
		return connectionCount(ev, AbstractDelegate(obj, pMemberFunc));
	}

	template<class T, class Y> bool hasConnections(T * obj, Y pMemberFunc) const
	{
		return hasConnections(AbstractDelegate(obj, pMemberFunc));
	}
	template<class T, class Y> bool hasConnections(AbstractEventRef const & ev, T * obj, Y pMemberFunc) const
	{
		return hasConnections(ev, AbstractDelegate(obj, pMemberFunc));
	}

	template<class T, class Y> size_t disconnect(T * obj, Y pMemberFunc)
	{
		return disconnect(AbstractDelegate(obj, pMemberFunc));
	}
	template<class T, class Y> size_t disconnect(AbstractEventRef const & ev, T * obj, Y pMemberFunc)
	{
		return disconnect(ev, AbstractDelegate(obj, pMemberFunc));
	}
private:
	typedef std::vector<AbstractConnection*> ConnectionsVector;
	mutable ThreadDataRef lock_;
	ConnectionsVector connections_;

	template<class Comparer> inline size_t getConnectionCount(Comparer const &) const;
	template<class Comparer> inline bool getHasConnections(Comparer const &) const;
	template<class Comparer> inline size_t doDisconnect(Comparer const & );
};

#endif //CONNECTION_LIST__HPP