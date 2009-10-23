#ifndef ABSTRACT_EVENT__HPP
#define ABSTRACT_EVENT__HPP

#include "ConnectionList.hpp"

class AbstractEvent
{
protected:
	AbstractEvent() {}
	~AbstractEvent() {}
public:
	size_t connectionCount() const
	{
		return connections_.connectionCount();
	}
	size_t connectionCount(AbstractDelegate const & deleg) const
	{
		return connections_.connectionCount(deleg);
	}

	template<class T, class Y> size_t connectionCount(T * obj, Y pMemberFunc) const
	{
		return connectionCount(AbstractDelegate(obj, pMemberFunc));
	}

	bool hasConnections() const
	{
		return connections_.hasConnections();
	}
	bool hasConnections(AbstractDelegate const & deleg) const
	{
		return connections_.hasConnections(deleg);
	}

	template<class T, class Y> bool hasConnections(T * obj, Y pMemberFunc) const
	{
		return hasConnections(AbstractDelegate(obj, pMemberFunc));
	}

	size_t disconnectAll()
	{
		return connections_.disconnectAll();
	}
	size_t disconnectAll(AbstractDelegate const & deleg)
	{
		return connections_.disconnectAll(deleg);
	}

	inline bool disconnectOne(AbstractDelegate const & deleg);

	template<class T, class Y> size_t disconnectAll(T * obj, Y pMemberFunc)
	{
		return disconnectAll(AbstractDelegate(obj, pMemberFunc));
	}
	template<class T, class Y> bool disconnectOne(T * obj, Y pMemberFunc)
	{
		return disconnectOne(AbstractDelegate(obj, pMemberFunc));
	}
protected:
	typedef ConnectionList::ConnectionsVector ConnectionsVector;

	class FireLock
	{
	public:
		FireLock(AbstractEvent const * e)
			: connections_(e->connections())
			, locker_(e->connectionsLock())
		{}

		ConnectionsVector const & connections() const
		{
			return connections_;
		}
	private:
		ConnectionsVector const & connections_;
		ThreadDataLocker locker_;
	};
	
	void addConnection(ConnectionList * tracker, AbstractConnection * conn)
	{
		connections_.connect(tracker, conn);
	}
private:
	ConnectionList connections_;

	ThreadDataRef & connectionsLock() const { return connections_.lock_; }
	ConnectionsVector const & connections() const { return connections_.connections_; }
};

class AbstractEventRef
{
public:
	AbstractEventRef(AbstractEvent * ev)
		: event_(ev)
	{}
	AbstractEventRef(AbstractEventRef const & other)
		: event_(other.event_)
	{}

	bool operator==(AbstractEventRef const & other) const
	{
		return event_ == other.event_;
	}

	bool operator!=(AbstractEventRef const & other) const
	{
		return event_ != other.event_;
	}

	size_t connectionCount() const
	{
		return event_->connectionCount();
	}
	size_t connectionCount(AbstractDelegate const & deleg) const
	{
		return event_->connectionCount(deleg);
	}
	template<class T, class Y> size_t connectionCount(T * reciever, Y pMemberFunc) const
	{
		return event_->connectionCount(reciever, pMemberFunc);
	}

	bool hasConnections() const
	{
		return event_->hasConnections();
	}
	bool hasConnections(AbstractDelegate const & deleg) const
	{
		return event_->hasConnections(deleg);
	}
	template<class T, class Y> bool hasConnections(T * reciever, Y pMemberFunc) const
	{
		return event_->hasConnections(reciever, pMemberFunc);
	}

	size_t disconnectAll()
	{
		return event_->disconnectAll();
	}
	size_t disconnectAll(AbstractDelegate const & deleg)
	{
		return event_->disconnectAll(deleg);
	}
	template<class T, class Y> size_t disconnectAll(T * reciever, Y pMemberFunc)
	{
		return event_->disconnectAll(reciever, pMemberFunc);
	}
	bool disconnectOne(AbstractDelegate const & deleg)
	{
		return event_->disconnectOne(deleg);
	}
	template<class T, class Y> bool disconnectOne(T * reciever, Y pMemberFunc)
	{
		return event_->disconnectOne(reciever, pMemberFunc);
	}
protected:
	AbstractEvent * senderEvent() const { return event_; }
private:
	AbstractEvent * event_;
};

inline AbstractEventRef AbstractConnection::senderEventRef() const
{
	return AbstractEventRef(event_);
}

inline bool AbstractEvent::disconnectOne(AbstractDelegate const & deleg)
{
	return connections_.disconnectOne(AbstractEventRef(this), deleg);
}


#endif //ABSTRACT_EVENT__HPP