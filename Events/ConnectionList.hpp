#ifndef CONNECTION_LIST__HPP
#define CONNECTION_LIST__HPP

#include "AtomicReferenceCounter.hpp"
#include "AbstractDelegate.hpp"
#include "Threading.hpp"
#include <vector>

class ExtraDelegateData
{
protected:
	ExtraDelegateData(AbstractDelegate const & d) : deleg_(d) {}
	virtual ~ExtraDelegateData() {};
public:
	void retain() const { ref_.retain(); }
	void release() const { if(ref_.release()) delete this; }
	
	AbstractDelegate const & targetDelegate() const { return deleg_; }
private:
	mutable AtomicReferenceCounter ref_;
	AbstractDelegate deleg_;
};

class ConnectionList
{
	friend class AbstractEvent;
private:
	ConnectionList(ConnectionList const & other);
	ConnectionList & operator=(ConnectionList const & other);
public:
	ConnectionList();
	~ConnectionList();

	void connect(ConnectionList * peer, AbstractDelegate const & deleg, ExtraDelegateData * data);

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
	struct ConnectionData
	{
		//Special value for null index
		static size_t const npos = size_t(0) - size_t(1);

		//Reference counter protects data record from being removed untimely.
		AtomicReferenceCounter ref_;
		//Each logical connection is protected by two mutexes in different connection lists.
		//They should be locked in specific order, in order to avoid deadlocks.
		//Thus, we need to access both mutexes before locking any of them.
		//But we cannot dereference peer_ pointer until mutex in this connection list is locked.
		//So we need to store reference to peer's mutex explicitly.
		ThreadDataRef peerLock_;
		//Pointer to peer connection list object.
		ConnectionList * peer_;
		//Index of symmetric connection record in peer connection list object.
		//(Updated when record is moved).
		size_t indexInPeer_;
		//Pointer to optional extra data assigned with delegate.
		ExtraDelegateData * extraData_;
		//Delegate that is used for invocation.
		//If extraData_ is null then this delegate is also the target delegate and can be used for comparison.
		//Otherwise extraData_->targetDelegate() should be used for comparison.
		AbstractDelegate delegate_;

		ConnectionData()
			: ref_()
			, peerLock_(ThreadDataRef::null())
			, peer_()
			, indexInPeer_(npos)
			, extraData_()
			, delegate_()
		{}

		AbstractDelegate const & targetDelegate() const
		{
			return extraData_ ? extraData_->targetDelegate() : delegate_;
		}

		ConnectionData * peerData()
		{
			return &peer_->connections_[indexInPeer_];
		}

		void clear()
		{
			peer_ = 0;
			indexInPeer_ = npos;
			delegate_.clear();
			if(extraData_)
			{
				extraData_->release();
				extraData_ = 0;
			}
		}
	};

	typedef std::vector<ConnectionData> ConnectionsVector;
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

	bool tryDisconnectWithLock(size_t index);
	void disconnectAt(size_t index);
	void retainConn(size_t index);
	void releaseConn(size_t index);
	void doDisconnect(size_t index);
};

#endif //CONNECTION_LIST__HPP