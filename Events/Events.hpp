#ifndef EVENTS_HPP
#define EVENTS_HPP

#include "AbstractEvent.hpp"
#include "ExtraDelegateData.hpp"
#include "TypeTraits.hpp"

class Event0 : public AbstractEvent
{
public:
	typedef fastdelegate::FastDelegate0<void> DelegateType;

	Event0() {}
	~Event0() {}

	void addConnection(ConnectionList * tracker, DelegateType const & deleg, ExtraDelegateData * data)
	{
		AbstractEvent::addConnection(tracker, deleg, data);
	}
	
	void fire() const
	{
		FireLock lock(this);
		ConnectionsVector const & conns = lock.connections();
		for(ConnectionsVector::const_iterator it = conns.begin(); it != conns.end(); ++it)
		{
			DelegateType deleg = it->delegate_.castToDelegate<DelegateType>();
			deleg();
		}
	}
};

class EventRef0 : public AbstractEventRef
{
public:
	typedef Event0 EventType;
	typedef EventType::DelegateType DelegateType;

	EventRef0(EventType * ev) : AbstractEventRef(ev) {}
	
	EventType * senderEvent() const
	{
		return static_cast<EventType*>(AbstractEventRef::senderEvent());
	}

	template<class T, class Y> void connect(ConnectionList * tracker, T * obj, void (Y::*pmf)())
	{
		addConnection(tracker, fastdelegate::MakeDelegate(obj, pmf), 0);
	}

	template<class T, class Y> void connect(ConnectionList * tracker, T const * obj, void (Y::*pmf)() const)
	{
		addConnection(tracker, fastdelegate::MakeDelegate(obj, pmf), 0);
	}

	template<class T, class Y> void connect(ConnectionList * tracker, T * obj, Y pmf)
	{
		detail::ArgList0 stored;
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1)
	{
		typedef typename StorageType<T1>::Type S1;
		detail::ArgList1<S1> stored(x1);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		detail::ArgList2<S1, S2> stored(x1, x2);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2, T3 x3)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		detail::ArgList3<S1, S2, S3> stored(x1, x2, x3);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3, class T4> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2, T3 x3, T4 x4)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		typedef typename StorageType<T4>::Type S4;
		detail::ArgList4<S1, S2, S3, S4> stored(x1, x2, x3, x4);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3, class T4, class T5> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2, T3 x3, T4 x4, T5 x5)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		typedef typename StorageType<T4>::Type S4;
		typedef typename StorageType<T5>::Type S5;
		detail::ArgList5<S1, S2, S3, S4, S5> stored(x1, x2, x3, x4, x5);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3, class T4, class T5, class T6> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2, T3 x3, T4 x4, T5 x5, T6 x6)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		typedef typename StorageType<T4>::Type S4;
		typedef typename StorageType<T5>::Type S5;
		typedef typename StorageType<T6>::Type S6;
		detail::ArgList6<S1, S2, S3, S4, S5, S6> stored(x1, x2, x3, x4, x5, x6);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3, class T4, class T5, class T6, class T7> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2, T3 x3, T4 x4, T5 x5, T6 x6, T7 x7)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		typedef typename StorageType<T4>::Type S4;
		typedef typename StorageType<T5>::Type S5;
		typedef typename StorageType<T6>::Type S6;
		typedef typename StorageType<T7>::Type S7;
		detail::ArgList7<S1, S2, S3, S4, S5, S6, S7> stored(x1, x2, x3, x4, x5, x6, x7);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

private:
	void addConnection(ConnectionList * tracker, DelegateType const & deleg, ExtraDelegateData * data)
	{
		senderEvent()->addConnection(tracker, deleg, data);
	}

	template<class DelegateClass, class StoredListClass> void connectEx(ConnectionList * tracker, DelegateClass const & deleg, StoredListClass const & stored)
	{
		typedef ExtraDelegateData0<DelegateClass, StoredListClass> ExtraDelegateDataType;
		ExtraDelegateDataType * data = new ExtraDelegateDataType(deleg, stored);
		addConnection(tracker, fastdelegate::MakeDelegate(data, &ExtraDelegateDataType::invokeHelper), data);
	}
};

