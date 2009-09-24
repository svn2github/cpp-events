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
	size_t connectionCount(anySender, anyReciever) const
	{
		return connections_.connectionCount();
	}
	size_t connectionCount(anySender, AbstractObjectRef reciever) const
	{
		return connections_.connectionCount(anySender(), reciever);
	}
	size_t connectionCount(anySender, AbstractDelegate const & deleg) const
	{
		return connections_.connectionCount(anySender(), deleg);
	}

	size_t connectionCount(AbstractObjectRef sender) const
	{
		return connections_.connectionCount(sender, anyReciever());
	}
	size_t connectionCount(AbstractObjectRef sender, anyReciever) const
	{
		return connections_.connectionCount(sender, anyReciever());
	}
	size_t connectionCount(AbstractObjectRef sender, AbstractObjectRef reciever) const
	{
		return connections_.connectionCount(sender, reciever);
	}
	size_t connectionCount(AbstractObjectRef sender, AbstractDelegate const & deleg) const
	{
		return connections_.connectionCount(sender, deleg);
	}

	template<class T, class Y> size_t connectionCount(anySender, T * obj, Y pMemberFunc) const
	{
		return connectionCount(anySender(), AbstractDelegate(obj, pMemberFunc));
	}
	template<class T, class Y> size_t connectionCount(AbstractObjectRef sender, T * obj, Y pMemberFunc) const
	{
		return connectionCount(sender, AbstractDelegate(obj, pMemberFunc));
	}

	bool hasConnections() const
	{
		return connections_.hasConnections();
	}
	bool hasConnections(anySender, anyReciever) const
	{
		return connections_.hasConnections();
	}
	bool hasConnections(anySender, AbstractObjectRef reciever) const
	{
		return connections_.hasConnections(anySender(), reciever);
	}
	bool hasConnections(anySender, AbstractDelegate const & deleg) const
	{
		return connections_.hasConnections(anySender(), deleg);
	}

	bool hasConnections(AbstractObjectRef sender) const
	{
		return connections_.hasConnections(sender, anyReciever());
	}
	bool hasConnections(AbstractObjectRef sender, anyReciever) const
	{
		return connections_.hasConnections(sender, anyReciever());
	}
	bool hasConnections(AbstractObjectRef sender, AbstractObjectRef reciever) const
	{
		return connections_.hasConnections(sender, reciever);
	}
	bool hasConnections(AbstractObjectRef sender, AbstractDelegate const & deleg) const
	{
		return connections_.hasConnections(sender, deleg);
	}

	template<class T, class Y> bool hasConnections(T * obj, Y pMemberFunc) const
	{
		return hasConnections(anySender(), AbstractDelegate(obj, pMemberFunc));
	}
	template<class T, class Y> bool hasConnections(AbstractObjectRef sender, T * obj, Y pMemberFunc) const
	{
		return hasConnections(sender, AbstractDelegate(obj, pMemberFunc));
	}

	size_t disconnectAll()
	{
		return connections_.disconnectAll();
	}
	size_t disconnect(anySender, anyReciever)
	{
		return connections_.disconnectAll();
	}
	size_t disconnect(anySender, AbstractObjectRef reciever)
	{
		return connections_.disconnect(anySender(), reciever);
	}
	size_t disconnect(anySender, AbstractDelegate const & deleg)
	{
		return connections_.disconnect(anySender(), deleg);
	}

	size_t disconnectAll(AbstractObjectRef sender)
	{
		return connections_.disconnect(sender, anyReciever());
	}
	size_t disconnect(AbstractObjectRef sender, anyReciever)
	{
		return connections_.disconnect(sender, anyReciever());
	}
	size_t disconnect(AbstractObjectRef sender, AbstractObjectRef reciever)
	{
		return connections_.disconnect(sender, reciever);
	}
	size_t disconnect(AbstractObjectRef sender, AbstractDelegate const & deleg)
	{
		return connections_.disconnect(sender, deleg);
	}

	template<class T, class Y> size_t disconnect(anySender, T * obj, Y pMemberFunc)
	{
		return disconnect(anySender(), AbstractDelegate(obj, pMemberFunc));
	}
	template<class T, class Y> size_t disconnect(AbstractObjectRef sender, T * obj, Y pMemberFunc)
	{
		return disconnect(sender, AbstractDelegate(obj, pMemberFunc));
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
	AbstractEventRef(AbstractObjectRef sender, AbstractEvent * ev)
		: sender_(sender)
		, event_(ev)
	{}
	AbstractEventRef(AbstractEventRef const & other)
		: sender_(other.sender_)
		, event_(other.event_)
	{}

	AbstractObjectRef senderObject() const { return sender_; }

	bool operator==(AbstractEventRef const & other) const
	{
		return event_ == other.event_ && sender_ == other.sender_;
	}

	bool operator!=(AbstractEventRef const & other) const
	{
		return event_ != other.event_ || sender_ != other.sender_;
	}

	size_t connectionCount() const
	{
		return event_->connectionCount(sender_);
	}
	size_t connectionCount(anyReciever) const
	{
		return event_->connectionCount(sender_);
	}
	size_t connectionCount(AbstractObjectRef reciever) const
	{
		return event_->connectionCount(sender_, reciever);
	}
	size_t connectionCount(AbstractDelegate const & deleg) const
	{
		return event_->connectionCount(sender_, deleg);
	}
	template<class T, class Y> size_t connectionCount(T * reciever, Y pMemberFunc) const
	{
		return event_->connectionCount(sender_, reciever, pMemberFunc);
	}

	bool hasConnections() const
	{
		return event_->hasConnections(sender_);
	}
	bool hasConnections(anyReciever) const
	{
		return event_->hasConnections(sender_);
	}
	bool hasConnections(AbstractObjectRef reciever) const
	{
		return event_->hasConnections(sender_, reciever);
	}
	bool hasConnections(AbstractDelegate const & deleg) const
	{
		return event_->hasConnections(sender_, deleg);
	}
	template<class T, class Y> bool hasConnections(T * reciever, Y pMemberFunc) const
	{
		return event_->hasConnections(sender_, reciever, pMemberFunc);
	}

	size_t disconnectAll()
	{
		return event_->disconnectAll(sender_);
	}
	size_t disconnect(AbstractObjectRef reciever)
	{
		return event_->disconnect(sender_, reciever);
	}
	size_t disconnect(AbstractDelegate const & deleg)
	{
		return event_->disconnect(sender_, deleg);
	}
	template<class T, class Y> size_t disconnect(T * reciever, Y pMemberFunc)
	{
		return event_->disconnect(sender_, reciever, pMemberFunc);
	}
protected:
	AbstractEvent * senderEvent() const { return event_; }
private:
	AbstractObjectRef sender_;
	AbstractEvent * event_;
};

inline AbstractEventRef AbstractConnection::senderEventRef() const
{
	return AbstractEventRef(sender_, event_);
}

#endif //ABSTRACT_EVENT__HPP