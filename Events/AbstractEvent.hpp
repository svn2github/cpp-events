#ifndef ABSTRACT_EVENT__HPP
#define ABSTRACT_EVENT__HPP

#include "ConnectionList.hpp"

class AbstractEvent
{
protected:
	AbstractEvent() {}
	~AbstractEvent() {}
public:
	bool hasConnections() const { return connections_.hasAnyConnections(); }
	void disconnectAll() { connections_.disconnectAll(); }

	template<class T> bool isConnectedTo(T * reciever) const
	{
		return connections_.hasConnectionsWithReciever(reciever);
	}

	template<class T, class Y> bool isConnectedTo(T * reciever, Y pMemberFunc) const
	{
		return connections_.hasConnectionsWithDelegate(reciever, pMemberFunc);
	}

	bool disconnectAllWithSender(AbstractObjectRef sender)
	{
		return connections_.disconnectFromSender(sender);
	}

	bool disconnectFrom(AbstractObjectRef reciever)
	{
		return connections_.disconnectFromReciver(reciever);
	}
	
	template<class T, class Y> bool disconnectFrom(T * reciever, Y pMemberFunc)
	{
		return disconnectFromDelegate(reciever, pMemberFunc);
	}
protected:
	typedef ConnectionList::ConnectionsVector ConnectionsVector;
	ConnectionsVector const & connections() const { return connections_.connections_; }
	AbstractConnection *  addConnection(AbstractConnection * conn){ return connections_.addConnection(conn); }
private:
	ConnectionList connections_;
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
	AbstractEvent * senderEvent() const { return event_; }

	bool operator==(AbstractEventRef const & other) const
	{
		return event_ == other.event_ && sender_ == other.sender_;
	}

	bool operator!=(AbstractEventRef const & other) const
	{
		return event_ != other.event_ || sender_ != other.sender_;
	}

	bool disconnectAll()
	{
		return event_->disconnectAllWithSender(sender_);
	}

	template<class T> bool disconnectFrom(T * reciever)
	{
		return event_->disconnectFrom(reciever);
	}

	template<class T, class Y> bool disconnectFrom(T * reciever, Y pMemberFunc)
	{
		return event_->disconnectFrom(reciever, pMemberFunc);
	}
private:
	AbstractObjectRef sender_;
	AbstractEvent * event_;
};

inline AbstractEventRef AbstractConnection::senderEventRef() const
{
	return AbstractEventRef(sender_, event_);
}

#endif //ABSTRACT_EVENT__HPP