template<class Param0> class Event1 : public AbstractEvent
{
public:
	typedef fastdelegate::FastDelegate1<Param0, void> DelegateType;

	Event1() {}
	~Event1() {}

	void addConnection(ConnectionList * tracker, DelegateType const & deleg, ExtraDelegateData * data)
	{
		AbstractEvent::addConnection(tracker, deleg, data);
	}
	
	void fire(Param0 p0) const
	{
		FireLock lock(this);
		ConnectionsVector const & conns = lock.connections();
		for(ConnectionsVector::const_iterator it = conns.begin(); it != conns.end(); ++it)
		{
			DelegateType deleg = it->delegate_.castToDelegate<DelegateType>();
			deleg(p0);
		}
	}
};

template<class Param0> class EventRef1 : public AbstractEventRef
{
public:
	typedef Event1<Param0> EventType;
	typedef typename EventType::DelegateType DelegateType;

	EventRef1(EventType * ev) : AbstractEventRef(ev) {}
	
	EventType * senderEvent() const
	{
		return static_cast<EventType*>(AbstractEventRef::senderEvent());
	}

	template<class T, class Y> void connect(ConnectionList * tracker, T * obj, void (Y::*pmf)(Param0 p0))
	{
		addConnection(tracker, fastdelegate::MakeDelegate(obj, pmf), 0);
	}

	template<class T, class Y> void connect(ConnectionList * tracker, T const * obj, void (Y::*pmf)(Param0 p0) const)
	{
		addConnection(tracker, fastdelegate::MakeDelegate(obj, pmf), 0);
	}

	template<class T, class Y> void connect(ConnectionList * tracker, T * obj, Y pmf)
	{
		detail::ArgList0 stored;
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1)
	{
		typedef typename StorageType<T1>::Type S1;
		detail::ArgList1<S1> stored(x1);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		detail::ArgList2<S1, S2> stored(x1, x2);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2, T3 x3)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		detail::ArgList3<S1, S2, S3> stored(x1, x2, x3);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3, class T4> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2, T3 x3, T4 x4)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		typedef typename StorageType<T4>::Type S4;
		detail::ArgList4<S1, S2, S3, S4> stored(x1, x2, x3, x4);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3, class T4, class T5> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2, T3 x3, T4 x4, T5 x5)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		typedef typename StorageType<T4>::Type S4;
		typedef typename StorageType<T5>::Type S5;
		detail::ArgList5<S1, S2, S3, S4, S5> stored(x1, x2, x3, x4, x5);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3, class T4, class T5, class T6> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2, T3 x3, T4 x4, T5 x5, T6 x6)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		typedef typename StorageType<T4>::Type S4;
		typedef typename StorageType<T5>::Type S5;
		typedef typename StorageType<T6>::Type S6;
		detail::ArgList6<S1, S2, S3, S4, S5, S6> stored(x1, x2, x3, x4, x5, x6);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3, class T4, class T5, class T6, class T7> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2, T3 x3, T4 x4, T5 x5, T6 x6, T7 x7)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		typedef typename StorageType<T4>::Type S4;
		typedef typename StorageType<T5>::Type S5;
		typedef typename StorageType<T6>::Type S6;
		typedef typename StorageType<T7>::Type S7;
		detail::ArgList7<S1, S2, S3, S4, S5, S6, S7> stored(x1, x2, x3, x4, x5, x6, x7);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

private:
	void addConnection(ConnectionList * tracker, DelegateType const & deleg, ExtraDelegateData * data)
	{
		senderEvent()->addConnection(tracker, deleg, data);
	}

	template<class DelegateClass, class StoredListClass> void connectEx(ConnectionList * tracker, DelegateClass const & deleg, StoredListClass const & stored)
	{
		typedef ExtraDelegateData1<Param0, DelegateClass, StoredListClass> ExtraDelegateDataType;
		ExtraDelegateDataType * data = new ExtraDelegateDataType(deleg, stored);
		addConnection(tracker, fastdelegate::MakeDelegate(data, &ExtraDelegateDataType::invokeHelper), data);
	}
};

