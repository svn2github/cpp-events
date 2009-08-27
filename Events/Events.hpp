#ifndef EVENTS_HPP
#define EVENTS_HPP

#include "AbstractEvent.hpp"
#include "ConnectionEx.hpp"
#include "TypeTraits.hpp"

template<class R> class EventFireHelper0 : public AbstractEvent
{
public:
	typedef Connection0<R> ConnectionType;

	R fire() const
	{
		R retVal;
		ConnectionsVector const & conns = connections();
		for(ConnectionsVector::const_iterator it = conns.begin(); it != conns.end(); ++it)
		{
			retVal = static_cast<ConnectionType const *>(*it)->invoke();
		}
		return retVal;
	}
protected:
	EventFireHelper0() {}
	~EventFireHelper0() {}
};

template<> class EventFireHelper0<void> : public AbstractEvent
{
public:
	void fire() const
	{
		ConnectionsVector const & conns = connections();
		for(ConnectionsVector::const_iterator it = conns.begin(); it != conns.end(); ++it)
		{
			static_cast<ConnectionType const *>(*it)->invoke();
		}
	}
protected:
	typedef Connection0<void> ConnectionType;

	EventFireHelper0() {}
	~EventFireHelper0() {}
};

template<class R = void> class EventRef0;

template<class R = void> class Event0 : public EventFireHelper0<R>
{
public:
	typedef typename EventFireHelper0<R>::ConnectionType ConnectionType;

	Event0() {}
	~Event0() {}

	AbstractConnection * addConnection(ConnectionType * conn)
	{
		return AbstractEvent::addConnection(conn);
	}

	inline EventRef0<R> bind(void const * sender);
	
	template<class T> inline EventRef0<R> bind(T * sender);
};

