#ifndef ABSTRACT_CONNECTION__HPP
#define ABSTRACT_CONNECTION__HPP

#include "../FastDelegate/src/FastDelegate.h"
#include <vector>

class AbstractEvent;
class AbstractEventRef;

//! Abstract class that represents arbitary delegate in a common form.
class AbstractDelegate
{
public:
	AbstractDelegate() : d_() {}
	AbstractDelegate(fastdelegate::DelegateMemento const & d) : d_(d) {}

	template<class T, class Y> AbstractDelegate(T obj, Y pmf)
		: d_(fastdelegate::MakeDelegate(obj, pmf))
	{}

	bool isNull() const { return d_.empty(); }
	void clear() { d_.clear(); }

	bool operator<(AbstractDelegate const & r) const { return d_.IsLess(r.d_); }
	bool operator>(AbstractDelegate const & r) const { return r.d_.IsLess(d_); }
	bool operator==(AbstractDelegate const & r) const { return d_.IsEqual(r.d_); }
	bool operator!=(AbstractDelegate const & r) const { return !d_.IsEqual(r.d_); }
	bool operator>=(AbstractDelegate const & r) const { return !d_.IsLess(r.d_); }
	bool operator<=(AbstractDelegate const & r) const { return !r.d_.IsLess(d_); }
private:
	fastdelegate::DelegateMemento d_;
};

//! Root class for all template connection classes.
class AbstractConnection
{
private:
	//Connections cannot be copied.
	AbstractConnection(AbstractConnection const &);
	AbstractConnection & operator=(AbstractConnection const &);
public:
	// Typeless pointer to the sender object (retrieved via dynamic_cast<void*>(pObj)).
	void const * senderObject() const { return sender_; }
	AbstractEvent const * senderEvent() const { return event_; }
	inline AbstractEventRef senderEventRef() const;
	// Typeless pointer to the receiver object (retrieved via dynamic_cast<void const *>(pObj)).
	void const * recieverObject() const { return reciever_; }
	// Typeless delegate of the receiver object that can be used for comparison, but cannot be invoked.
	AbstractDelegate recieverDelegate() const { return targetDelegate_; }

	void disconnect();

	template<class T, class Y> void addDisconnectListener(T * obj, void (Y::*pmf)(AbstractConnection const *))
	{
		doAddDisconnectListener(fastdelegate::MakeDelegate(obj, pmf));
	}

	template<class T, class Y> void addDisconnectListener(T const * obj, void (Y::*pmf)(AbstractConnection const *) const)
	{
		doAddDisconnectListener(fastdelegate::MakeDelegate(obj, pmf));
	}

	template<class T, class Y> void removeDisconnectListener(T * obj, void (Y::*pmf)(AbstractConnection const *))
	{
		doRemoveDisconnectListener(fastdelegate::MakeDelegate(obj, pmf));
	}

	template<class T, class Y> void removeDisconnectListener(T const * obj, void (Y::*pmf)(AbstractConnection const *) const)
	{
		doRemoveDisconnectListener(fastdelegate::MakeDelegate(obj, pmf));
	}
protected:
	AbstractConnection(void const * sender, AbstractEvent * ev, void const * reciever, AbstractDelegate const & targetDelegate)
		: sender_(sender), event_(ev)
		, reciever_(reciever)
		, targetDelegate_(targetDelegate)
	{}
	virtual ~AbstractConnection() {}
private:
	typedef fastdelegate::FastDelegate1<AbstractConnection const *> DisconnectDelegate;
	typedef std::vector<DisconnectDelegate> ListenersList;

	void const * sender_;
	AbstractEvent * event_;
	void const * reciever_;
	AbstractDelegate targetDelegate_;
	// Array of listeners that will be notified when this connection is broken.
	// Order of notifications is undefined.
	ListenersList listeners_;

	void doAddDisconnectListener(DisconnectDelegate const & deleg);
	void doRemoveDisconnectListener(DisconnectDelegate const & deleg);
};

#endif //ABSTRACT_CONNECTION__HPP