template<class Param0, class Param1> class Event2 : public AbstractEvent
{
public:
	typedef fastdelegate::FastDelegate2<Param0, Param1, void> DelegateType;

	Event2() {}
	~Event2() {}

	void addConnection(ConnectionList * tracker, DelegateType const & deleg, ExtraDelegateData * data)
	{
		AbstractEvent::addConnection(tracker, deleg, data);
	}
	
	void fire(Param0 p0, Param1 p1) const
	{
		FireLock lock(this);
		ConnectionsVector const & conns = lock.connections();
		for(ConnectionsVector::const_iterator it = conns.begin(); it != conns.end(); ++it)
		{
			DelegateType deleg = it->delegate_.castToDelegate<DelegateType>();
			deleg(p0, p1);
		}
	}
};

template<class Param0, class Param1> class EventRef2 : public AbstractEventRef
{
public:
	typedef Event2<Param0, Param1> EventType;
	typedef typename EventType::DelegateType DelegateType;

	EventRef2(EventType * ev) : AbstractEventRef(ev) {}
	
	EventType * senderEvent() const
	{
		return static_cast<EventType*>(AbstractEventRef::senderEvent());
	}

	template<class T, class Y> void connect(ConnectionList * tracker, T * obj, void (Y::*pmf)(Param0 p0, Param1 p1))
	{
		addConnection(tracker, fastdelegate::MakeDelegate(obj, pmf), 0);
	}

	template<class T, class Y> void connect(ConnectionList * tracker, T const * obj, void (Y::*pmf)(Param0 p0, Param1 p1) const)
	{
		addConnection(tracker, fastdelegate::MakeDelegate(obj, pmf), 0);
	}

	template<class T, class Y> void connect(ConnectionList * tracker, T * obj, Y pmf)
	{
		detail::ArgList0 stored;
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1)
	{
		typedef typename StorageType<T1>::Type S1;
		detail::ArgList1<S1> stored(x1);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		detail::ArgList2<S1, S2> stored(x1, x2);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2, T3 x3)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		detail::ArgList3<S1, S2, S3> stored(x1, x2, x3);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3, class T4> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2, T3 x3, T4 x4)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		typedef typename StorageType<T4>::Type S4;
		detail::ArgList4<S1, S2, S3, S4> stored(x1, x2, x3, x4);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3, class T4, class T5> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2, T3 x3, T4 x4, T5 x5)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		typedef typename StorageType<T4>::Type S4;
		typedef typename StorageType<T5>::Type S5;
		detail::ArgList5<S1, S2, S3, S4, S5> stored(x1, x2, x3, x4, x5);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3, class T4, class T5, class T6> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2, T3 x3, T4 x4, T5 x5, T6 x6)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		typedef typename StorageType<T4>::Type S4;
		typedef typename StorageType<T5>::Type S5;
		typedef typename StorageType<T6>::Type S6;
		detail::ArgList6<S1, S2, S3, S4, S5, S6> stored(x1, x2, x3, x4, x5, x6);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3, class T4, class T5, class T6, class T7> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2, T3 x3, T4 x4, T5 x5, T6 x6, T7 x7)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		typedef typename StorageType<T4>::Type S4;
		typedef typename StorageType<T5>::Type S5;
		typedef typename StorageType<T6>::Type S6;
		typedef typename StorageType<T7>::Type S7;
		detail::ArgList7<S1, S2, S3, S4, S5, S6, S7> stored(x1, x2, x3, x4, x5, x6, x7);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

private:
	void addConnection(ConnectionList * tracker, DelegateType const & deleg, ExtraDelegateData * data)
	{
		senderEvent()->addConnection(tracker, deleg, data);
	}

	template<class DelegateClass, class StoredListClass> void connectEx(ConnectionList * tracker, DelegateClass const & deleg, StoredListClass const & stored)
	{
		typedef ExtraDelegateData2<Param0, Param1, DelegateClass, StoredListClass> ExtraDelegateDataType;
		ExtraDelegateDataType * data = new ExtraDelegateDataType(deleg, stored);
		addConnection(tracker, fastdelegate::MakeDelegate(data, &ExtraDelegateDataType::invokeHelper), data);
	}
};

template<class Param0, class Param1, class Param2> class Event3 : public AbstractEvent
{
public:
	typedef fastdelegate::FastDelegate3<Param0, Param1, Param2, void> DelegateType;

	Event3() {}
	~Event3() {}

	void addConnection(ConnectionList * tracker, DelegateType const & deleg, ExtraDelegateData * data)
	{
		AbstractEvent::addConnection(tracker, deleg, data);
	}
	
	void fire(Param0 p0, Param1 p1, Param2 p2) const
	{
		FireLock lock(this);
		ConnectionsVector const & conns = lock.connections();
		for(ConnectionsVector::const_iterator it = conns.begin(); it != conns.end(); ++it)
		{
			DelegateType deleg = it->delegate_.castToDelegate<DelegateType>();
			deleg(p0, p1, p2);
		}
	}
};

