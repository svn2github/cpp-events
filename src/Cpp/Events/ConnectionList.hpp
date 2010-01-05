#ifndef CONNECTION_LIST__HPP
#define CONNECTION_LIST__HPP

#include "BorrowableData.hpp"

class ConnectionList
{
	friend void AbstractConnection::doDisconnect();
	DISABLE_COPY(ConnectionList)
public:
	class FireLock;

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
private:
	class NullComparer;
	class DelegateComparer;
	class PeerComparer;
	class FullComparer;

	mutable ThreadDataRef lock_;
	BorrowableData data_;

	template<class Comparer> inline size_t getConnectionCount(Comparer const &) const;
	template<class Comparer> inline bool getHasConnections(Comparer const &) const;
	template<class Comparer> inline size_t doDisconnectAll(Comparer const & );
	template<class Comparer> inline bool doDisconnectOne(Comparer const & );
};

class ConnectionList::FireLock
{
	DISABLE_COPY(FireLock)
public:
	FireLock(ConnectionList const * list)
		: locker_(list->lock_)
		, borrower_(&list->data_)
	{}

	ConnectionsVector const & constData() const
	{
		return borrower_.constData();
	}
private:
	ThreadDataLocker locker_;
	BorrowableData::Borrower borrower_;
};

#endif //CONNECTION_LIST__HPP