template<class R> class EventRef0 : public AbstractEventRef
{
public:
	typedef Event0<R> EventType;
	typedef typename EventType::ConnectionType ConnectionType;

	EventRef0(void const * sender, EventType * ev) : AbstractEventRef(sender, ev) {}

	EventRef0<R> rebind(void const * newSender) const
	{
		return EventRef0<R>(newSender, event_);
	}
	
	template<class T> inline EventRef0<R> rebind(T * newSender) const
	{
		return rebind(normalize_cast(newSender));
	}

	template<class T, class Y> AbstractConnection * connect(T * obj, R (Y::*pmf)())
	{
		ConnectionType * conn = new ConnectionType(
			senderObject(), senderEvent(), normalize_cast(obj),
			fastdelegate::MakeDelegate(obj, pmf)
		);
		return addConnection(conn);
	}

	template<class T, class Y> AbstractConnection * connect(T const * obj, R (Y::*pmf)() const)
	{
		ConnectionType * conn = new ConnectionType(
			senderObject(), senderEvent(), normalize_cast(obj),
			fastdelegate::MakeDelegate(obj, pmf)
		);
		return addConnection(conn);
	}

	template<class T, class Y> AbstractConnection * connect(T * obj, Y pmf)
	{
		detail::ArgList0 stored;
		return connectEx(normalize_cast(obj), fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1> AbstractConnection * connect(T * obj, Y pmf, T1 x1)
	{
		typedef typename StorageType<T1>::Type S1;
		detail::ArgList1<S1> stored(x1);
		return connectEx(normalize_cast(obj), fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2> AbstractConnection * connect(T * obj, Y pmf, T1 x1, T2 x2)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		detail::ArgList2<S1,S2> stored(x1,x2);
		return connectEx(normalize_cast(obj), fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3> AbstractConnection * connect(T * obj, Y pmf, T1 x1, T2 x2, T3 x3)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		detail::ArgList3<S1,S2,S3> stored(x1,x2,x3);
		return connectEx(normalize_cast(obj), fastdelegate::MakeDelegate(obj, pmf), stored);
	}
private:
	AbstractConnection * addConnection(ConnectionType * conn)
	{
		return static_cast<EventType*>(senderEvent())->addConnection(conn);
	}

	template<class DelegateClass, class StoredListClass> AbstractConnection * connectEx(void const * obj, DelegateClass const & deleg, StoredListClass const & stored)
	{
		ConnectionType * conn = new ConnectionEx0<R, DelegateClass, StoredListClass>(
			senderObject(), senderEvent(), obj, deleg, stored
		);
		return addConnection(conn);
	}
};

template<class R> inline EventRef0<R> Event0<R>::bind(void const * sender)
{
	return EventRef0<R>(sender, this);
}

template<class R> template<class T> inline EventRef0<R> Event0<R>::bind(T * sender)
{
	return bind(normalize_cast(sender));
}

template<class Param0, class R> class EventFireHelper1 : public AbstractEvent
{
public:
	typedef Connection1<Param0, R> ConnectionType;

	R fire(Param0 p0) const
	{
		R retVal;
		ConnectionsVector const & conns = connections();
		for(ConnectionsVector::const_iterator it = conns.begin(); it != conns.end(); ++it)
		{
			retVal = static_cast<ConnectionType const *>(*it)->invoke(p0);
		}
		return retVal;
	}
protected:
	EventFireHelper1() {}
	~EventFireHelper1() {}
};

template<class Param0> class EventFireHelper1<Param0, void> : public AbstractEvent
{
public:
	void fire(Param0 p0) const
	{
		ConnectionsVector const & conns = connections();
		for(ConnectionsVector::const_iterator it = conns.begin(); it != conns.end(); ++it)
		{
			static_cast<ConnectionType const *>(*it)->invoke(p0);
		}
	}
protected:
	typedef Connection1<Param0, void> ConnectionType;

	EventFireHelper1() {}
	~EventFireHelper1() {}
};

template<class Param0, class R = void> class EventRef1;

template<class Param0, class R = void> class Event1 : public EventFireHelper1<Param0, R>
{
public:
	typedef typename EventFireHelper1<Param0, R>::ConnectionType ConnectionType;

	Event1() {}
	~Event1() {}

	AbstractConnection * addConnection(ConnectionType * conn)
	{
		return AbstractEvent::addConnection(conn);
	}

	inline EventRef1<Param0, R> bind(void const * sender);
	
	template<class T> inline EventRef1<Param0, R> bind(T * sender);
};

template<class Param0, class R> class EventRef1 : public AbstractEventRef
{
public:
	typedef Event1<Param0, R> EventType;
	typedef typename EventType::ConnectionType ConnectionType;

	EventRef1(void const * sender, EventType * ev) : AbstractEventRef(sender, ev) {}

	EventRef1<Param0, R> rebind(void const * newSender) const
	{
		return EventRef1<Param0, R>(newSender, event_);
	}
	
	template<class T> inline EventRef1<Param0, R> rebind(T * newSender) const
	{
		return rebind(normalize_cast(newSender));
	}

	template<class T, class Y> AbstractConnection * connect(T * obj, R (Y::*pmf)(Param0 p0))
	{
		ConnectionType * conn = new ConnectionType(
			senderObject(), senderEvent(), normalize_cast(obj),
			fastdelegate::MakeDelegate(obj, pmf)
		);
		return addConnection(conn);
	}

	template<class T, class Y> AbstractConnection * connect(T const * obj, R (Y::*pmf)(Param0 p0) const)
	{
		ConnectionType * conn = new ConnectionType(
			senderObject(), senderEvent(), normalize_cast(obj),
			fastdelegate::MakeDelegate(obj, pmf)
		);
		return addConnection(conn);
	}

	template<class T, class Y> AbstractConnection * connect(T * obj, Y pmf)
	{
		detail::ArgList0 stored;
		return connectEx(normalize_cast(obj), fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1> AbstractConnection * connect(T * obj, Y pmf, T1 x1)
	{
		typedef typename StorageType<T1>::Type S1;
		detail::ArgList1<S1> stored(x1);
		return connectEx(normalize_cast(obj), fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2> AbstractConnection * connect(T * obj, Y pmf, T1 x1, T2 x2)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		detail::ArgList2<S1,S2> stored(x1,x2);
		return connectEx(normalize_cast(obj), fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3> AbstractConnection * connect(T * obj, Y pmf, T1 x1, T2 x2, T3 x3)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		detail::ArgList3<S1,S2,S3> stored(x1,x2,x3);
		return connectEx(normalize_cast(obj), fastdelegate::MakeDelegate(obj, pmf), stored);
	}
private:
	AbstractConnection * addConnection(ConnectionType * conn)
	{
		return static_cast<EventType*>(senderEvent())->addConnection(conn);
	}

	template<class DelegateClass, class StoredListClass> AbstractConnection * connectEx(void const * obj, DelegateClass const & deleg, StoredListClass const & stored)
	{
		ConnectionType * conn = new ConnectionEx1<Param0, R, DelegateClass, StoredListClass>(
			senderObject(), senderEvent(), obj, deleg, stored
		);
		return addConnection(conn);
	}
};

template<class Param0, class R> inline EventRef1<Param0, R> Event1<Param0, R>::bind(void const * sender)
{
	return EventRef1<Param0, R>(sender, this);
}

template<class Param0, class R> template<class T> inline EventRef1<Param0, R> Event1<Param0, R>::bind(T * sender)
{
	return bind(normalize_cast(sender));
}

template<class Param0, class Param1, class R> class EventFireHelper2 : public AbstractEvent
{
public:
	typedef Connection2<Param0, Param1, R> ConnectionType;

	R fire(Param0 p0, Param1 p1) const
	{
		R retVal;
		ConnectionsVector const & conns = connections();
		for(ConnectionsVector::const_iterator it = conns.begin(); it != conns.end(); ++it)
		{
			retVal = static_cast<ConnectionType const *>(*it)->invoke(p0, p1);
		}
		return retVal;
	}
protected:
	EventFireHelper2() {}
	~EventFireHelper2() {}
};

template<class Param0, class Param1> class EventFireHelper2<Param0, Param1, void> : public AbstractEvent
{
public:
	void fire(Param0 p0, Param1 p1) const
	{
		ConnectionsVector const & conns = connections();
		for(ConnectionsVector::const_iterator it = conns.begin(); it != conns.end(); ++it)
		{
			static_cast<ConnectionType const *>(*it)->invoke(p0, p1);
		}
	}
protected:
	typedef Connection2<Param0, Param1, void> ConnectionType;

	EventFireHelper2() {}
	~EventFireHelper2() {}
};

template<class Param0, class Param1, class R = void> class EventRef2;

template<class Param0, class Param1, class R = void> class Event2 : public EventFireHelper2<Param0, Param1, R>
{
public:
	typedef typename EventFireHelper2<Param0, Param1, R>::ConnectionType ConnectionType;

	Event2() {}
	~Event2() {}

	AbstractConnection * addConnection(ConnectionType * conn)
	{
		return AbstractEvent::addConnection(conn);
	}

	inline EventRef2<Param0, Param1, R> bind(void const * sender);
	
	template<class T> inline EventRef2<Param0, Param1, R> bind(T * sender);
};

template<class Param0, class Param1, class R> class EventRef2 : public AbstractEventRef
{
public:
	typedef Event2<Param0, Param1, R> EventType;
	typedef typename EventType::ConnectionType ConnectionType;

	EventRef2(void const * sender, EventType * ev) : AbstractEventRef(sender, ev) {}

	EventRef2<Param0, Param1, R> rebind(void const * newSender) const
	{
		return EventRef2<Param0, Param1, R>(newSender, event_);
	}
	
	template<class T> inline EventRef2<Param0, Param1, R> rebind(T * newSender) const
	{
		return rebind(normalize_cast(newSender));
	}

	template<class T, class Y> AbstractConnection * connect(T * obj, R (Y::*pmf)(Param0 p0, Param1 p1))
	{
		ConnectionType * conn = new ConnectionType(
			senderObject(), senderEvent(), normalize_cast(obj),
			fastdelegate::MakeDelegate(obj, pmf)
		);
		return addConnection(conn);
	}

	template<class T, class Y> AbstractConnection * connect(T const * obj, R (Y::*pmf)(Param0 p0, Param1 p1) const)
	{
		ConnectionType * conn = new ConnectionType(
			senderObject(), senderEvent(), normalize_cast(obj),
			fastdelegate::MakeDelegate(obj, pmf)
		);
		return addConnection(conn);
	}

	template<class T, class Y> AbstractConnection * connect(T * obj, Y pmf)
	{
		detail::ArgList0 stored;
		return connectEx(normalize_cast(obj), fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1> AbstractConnection * connect(T * obj, Y pmf, T1 x1)
	{
		typedef typename StorageType<T1>::Type S1;
		detail::ArgList1<S1> stored(x1);
		return connectEx(normalize_cast(obj), fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2> AbstractConnection * connect(T * obj, Y pmf, T1 x1, T2 x2)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		detail::ArgList2<S1,S2> stored(x1,x2);
		return connectEx(normalize_cast(obj), fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3> AbstractConnection * connect(T * obj, Y pmf, T1 x1, T2 x2, T3 x3)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		detail::ArgList3<S1,S2,S3> stored(x1,x2,x3);
		return connectEx(normalize_cast(obj), fastdelegate::MakeDelegate(obj, pmf), stored);
	}
private:
	AbstractConnection * addConnection(ConnectionType * conn)
	{
		return static_cast<EventType*>(senderEvent())->addConnection(conn);
	}

	template<class DelegateClass, class StoredListClass> AbstractConnection * connectEx(void const * obj, DelegateClass const & deleg, StoredListClass const & stored)
	{
		ConnectionType * conn = new ConnectionEx2<Param0, Param1, R, DelegateClass, StoredListClass>(
			senderObject(), senderEvent(), obj, deleg, stored
		);
		return addConnection(conn);
	}
};

template<class Param0, class Param1, class R> inline EventRef2<Param0, Param1, R> Event2<Param0, Param1, R>::bind(void const * sender)
{
	return EventRef2<Param0, Param1, R>(sender, this);
}

template<class Param0, class Param1, class R> template<class T> inline EventRef2<Param0, Param1, R> Event2<Param0, Param1, R>::bind(T * sender)
{
	return bind(normalize_cast(sender));
}

template<class Param0, class Param1, class Param2, class R> class EventFireHelper3 : public AbstractEvent
{
public:
	typedef Connection3<Param0, Param1, Param2, R> ConnectionType;

	R fire(Param0 p0, Param1 p1, Param2 p2) const
	{
		R retVal;
		ConnectionsVector const & conns = connections();
		for(ConnectionsVector::const_iterator it = conns.begin(); it != conns.end(); ++it)
		{
			retVal = static_cast<ConnectionType const *>(*it)->invoke(p0, p1, p2);
		}
		return retVal;
	}
protected:
	EventFireHelper3() {}
	~EventFireHelper3() {}
};

template<class Param0, class Param1, class Param2> class EventFireHelper3<Param0, Param1, Param2, void> : public AbstractEvent
{
public:
	void fire(Param0 p0, Param1 p1, Param2 p2) const
	{
		ConnectionsVector const & conns = connections();
		for(ConnectionsVector::const_iterator it = conns.begin(); it != conns.end(); ++it)
		{
			static_cast<ConnectionType const *>(*it)->invoke(p0, p1, p2);
		}
	}
protected:
	typedef Connection3<Param0, Param1, Param2, void> ConnectionType;

	EventFireHelper3() {}
	~EventFireHelper3() {}
};

template<class Param0, class Param1, class Param2, class R = void> class EventRef3;

template<class Param0, class Param1, class Param2, class R = void> class Event3 : public EventFireHelper3<Param0, Param1, Param2, R>
{
public:
	typedef typename EventFireHelper3<Param0, Param1, Param2, R>::ConnectionType ConnectionType;

	Event3() {}
	~Event3() {}

	AbstractConnection * addConnection(ConnectionType * conn)
	{
		return AbstractEvent::addConnection(conn);
	}

	inline EventRef3<Param0, Param1, Param2, R> bind(void const * sender);
	
	template<class T> inline EventRef3<Param0, Param1, Param2, R> bind(T * sender);
};

template<class Param0, class Param1, class Param2, class R> class EventRef3 : public AbstractEventRef
{
public:
	typedef Event3<Param0, Param1, Param2, R> EventType;
	typedef typename EventType::ConnectionType ConnectionType;

	EventRef3(void const * sender, EventType * ev) : AbstractEventRef(sender, ev) {}

	EventRef3<Param0, Param1, Param2, R> rebind(void const * newSender) const
	{
		return EventRef3<Param0, Param1, Param2, R>(newSender, event_);
	}
	
	template<class T> inline EventRef3<Param0, Param1, Param2, R> rebind(T * newSender) const
	{
		return rebind(normalize_cast(newSender));
	}

	template<class T, class Y> AbstractConnection * connect(T * obj, R (Y::*pmf)(Param0 p0, Param1 p1, Param2 p2))
	{
		ConnectionType * conn = new ConnectionType(
			senderObject(), senderEvent(), normalize_cast(obj),
			fastdelegate::MakeDelegate(obj, pmf)
		);
		return addConnection(conn);
	}

	template<class T, class Y> AbstractConnection * connect(T const * obj, R (Y::*pmf)(Param0 p0, Param1 p1, Param2 p2) const)
	{
		ConnectionType * conn = new ConnectionType(
			senderObject(), senderEvent(), normalize_cast(obj),
			fastdelegate::MakeDelegate(obj, pmf)
		);
		return addConnection(conn);
	}

	template<class T, class Y> AbstractConnection * connect(T * obj, Y pmf)
	{
		detail::ArgList0 stored;
		return connectEx(normalize_cast(obj), fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1> AbstractConnection * connect(T * obj, Y pmf, T1 x1)
	{
		typedef typename StorageType<T1>::Type S1;
		detail::ArgList1<S1> stored(x1);
		return connectEx(normalize_cast(obj), fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2> AbstractConnection * connect(T * obj, Y pmf, T1 x1, T2 x2)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		detail::ArgList2<S1,S2> stored(x1,x2);
		return connectEx(normalize_cast(obj), fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3> AbstractConnection * connect(T * obj, Y pmf, T1 x1, T2 x2, T3 x3)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		detail::ArgList3<S1,S2,S3> stored(x1,x2,x3);
		return connectEx(normalize_cast(obj), fastdelegate::MakeDelegate(obj, pmf), stored);
	}
private:
	AbstractConnection * addConnection(ConnectionType * conn)
	{
		return static_cast<EventType*>(senderEvent())->addConnection(conn);
	}

	template<class DelegateClass, class StoredListClass> AbstractConnection * connectEx(void const * obj, DelegateClass const & deleg, StoredListClass const & stored)
	{
		ConnectionType * conn = new ConnectionEx3<Param0, Param1, Param2, R, DelegateClass, StoredListClass>(
			senderObject(), senderEvent(), obj, deleg, stored
		);
		return addConnection(conn);
	}
};

template<class Param0, class Param1, class Param2, class R> inline EventRef3<Param0, Param1, Param2, R> Event3<Param0, Param1, Param2, R>::bind(void const * sender)
{
	return EventRef3<Param0, Param1, Param2, R>(sender, this);
}

template<class Param0, class Param1, class Param2, class R> template<class T> inline EventRef3<Param0, Param1, Param2, R> Event3<Param0, Param1, Param2, R>::bind(T * sender)
{
	return bind(normalize_cast(sender));
}

template<class Param0, class Param1, class Param2, class Param3, class R> class EventFireHelper4 : public AbstractEvent
{
public:
	typedef Connection4<Param0, Param1, Param2, Param3, R> ConnectionType;

	R fire(Param0 p0, Param1 p1, Param2 p2, Param3 p3) const
	{
		R retVal;
		ConnectionsVector const & conns = connections();
		for(ConnectionsVector::const_iterator it = conns.begin(); it != conns.end(); ++it)
		{
			retVal = static_cast<ConnectionType const *>(*it)->invoke(p0, p1, p2, p3);
		}
		return retVal;
	}
protected:
	EventFireHelper4() {}
	~EventFireHelper4() {}
};

template<class Param0, class Param1, class Param2, class Param3> class EventFireHelper4<Param0, Param1, Param2, Param3, void> : public AbstractEvent
{
public:
	void fire(Param0 p0, Param1 p1, Param2 p2, Param3 p3) const
	{
		ConnectionsVector const & conns = connections();
		for(ConnectionsVector::const_iterator it = conns.begin(); it != conns.end(); ++it)
		{
			static_cast<ConnectionType const *>(*it)->invoke(p0, p1, p2, p3);
		}
	}
protected:
	typedef Connection4<Param0, Param1, Param2, Param3, void> ConnectionType;

	EventFireHelper4() {}
	~EventFireHelper4() {}
};

template<class Param0, class Param1, class Param2, class Param3, class R = void> class EventRef4;

template<class Param0, class Param1, class Param2, class Param3, class R = void> class Event4 : public EventFireHelper4<Param0, Param1, Param2, Param3, R>
{
public:
	typedef typename EventFireHelper4<Param0, Param1, Param2, Param3, R>::ConnectionType ConnectionType;

	Event4() {}
	~Event4() {}

	AbstractConnection * addConnection(ConnectionType * conn)
	{
		return AbstractEvent::addConnection(conn);
	}

	inline EventRef4<Param0, Param1, Param2, Param3, R> bind(void const * sender);
	
	template<class T> inline EventRef4<Param0, Param1, Param2, Param3, R> bind(T * sender);
};

template<class Param0, class Param1, class Param2, class Param3, class R> class EventRef4 : public AbstractEventRef
{
public:
	typedef Event4<Param0, Param1, Param2, Param3, R> EventType;
	typedef typename EventType::ConnectionType ConnectionType;

	EventRef4(void const * sender, EventType * ev) : AbstractEventRef(sender, ev) {}

	EventRef4<Param0, Param1, Param2, Param3, R> rebind(void const * newSender) const
	{
		return EventRef4<Param0, Param1, Param2, Param3, R>(newSender, event_);
	}
	
	template<class T> inline EventRef4<Param0, Param1, Param2, Param3, R> rebind(T * newSender) const
	{
		return rebind(normalize_cast(newSender));
	}

	template<class T, class Y> AbstractConnection * connect(T * obj, R (Y::*pmf)(Param0 p0, Param1 p1, Param2 p2, Param3 p3))
	{
		ConnectionType * conn = new ConnectionType(
			senderObject(), senderEvent(), normalize_cast(obj),
			fastdelegate::MakeDelegate(obj, pmf)
		);
		return addConnection(conn);
	}

	template<class T, class Y> AbstractConnection * connect(T const * obj, R (Y::*pmf)(Param0 p0, Param1 p1, Param2 p2, Param3 p3) const)
	{
		ConnectionType * conn = new ConnectionType(
			senderObject(), senderEvent(), normalize_cast(obj),
			fastdelegate::MakeDelegate(obj, pmf)
		);
		return addConnection(conn);
	}

	template<class T, class Y> AbstractConnection * connect(T * obj, Y pmf)
	{
		detail::ArgList0 stored;
		return connectEx(normalize_cast(obj), fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1> AbstractConnection * connect(T * obj, Y pmf, T1 x1)
	{
		typedef typename StorageType<T1>::Type S1;
		detail::ArgList1<S1> stored(x1);
		return connectEx(normalize_cast(obj), fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2> AbstractConnection * connect(T * obj, Y pmf, T1 x1, T2 x2)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		detail::ArgList2<S1,S2> stored(x1,x2);
		return connectEx(normalize_cast(obj), fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3> AbstractConnection * connect(T * obj, Y pmf, T1 x1, T2 x2, T3 x3)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		detail::ArgList3<S1,S2,S3> stored(x1,x2,x3);
		return connectEx(normalize_cast(obj), fastdelegate::MakeDelegate(obj, pmf), stored);
	}
private:
	AbstractConnection * addConnection(ConnectionType * conn)
	{
		return static_cast<EventType*>(senderEvent())->addConnection(conn);
	}

	template<class DelegateClass, class StoredListClass> AbstractConnection * connectEx(void const * obj, DelegateClass const & deleg, StoredListClass const & stored)
	{
		ConnectionType * conn = new ConnectionEx4<Param0, Param1, Param2, Param3, R, DelegateClass, StoredListClass>(
			senderObject(), senderEvent(), obj, deleg, stored
		);
		return addConnection(conn);
	}
};

template<class Param0, class Param1, class Param2, class Param3, class R> inline EventRef4<Param0, Param1, Param2, Param3, R> Event4<Param0, Param1, Param2, Param3, R>::bind(void const * sender)
{
	return EventRef4<Param0, Param1, Param2, Param3, R>(sender, this);
}

template<class Param0, class Param1, class Param2, class Param3, class R> template<class T> inline EventRef4<Param0, Param1, Param2, Param3, R> Event4<Param0, Param1, Param2, Param3, R>::bind(T * sender)
{
	return bind(normalize_cast(sender));
}

template<class Param0, class Param1, class Param2, class Param3, class Param4, class R> class EventFireHelper5 : public AbstractEvent
{
public:
	typedef Connection5<Param0, Param1, Param2, Param3, Param4, R> ConnectionType;

	R fire(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4) const
	{
		R retVal;
		ConnectionsVector const & conns = connections();
		for(ConnectionsVector::const_iterator it = conns.begin(); it != conns.end(); ++it)
		{
			retVal = static_cast<ConnectionType const *>(*it)->invoke(p0, p1, p2, p3, p4);
		}
		return retVal;
	}
protected:
	EventFireHelper5() {}
	~EventFireHelper5() {}
};

template<class Param0, class Param1, class Param2, class Param3, class Param4> class EventFireHelper5<Param0, Param1, Param2, Param3, Param4, void> : public AbstractEvent
{
public:
	void fire(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4) const
	{
		ConnectionsVector const & conns = connections();
		for(ConnectionsVector::const_iterator it = conns.begin(); it != conns.end(); ++it)
		{
			static_cast<ConnectionType const *>(*it)->invoke(p0, p1, p2, p3, p4);
		}
	}
protected:
	typedef Connection5<Param0, Param1, Param2, Param3, Param4, void> ConnectionType;

	EventFireHelper5() {}
	~EventFireHelper5() {}
};

template<class Param0, class Param1, class Param2, class Param3, class Param4, class R = void> class EventRef5;

template<class Param0, class Param1, class Param2, class Param3, class Param4, class R = void> class Event5 : public EventFireHelper5<Param0, Param1, Param2, Param3, Param4, R>
{
public:
	typedef typename EventFireHelper5<Param0, Param1, Param2, Param3, Param4, R>::ConnectionType ConnectionType;

	Event5() {}
	~Event5() {}

	AbstractConnection * addConnection(ConnectionType * conn)
	{
		return AbstractEvent::addConnection(conn);
	}

	inline EventRef5<Param0, Param1, Param2, Param3, Param4, R> bind(void const * sender);
	
	template<class T> inline EventRef5<Param0, Param1, Param2, Param3, Param4, R> bind(T * sender);
};

template<class Param0, class Param1, class Param2, class Param3, class Param4, class R> class EventRef5 : public AbstractEventRef
{
public:
	typedef Event5<Param0, Param1, Param2, Param3, Param4, R> EventType;
	typedef typename EventType::ConnectionType ConnectionType;

	EventRef5(void const * sender, EventType * ev) : AbstractEventRef(sender, ev) {}

	EventRef5<Param0, Param1, Param2, Param3, Param4, R> rebind(void const * newSender) const
	{
		return EventRef5<Param0, Param1, Param2, Param3, Param4, R>(newSender, event_);
	}
	
	template<class T> inline EventRef5<Param0, Param1, Param2, Param3, Param4, R> rebind(T * newSender) const
	{
		return rebind(normalize_cast(newSender));
	}

	template<class T, class Y> AbstractConnection * connect(T * obj, R (Y::*pmf)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4))
	{
		ConnectionType * conn = new ConnectionType(
			senderObject(), senderEvent(), normalize_cast(obj),
			fastdelegate::MakeDelegate(obj, pmf)
		);
		return addConnection(conn);
	}

	template<class T, class Y> AbstractConnection * connect(T const * obj, R (Y::*pmf)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4) const)
	{
		ConnectionType * conn = new ConnectionType(
			senderObject(), senderEvent(), normalize_cast(obj),
			fastdelegate::MakeDelegate(obj, pmf)
		);
		return addConnection(conn);
	}

	template<class T, class Y> AbstractConnection * connect(T * obj, Y pmf)
	{
		detail::ArgList0 stored;
		return connectEx(normalize_cast(obj), fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1> AbstractConnection * connect(T * obj, Y pmf, T1 x1)
	{
		typedef typename StorageType<T1>::Type S1;
		detail::ArgList1<S1> stored(x1);
		return connectEx(normalize_cast(obj), fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2> AbstractConnection * connect(T * obj, Y pmf, T1 x1, T2 x2)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		detail::ArgList2<S1,S2> stored(x1,x2);
		return connectEx(normalize_cast(obj), fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3> AbstractConnection * connect(T * obj, Y pmf, T1 x1, T2 x2, T3 x3)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		detail::ArgList3<S1,S2,S3> stored(x1,x2,x3);
		return connectEx(normalize_cast(obj), fastdelegate::MakeDelegate(obj, pmf), stored);
	}
private:
	AbstractConnection * addConnection(ConnectionType * conn)
	{
		return static_cast<EventType*>(senderEvent())->addConnection(conn);
	}

	template<class DelegateClass, class StoredListClass> AbstractConnection * connectEx(void const * obj, DelegateClass const & deleg, StoredListClass const & stored)
	{
		ConnectionType * conn = new ConnectionEx5<Param0, Param1, Param2, Param3, Param4, R, DelegateClass, StoredListClass>(
			senderObject(), senderEvent(), obj, deleg, stored
		);
		return addConnection(conn);
	}
};

template<class Param0, class Param1, class Param2, class Param3, class Param4, class R> inline EventRef5<Param0, Param1, Param2, Param3, Param4, R> Event5<Param0, Param1, Param2, Param3, Param4, R>::bind(void const * sender)
{
	return EventRef5<Param0, Param1, Param2, Param3, Param4, R>(sender, this);
}

template<class Param0, class Param1, class Param2, class Param3, class Param4, class R> template<class T> inline EventRef5<Param0, Param1, Param2, Param3, Param4, R> Event5<Param0, Param1, Param2, Param3, Param4, R>::bind(T * sender)
{
	return bind(normalize_cast(sender));
}

template<class Param0, class Param1, class Param2, class Param3, class Param4, class Param5, class R> class EventFireHelper6 : public AbstractEvent
{
public:
	typedef Connection6<Param0, Param1, Param2, Param3, Param4, Param5, R> ConnectionType;

	R fire(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) const
	{
		R retVal;
		ConnectionsVector const & conns = connections();
		for(ConnectionsVector::const_iterator it = conns.begin(); it != conns.end(); ++it)
		{
			retVal = static_cast<ConnectionType const *>(*it)->invoke(p0, p1, p2, p3, p4, p5);
		}
		return retVal;
	}
protected:
	EventFireHelper6() {}
	~EventFireHelper6() {}
};

template<class Param0, class Param1, class Param2, class Param3, class Param4, class Param5> class EventFireHelper6<Param0, Param1, Param2, Param3, Param4, Param5, void> : public AbstractEvent
{
public:
	void fire(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) const
	{
		ConnectionsVector const & conns = connections();
		for(ConnectionsVector::const_iterator it = conns.begin(); it != conns.end(); ++it)
		{
			static_cast<ConnectionType const *>(*it)->invoke(p0, p1, p2, p3, p4, p5);
		}
	}
protected:
	typedef Connection6<Param0, Param1, Param2, Param3, Param4, Param5, void> ConnectionType;

	EventFireHelper6() {}
	~EventFireHelper6() {}
};

template<class Param0, class Param1, class Param2, class Param3, class Param4, class Param5, class R = void> class EventRef6;

template<class Param0, class Param1, class Param2, class Param3, class Param4, class Param5, class R = void> class Event6 : public EventFireHelper6<Param0, Param1, Param2, Param3, Param4, Param5, R>
{
public:
	typedef typename EventFireHelper6<Param0, Param1, Param2, Param3, Param4, Param5, R>::ConnectionType ConnectionType;

	Event6() {}
	~Event6() {}

	AbstractConnection * addConnection(ConnectionType * conn)
	{
		return AbstractEvent::addConnection(conn);
	}

	inline EventRef6<Param0, Param1, Param2, Param3, Param4, Param5, R> bind(void const * sender);
	
	template<class T> inline EventRef6<Param0, Param1, Param2, Param3, Param4, Param5, R> bind(T * sender);
};

template<class Param0, class Param1, class Param2, class Param3, class Param4, class Param5, class R> class EventRef6 : public AbstractEventRef
{
public:
	typedef Event6<Param0, Param1, Param2, Param3, Param4, Param5, R> EventType;
	typedef typename EventType::ConnectionType ConnectionType;

	EventRef6(void const * sender, EventType * ev) : AbstractEventRef(sender, ev) {}

	EventRef6<Param0, Param1, Param2, Param3, Param4, Param5, R> rebind(void const * newSender) const
	{
		return EventRef6<Param0, Param1, Param2, Param3, Param4, Param5, R>(newSender, event_);
	}
	
	template<class T> inline EventRef6<Param0, Param1, Param2, Param3, Param4, Param5, R> rebind(T * newSender) const
	{
		return rebind(normalize_cast(newSender));
	}

	template<class T, class Y> AbstractConnection * connect(T * obj, R (Y::*pmf)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5))
	{
		ConnectionType * conn = new ConnectionType(
			senderObject(), senderEvent(), normalize_cast(obj),
			fastdelegate::MakeDelegate(obj, pmf)
		);
		return addConnection(conn);
	}

	template<class T, class Y> AbstractConnection * connect(T const * obj, R (Y::*pmf)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) const)
	{
		ConnectionType * conn = new ConnectionType(
			senderObject(), senderEvent(), normalize_cast(obj),
			fastdelegate::MakeDelegate(obj, pmf)
		);
		return addConnection(conn);
	}

	template<class T, class Y> AbstractConnection * connect(T * obj, Y pmf)
	{
		detail::ArgList0 stored;
		return connectEx(normalize_cast(obj), fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1> AbstractConnection * connect(T * obj, Y pmf, T1 x1)
	{
		typedef typename StorageType<T1>::Type S1;
		detail::ArgList1<S1> stored(x1);
		return connectEx(normalize_cast(obj), fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2> AbstractConnection * connect(T * obj, Y pmf, T1 x1, T2 x2)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		detail::ArgList2<S1,S2> stored(x1,x2);
		return connectEx(normalize_cast(obj), fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3> AbstractConnection * connect(T * obj, Y pmf, T1 x1, T2 x2, T3 x3)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		detail::ArgList3<S1,S2,S3> stored(x1,x2,x3);
		return connectEx(normalize_cast(obj), fastdelegate::MakeDelegate(obj, pmf), stored);
	}
private:
	AbstractConnection * addConnection(ConnectionType * conn)
	{
		return static_cast<EventType*>(senderEvent())->addConnection(conn);
	}

	template<class DelegateClass, class StoredListClass> AbstractConnection * connectEx(void const * obj, DelegateClass const & deleg, StoredListClass const & stored)
	{
		ConnectionType * conn = new ConnectionEx6<Param0, Param1, Param2, Param3, Param4, Param5, R, DelegateClass, StoredListClass>(
			senderObject(), senderEvent(), obj, deleg, stored
		);
		return addConnection(conn);
	}
};

template<class Param0, class Param1, class Param2, class Param3, class Param4, class Param5, class R> inline EventRef6<Param0, Param1, Param2, Param3, Param4, Param5, R> Event6<Param0, Param1, Param2, Param3, Param4, Param5, R>::bind(void const * sender)
{
	return EventRef6<Param0, Param1, Param2, Param3, Param4, Param5, R>(sender, this);
}

template<class Param0, class Param1, class Param2, class Param3, class Param4, class Param5, class R> template<class T> inline EventRef6<Param0, Param1, Param2, Param3, Param4, Param5, R> Event6<Param0, Param1, Param2, Param3, Param4, Param5, R>::bind(T * sender)
{
	return bind(normalize_cast(sender));
}

template<class Param0, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class R> class EventFireHelper7 : public AbstractEvent
{
public:
	typedef Connection7<Param0, Param1, Param2, Param3, Param4, Param5, Param6, R> ConnectionType;

	R fire(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6) const
	{
		R retVal;
		ConnectionsVector const & conns = connections();
		for(ConnectionsVector::const_iterator it = conns.begin(); it != conns.end(); ++it)
		{
			retVal = static_cast<ConnectionType const *>(*it)->invoke(p0, p1, p2, p3, p4, p5, p6);
		}
		return retVal;
	}
protected:
	EventFireHelper7() {}
	~EventFireHelper7() {}
};

template<class Param0, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6> class EventFireHelper7<Param0, Param1, Param2, Param3, Param4, Param5, Param6, void> : public AbstractEvent
{
public:
	void fire(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6) const
	{
		ConnectionsVector const & conns = connections();
		for(ConnectionsVector::const_iterator it = conns.begin(); it != conns.end(); ++it)
		{
			static_cast<ConnectionType const *>(*it)->invoke(p0, p1, p2, p3, p4, p5, p6);
		}
	}
protected:
	typedef Connection7<Param0, Param1, Param2, Param3, Param4, Param5, Param6, void> ConnectionType;

	EventFireHelper7() {}
	~EventFireHelper7() {}
};

template<class Param0, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class R = void> class EventRef7;

template<class Param0, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class R = void> class Event7 : public EventFireHelper7<Param0, Param1, Param2, Param3, Param4, Param5, Param6, R>
{
public:
	typedef typename EventFireHelper7<Param0, Param1, Param2, Param3, Param4, Param5, Param6, R>::ConnectionType ConnectionType;

	Event7() {}
	~Event7() {}

	AbstractConnection * addConnection(ConnectionType * conn)
	{
		return AbstractEvent::addConnection(conn);
	}

	inline EventRef7<Param0, Param1, Param2, Param3, Param4, Param5, Param6, R> bind(void const * sender);
	
	template<class T> inline EventRef7<Param0, Param1, Param2, Param3, Param4, Param5, Param6, R> bind(T * sender);
};

template<class Param0, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class R> class EventRef7 : public AbstractEventRef
{
public:
	typedef Event7<Param0, Param1, Param2, Param3, Param4, Param5, Param6, R> EventType;
	typedef typename EventType::ConnectionType ConnectionType;

	EventRef7(void const * sender, EventType * ev) : AbstractEventRef(sender, ev) {}

	EventRef7<Param0, Param1, Param2, Param3, Param4, Param5, Param6, R> rebind(void const * newSender) const
	{
		return EventRef7<Param0, Param1, Param2, Param3, Param4, Param5, Param6, R>(newSender, event_);
	}
	
	template<class T> inline EventRef7<Param0, Param1, Param2, Param3, Param4, Param5, Param6, R> rebind(T * newSender) const
	{
		return rebind(normalize_cast(newSender));
	}

	template<class T, class Y> AbstractConnection * connect(T * obj, R (Y::*pmf)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6))
	{
		ConnectionType * conn = new ConnectionType(
			senderObject(), senderEvent(), normalize_cast(obj),
			fastdelegate::MakeDelegate(obj, pmf)
		);
		return addConnection(conn);
	}

	template<class T, class Y> AbstractConnection * connect(T const * obj, R (Y::*pmf)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6) const)
	{
		ConnectionType * conn = new ConnectionType(
			senderObject(), senderEvent(), normalize_cast(obj),
			fastdelegate::MakeDelegate(obj, pmf)
		);
		return addConnection(conn);
	}

	template<class T, class Y> AbstractConnection * connect(T * obj, Y pmf)
	{
		detail::ArgList0 stored;
		return connectEx(normalize_cast(obj), fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1> AbstractConnection * connect(T * obj, Y pmf, T1 x1)
	{
		typedef typename StorageType<T1>::Type S1;
		detail::ArgList1<S1> stored(x1);
		return connectEx(normalize_cast(obj), fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2> AbstractConnection * connect(T * obj, Y pmf, T1 x1, T2 x2)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		detail::ArgList2<S1,S2> stored(x1,x2);
		return connectEx(normalize_cast(obj), fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3> AbstractConnection * connect(T * obj, Y pmf, T1 x1, T2 x2, T3 x3)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		detail::ArgList3<S1,S2,S3> stored(x1,x2,x3);
		return connectEx(normalize_cast(obj), fastdelegate::MakeDelegate(obj, pmf), stored);
	}
private:
	AbstractConnection * addConnection(ConnectionType * conn)
	{
		return static_cast<EventType*>(senderEvent())->addConnection(conn);
	}

	template<class DelegateClass, class StoredListClass> AbstractConnection * connectEx(void const * obj, DelegateClass const & deleg, StoredListClass const & stored)
	{
		ConnectionType * conn = new ConnectionEx7<Param0, Param1, Param2, Param3, Param4, Param5, Param6, R, DelegateClass, StoredListClass>(
			senderObject(), senderEvent(), obj, deleg, stored
		);
		return addConnection(conn);
	}
};

template<class Param0, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class R> inline EventRef7<Param0, Param1, Param2, Param3, Param4, Param5, Param6, R> Event7<Param0, Param1, Param2, Param3, Param4, Param5, Param6, R>::bind(void const * sender)
{
	return EventRef7<Param0, Param1, Param2, Param3, Param4, Param5, Param6, R>(sender, this);
}

template<class Param0, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class R> template<class T> inline EventRef7<Param0, Param1, Param2, Param3, Param4, Param5, Param6, R> Event7<Param0, Param1, Param2, Param3, Param4, Param5, Param6, R>::bind(T * sender)
{
	return bind(normalize_cast(sender));
}

#endif //EVENTS_H