template<class Param0, class Param1, class Param2> class EventRef3 : public AbstractEventRef
{
public:
	typedef Event3<Param0, Param1, Param2> EventType;
	typedef typename EventType::DelegateType DelegateType;

	EventRef3(EventType * ev) : AbstractEventRef(ev) {}
	
	EventType * senderEvent() const
	{
		return static_cast<EventType*>(AbstractEventRef::senderEvent());
	}

	template<class T, class Y> void connect(ConnectionList * tracker, T * obj, void (Y::*pmf)(Param0 p0, Param1 p1, Param2 p2))
	{
		addConnection(tracker, fastdelegate::MakeDelegate(obj, pmf), 0);
	}

	template<class T, class Y> void connect(ConnectionList * tracker, T const * obj, void (Y::*pmf)(Param0 p0, Param1 p1, Param2 p2) const)
	{
		addConnection(tracker, fastdelegate::MakeDelegate(obj, pmf), 0);
	}

	template<class T, class Y> void connect(ConnectionList * tracker, T * obj, Y pmf)
	{
		detail::ArgList0 stored;
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1)
	{
		typedef typename StorageType<T1>::Type S1;
		detail::ArgList1<S1> stored(x1);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		detail::ArgList2<S1, S2> stored(x1, x2);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2, T3 x3)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		detail::ArgList3<S1, S2, S3> stored(x1, x2, x3);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3, class T4> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2, T3 x3, T4 x4)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		typedef typename StorageType<T4>::Type S4;
		detail::ArgList4<S1, S2, S3, S4> stored(x1, x2, x3, x4);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3, class T4, class T5> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2, T3 x3, T4 x4, T5 x5)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		typedef typename StorageType<T4>::Type S4;
		typedef typename StorageType<T5>::Type S5;
		detail::ArgList5<S1, S2, S3, S4, S5> stored(x1, x2, x3, x4, x5);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3, class T4, class T5, class T6> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2, T3 x3, T4 x4, T5 x5, T6 x6)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		typedef typename StorageType<T4>::Type S4;
		typedef typename StorageType<T5>::Type S5;
		typedef typename StorageType<T6>::Type S6;
		detail::ArgList6<S1, S2, S3, S4, S5, S6> stored(x1, x2, x3, x4, x5, x6);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3, class T4, class T5, class T6, class T7> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2, T3 x3, T4 x4, T5 x5, T6 x6, T7 x7)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		typedef typename StorageType<T4>::Type S4;
		typedef typename StorageType<T5>::Type S5;
		typedef typename StorageType<T6>::Type S6;
		typedef typename StorageType<T7>::Type S7;
		detail::ArgList7<S1, S2, S3, S4, S5, S6, S7> stored(x1, x2, x3, x4, x5, x6, x7);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

private:
	void addConnection(ConnectionList * tracker, DelegateType const & deleg, ExtraDelegateData * data)
	{
		senderEvent()->addConnection(tracker, deleg, data);
	}

	template<class DelegateClass, class StoredListClass> void connectEx(ConnectionList * tracker, DelegateClass const & deleg, StoredListClass const & stored)
	{
		typedef ExtraDelegateData3<Param0, Param1, Param2, DelegateClass, StoredListClass> ExtraDelegateDataType;
		ExtraDelegateDataType * data = new ExtraDelegateDataType(deleg, stored);
		addConnection(tracker, fastdelegate::MakeDelegate(data, &ExtraDelegateDataType::invokeHelper), data);
	}
};

template<class Param0, class Param1, class Param2, class Param3> class Event4 : public AbstractEvent
{
public:
	typedef fastdelegate::FastDelegate4<Param0, Param1, Param2, Param3, void> DelegateType;

	Event4() {}
	~Event4() {}

	void addConnection(ConnectionList * tracker, DelegateType const & deleg, ExtraDelegateData * data)
	{
		AbstractEvent::addConnection(tracker, deleg, data);
	}
	
	void fire(Param0 p0, Param1 p1, Param2 p2, Param3 p3) const
	{
		FireLock lock(this);
		ConnectionsVector const & conns = lock.connections();
		for(ConnectionsVector::const_iterator it = conns.begin(); it != conns.end(); ++it)
		{
			DelegateType deleg = it->delegate_.castToDelegate<DelegateType>();
			deleg(p0, p1, p2, p3);
		}
	}
};

