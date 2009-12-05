#ifndef CONNECTION_LIST__HPP
#define CONNECTION_LIST__HPP

#include "AbstractConnection.hpp"
#include <vector>

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

	void connect(ConnectionList * peer, AbstractConnection * conn);

	size_t connectionCount() const;
	size_t connectionCount(AbstractDelegate const & deleg) const;
	size_t connectionCount(ConnectionList * peer) const;
	size_t connectionCount(ConnectionList * peer, AbstractDelegate const & deleg) const;

	bool hasConnections() const;
	bool hasConnections(AbstractDelegate const & deleg) const;
	bool hasConnections(ConnectionList * peer) const;
	bool hasConnections(ConnectionList * peer, AbstractDelegate const & deleg) const;

	size_t disconnectAll();
	size_t disconnectAll(AbstractDelegate const & deleg);
	size_t disconnectAll(ConnectionList * peer);
	size_t disconnectAll(ConnectionList * peer, AbstractDelegate const & deleg);

	bool disconnectOne(AbstractDelegate const & deleg);
	bool disconnectOne(ConnectionList * peer);
	bool disconnectOne(ConnectionList * peer, AbstractDelegate const & deleg);

	template<class T, class Y> size_t connectionCount(T * obj, Y pMemberFunc) const
	{
		return connectionCount(AbstractDelegate(obj, pMemberFunc));
	}
	template<class T, class Y> size_t connectionCount(ConnectionList * peer, T * obj, Y pMemberFunc) const
	{
		return connectionCount(peer, AbstractDelegate(obj, pMemberFunc));
	}

	template<class T, class Y> bool hasConnections(T * obj, Y pMemberFunc) const
	{
		return hasConnections(AbstractDelegate(obj, pMemberFunc));
	}
	template<class T, class Y> bool hasConnections(ConnectionList * peer, T * obj, Y pMemberFunc) const
	{
		return hasConnections(peer, AbstractDelegate(obj, pMemberFunc));
	}

	template<class T, class Y> size_t disconnect(T * obj, Y pMemberFunc)
	{
		return disconnect(AbstractDelegate(obj, pMemberFunc));
	}
	template<class T, class Y> size_t disconnect(ConnectionList * peer, T * obj, Y pMemberFunc)
	{
		return disconnect(peer, AbstractDelegate(obj, pMemberFunc));
	}
private:
	typedef std::vector<AbstractConnection*> ConnectionsVector;
	class NullComparer;
	class DelegateComparer;
	class PeerComparer;
	class FullComparer;

	mutable ThreadDataRef lock_;
	ConnectionsVector connections_;
	ConnectionsVector * stolenConnections_;

	template<class Comparer> inline size_t getConnectionCount(Comparer const &) const;
	template<class Comparer> inline bool getHasConnections(Comparer const &) const;
	template<class Comparer> inline size_t doDisconnectAll(Comparer const & );
	template<class Comparer> inline bool doDisconnectOne(Comparer const & );

	ConnectionsVector const & constRef() const;
	void detach();
};

#endif //CONNECTION_LIST__HPP