template<class Param0, class Param1, class Param2, class Param3> class EventRef4 : public AbstractEventRef
{
public:
	typedef Event4<Param0, Param1, Param2, Param3> EventType;
	typedef typename EventType::DelegateType DelegateType;

	EventRef4(EventType * ev) : AbstractEventRef(ev) {}
	
	EventType * senderEvent() const
	{
		return static_cast<EventType*>(AbstractEventRef::senderEvent());
	}

	template<class T, class Y> void connect(ConnectionList * tracker, T * obj, void (Y::*pmf)(Param0 p0, Param1 p1, Param2 p2, Param3 p3))
	{
		addConnection(tracker, fastdelegate::MakeDelegate(obj, pmf), 0);
	}

	template<class T, class Y> void connect(ConnectionList * tracker, T const * obj, void (Y::*pmf)(Param0 p0, Param1 p1, Param2 p2, Param3 p3) const)
	{
		addConnection(tracker, fastdelegate::MakeDelegate(obj, pmf), 0);
	}

	template<class T, class Y> void connect(ConnectionList * tracker, T * obj, Y pmf)
	{
		detail::ArgList0 stored;
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1)
	{
		typedef typename StorageType<T1>::Type S1;
		detail::ArgList1<S1> stored(x1);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		detail::ArgList2<S1, S2> stored(x1, x2);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2, T3 x3)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		detail::ArgList3<S1, S2, S3> stored(x1, x2, x3);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3, class T4> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2, T3 x3, T4 x4)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		typedef typename StorageType<T4>::Type S4;
		detail::ArgList4<S1, S2, S3, S4> stored(x1, x2, x3, x4);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3, class T4, class T5> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2, T3 x3, T4 x4, T5 x5)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		typedef typename StorageType<T4>::Type S4;
		typedef typename StorageType<T5>::Type S5;
		detail::ArgList5<S1, S2, S3, S4, S5> stored(x1, x2, x3, x4, x5);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3, class T4, class T5, class T6> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2, T3 x3, T4 x4, T5 x5, T6 x6)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		typedef typename StorageType<T4>::Type S4;
		typedef typename StorageType<T5>::Type S5;
		typedef typename StorageType<T6>::Type S6;
		detail::ArgList6<S1, S2, S3, S4, S5, S6> stored(x1, x2, x3, x4, x5, x6);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3, class T4, class T5, class T6, class T7> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2, T3 x3, T4 x4, T5 x5, T6 x6, T7 x7)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		typedef typename StorageType<T4>::Type S4;
		typedef typename StorageType<T5>::Type S5;
		typedef typename StorageType<T6>::Type S6;
		typedef typename StorageType<T7>::Type S7;
		detail::ArgList7<S1, S2, S3, S4, S5, S6, S7> stored(x1, x2, x3, x4, x5, x6, x7);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

private:
	void addConnection(ConnectionList * tracker, DelegateType const & deleg, ExtraDelegateData * data)
	{
		senderEvent()->addConnection(tracker, deleg, data);
	}

	template<class DelegateClass, class StoredListClass> void connectEx(ConnectionList * tracker, DelegateClass const & deleg, StoredListClass const & stored)
	{
		typedef ExtraDelegateData4<Param0, Param1, Param2, Param3, DelegateClass, StoredListClass> ExtraDelegateDataType;
		ExtraDelegateDataType * data = new ExtraDelegateDataType(deleg, stored);
		addConnection(tracker, fastdelegate::MakeDelegate(data, &ExtraDelegateDataType::invokeHelper), data);
	}
};

template<class Param0, class Param1, class Param2, class Param3, class Param4> class Event5 : public AbstractEvent
{
public:
	typedef fastdelegate::FastDelegate5<Param0, Param1, Param2, Param3, Param4, void> DelegateType;

	Event5() {}
	~Event5() {}

	void addConnection(ConnectionList * tracker, DelegateType const & deleg, ExtraDelegateData * data)
	{
		AbstractEvent::addConnection(tracker, deleg, data);
	}
	
	void fire(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4) const
	{
		FireLock lock(this);
		ConnectionsVector const & conns = lock.connections();
		for(ConnectionsVector::const_iterator it = conns.begin(); it != conns.end(); ++it)
		{
			DelegateType deleg = it->delegate_.castToDelegate<DelegateType>();
			deleg(p0, p1, p2, p3, p4);
		}
	}
};

template<class Param0, class Param1, class Param2, class Param3, class Param4> class EventRef5 : public AbstractEventRef
{
public:
	typedef Event5<Param0, Param1, Param2, Param3, Param4> EventType;
	typedef typename EventType::DelegateType DelegateType;

	EventRef5(EventType * ev) : AbstractEventRef(ev) {}
	
	EventType * senderEvent() const
	{
		return static_cast<EventType*>(AbstractEventRef::senderEvent());
	}

	template<class T, class Y> void connect(ConnectionList * tracker, T * obj, void (Y::*pmf)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4))
	{
		addConnection(tracker, fastdelegate::MakeDelegate(obj, pmf), 0);
	}

	template<class T, class Y> void connect(ConnectionList * tracker, T const * obj, void (Y::*pmf)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4) const)
	{
		addConnection(tracker, fastdelegate::MakeDelegate(obj, pmf), 0);
	}

	template<class T, class Y> void connect(ConnectionList * tracker, T * obj, Y pmf)
	{
		detail::ArgList0 stored;
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1)
	{
		typedef typename StorageType<T1>::Type S1;
		detail::ArgList1<S1> stored(x1);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		detail::ArgList2<S1, S2> stored(x1, x2);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2, T3 x3)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		detail::ArgList3<S1, S2, S3> stored(x1, x2, x3);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3, class T4> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2, T3 x3, T4 x4)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		typedef typename StorageType<T4>::Type S4;
		detail::ArgList4<S1, S2, S3, S4> stored(x1, x2, x3, x4);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3, class T4, class T5> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2, T3 x3, T4 x4, T5 x5)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		typedef typename StorageType<T4>::Type S4;
		typedef typename StorageType<T5>::Type S5;
		detail::ArgList5<S1, S2, S3, S4, S5> stored(x1, x2, x3, x4, x5);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3, class T4, class T5, class T6> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2, T3 x3, T4 x4, T5 x5, T6 x6)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		typedef typename StorageType<T4>::Type S4;
		typedef typename StorageType<T5>::Type S5;
		typedef typename StorageType<T6>::Type S6;
		detail::ArgList6<S1, S2, S3, S4, S5, S6> stored(x1, x2, x3, x4, x5, x6);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3, class T4, class T5, class T6, class T7> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2, T3 x3, T4 x4, T5 x5, T6 x6, T7 x7)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		typedef typename StorageType<T4>::Type S4;
		typedef typename StorageType<T5>::Type S5;
		typedef typename StorageType<T6>::Type S6;
		typedef typename StorageType<T7>::Type S7;
		detail::ArgList7<S1, S2, S3, S4, S5, S6, S7> stored(x1, x2, x3, x4, x5, x6, x7);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

private:
	void addConnection(ConnectionList * tracker, DelegateType const & deleg, ExtraDelegateData * data)
	{
		senderEvent()->addConnection(tracker, deleg, data);
	}

	template<class DelegateClass, class StoredListClass> void connectEx(ConnectionList * tracker, DelegateClass const & deleg, StoredListClass const & stored)
	{
		typedef ExtraDelegateData5<Param0, Param1, Param2, Param3, Param4, DelegateClass, StoredListClass> ExtraDelegateDataType;
		ExtraDelegateDataType * data = new ExtraDelegateDataType(deleg, stored);
		addConnection(tracker, fastdelegate::MakeDelegate(data, &ExtraDelegateDataType::invokeHelper), data);
	}
};

template<class Param0, class Param1, class Param2, class Param3, class Param4, class Param5> class Event6 : public AbstractEvent
{
public:
	typedef fastdelegate::FastDelegate6<Param0, Param1, Param2, Param3, Param4, Param5, void> DelegateType;

	Event6() {}
	~Event6() {}

	void addConnection(ConnectionList * tracker, DelegateType const & deleg, ExtraDelegateData * data)
	{
		AbstractEvent::addConnection(tracker, deleg, data);
	}
	
	void fire(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) const
	{
		FireLock lock(this);
		ConnectionsVector const & conns = lock.connections();
		for(ConnectionsVector::const_iterator it = conns.begin(); it != conns.end(); ++it)
		{
			DelegateType deleg = it->delegate_.castToDelegate<DelegateType>();
			deleg(p0, p1, p2, p3, p4, p5);
		}
	}
};

template<class Param0, class Param1, class Param2, class Param3, class Param4, class Param5> class EventRef6 : public AbstractEventRef
{
public:
	typedef Event6<Param0, Param1, Param2, Param3, Param4, Param5> EventType;
	typedef typename EventType::DelegateType DelegateType;

	EventRef6(EventType * ev) : AbstractEventRef(ev) {}
	
	EventType * senderEvent() const
	{
		return static_cast<EventType*>(AbstractEventRef::senderEvent());
	}

	template<class T, class Y> void connect(ConnectionList * tracker, T * obj, void (Y::*pmf)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5))
	{
		addConnection(tracker, fastdelegate::MakeDelegate(obj, pmf), 0);
	}

	template<class T, class Y> void connect(ConnectionList * tracker, T const * obj, void (Y::*pmf)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) const)
	{
		addConnection(tracker, fastdelegate::MakeDelegate(obj, pmf), 0);
	}

	template<class T, class Y> void connect(ConnectionList * tracker, T * obj, Y pmf)
	{
		detail::ArgList0 stored;
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1)
	{
		typedef typename StorageType<T1>::Type S1;
		detail::ArgList1<S1> stored(x1);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		detail::ArgList2<S1, S2> stored(x1, x2);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2, T3 x3)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		detail::ArgList3<S1, S2, S3> stored(x1, x2, x3);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3, class T4> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2, T3 x3, T4 x4)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		typedef typename StorageType<T4>::Type S4;
		detail::ArgList4<S1, S2, S3, S4> stored(x1, x2, x3, x4);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3, class T4, class T5> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2, T3 x3, T4 x4, T5 x5)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		typedef typename StorageType<T4>::Type S4;
		typedef typename StorageType<T5>::Type S5;
		detail::ArgList5<S1, S2, S3, S4, S5> stored(x1, x2, x3, x4, x5);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3, class T4, class T5, class T6> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2, T3 x3, T4 x4, T5 x5, T6 x6)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		typedef typename StorageType<T4>::Type S4;
		typedef typename StorageType<T5>::Type S5;
		typedef typename StorageType<T6>::Type S6;
		detail::ArgList6<S1, S2, S3, S4, S5, S6> stored(x1, x2, x3, x4, x5, x6);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3, class T4, class T5, class T6, class T7> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2, T3 x3, T4 x4, T5 x5, T6 x6, T7 x7)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		typedef typename StorageType<T4>::Type S4;
		typedef typename StorageType<T5>::Type S5;
		typedef typename StorageType<T6>::Type S6;
		typedef typename StorageType<T7>::Type S7;
		detail::ArgList7<S1, S2, S3, S4, S5, S6, S7> stored(x1, x2, x3, x4, x5, x6, x7);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

private:
	void addConnection(ConnectionList * tracker, DelegateType const & deleg, ExtraDelegateData * data)
	{
		senderEvent()->addConnection(tracker, deleg, data);
	}

	template<class DelegateClass, class StoredListClass> void connectEx(ConnectionList * tracker, DelegateClass const & deleg, StoredListClass const & stored)
	{
		typedef ExtraDelegateData6<Param0, Param1, Param2, Param3, Param4, Param5, DelegateClass, StoredListClass> ExtraDelegateDataType;
		ExtraDelegateDataType * data = new ExtraDelegateDataType(deleg, stored);
		addConnection(tracker, fastdelegate::MakeDelegate(data, &ExtraDelegateDataType::invokeHelper), data);
	}
};

template<class Param0, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6> class Event7 : public AbstractEvent
{
public:
	typedef fastdelegate::FastDelegate7<Param0, Param1, Param2, Param3, Param4, Param5, Param6, void> DelegateType;

	Event7() {}
	~Event7() {}

	void addConnection(ConnectionList * tracker, DelegateType const & deleg, ExtraDelegateData * data)
	{
		AbstractEvent::addConnection(tracker, deleg, data);
	}
	
	void fire(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6) const
	{
		FireLock lock(this);
		ConnectionsVector const & conns = lock.connections();
		for(ConnectionsVector::const_iterator it = conns.begin(); it != conns.end(); ++it)
		{
			DelegateType deleg = it->delegate_.castToDelegate<DelegateType>();
			deleg(p0, p1, p2, p3, p4, p5, p6);
		}
	}
};

template<class Param0, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6> class EventRef7 : public AbstractEventRef
{
public:
	typedef Event7<Param0, Param1, Param2, Param3, Param4, Param5, Param6> EventType;
	typedef typename EventType::DelegateType DelegateType;

	EventRef7(EventType * ev) : AbstractEventRef(ev) {}
	
	EventType * senderEvent() const
	{
		return static_cast<EventType*>(AbstractEventRef::senderEvent());
	}

	template<class T, class Y> void connect(ConnectionList * tracker, T * obj, void (Y::*pmf)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6))
	{
		addConnection(tracker, fastdelegate::MakeDelegate(obj, pmf), 0);
	}

	template<class T, class Y> void connect(ConnectionList * tracker, T const * obj, void (Y::*pmf)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6) const)
	{
		addConnection(tracker, fastdelegate::MakeDelegate(obj, pmf), 0);
	}

	template<class T, class Y> void connect(ConnectionList * tracker, T * obj, Y pmf)
	{
		detail::ArgList0 stored;
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1)
	{
		typedef typename StorageType<T1>::Type S1;
		detail::ArgList1<S1> stored(x1);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		detail::ArgList2<S1, S2> stored(x1, x2);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2, T3 x3)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		detail::ArgList3<S1, S2, S3> stored(x1, x2, x3);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3, class T4> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2, T3 x3, T4 x4)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		typedef typename StorageType<T4>::Type S4;
		detail::ArgList4<S1, S2, S3, S4> stored(x1, x2, x3, x4);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3, class T4, class T5> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2, T3 x3, T4 x4, T5 x5)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		typedef typename StorageType<T4>::Type S4;
		typedef typename StorageType<T5>::Type S5;
		detail::ArgList5<S1, S2, S3, S4, S5> stored(x1, x2, x3, x4, x5);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3, class T4, class T5, class T6> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2, T3 x3, T4 x4, T5 x5, T6 x6)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		typedef typename StorageType<T4>::Type S4;
		typedef typename StorageType<T5>::Type S5;
		typedef typename StorageType<T6>::Type S6;
		detail::ArgList6<S1, S2, S3, S4, S5, S6> stored(x1, x2, x3, x4, x5, x6);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

	template<class T, class Y, class T1, class T2, class T3, class T4, class T5, class T6, class T7> void connect(ConnectionList * tracker, T * obj, Y pmf, T1 x1, T2 x2, T3 x3, T4 x4, T5 x5, T6 x6, T7 x7)
	{
		typedef typename StorageType<T1>::Type S1;
		typedef typename StorageType<T2>::Type S2;
		typedef typename StorageType<T3>::Type S3;
		typedef typename StorageType<T4>::Type S4;
		typedef typename StorageType<T5>::Type S5;
		typedef typename StorageType<T6>::Type S6;
		typedef typename StorageType<T7>::Type S7;
		detail::ArgList7<S1, S2, S3, S4, S5, S6, S7> stored(x1, x2, x3, x4, x5, x6, x7);
		connectEx(tracker, fastdelegate::MakeDelegate(obj, pmf), stored);
	}

private:
	void addConnection(ConnectionList * tracker, DelegateType const & deleg, ExtraDelegateData * data)
	{
		senderEvent()->addConnection(tracker, deleg, data);
	}

	template<class DelegateClass, class StoredListClass> void connectEx(ConnectionList * tracker, DelegateClass const & deleg, StoredListClass const & stored)
	{
		typedef ExtraDelegateData7<Param0, Param1, Param2, Param3, Param4, Param5, Param6, DelegateClass, StoredListClass> ExtraDelegateDataType;
		ExtraDelegateDataType * data = new ExtraDelegateDataType(deleg, stored);
		addConnection(tracker, fastdelegate::MakeDelegate(data, &ExtraDelegateDataType::invokeHelper), data);
	}
};

#endif //EVENTS_H