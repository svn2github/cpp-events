#ifndef CONNECTION_EX__HPP
#define CONNECTION_EX__HPP

#include "Connection.hpp"
#include "ArgList.hpp"

template<class DelegateClass, class StoredListClass>
class ConnectionEx0 : public Connection0
{
public:
	typedef Connection0 BaseType;
	typedef ConnectionEx0<DelegateClass, StoredListClass> ThisType;

	ConnectionEx0(
		void const * sender, AbstractEvent * ev, void const * reciever,
		DelegateClass const & deleg, StoredListClass const & stored
	)
		: BaseType(sender, ev, reciever, deleg.GetMemento())
		, deleg_(deleg), stored_(stored)
	{
		BaseType::delegate_ = fastdelegate::MakeDelegate(this, &ThisType::invokeHelper);
	}
private:
	DelegateClass deleg_;
	StoredListClass stored_;

	void invokeHelper() const
	{
		detail::ArgList0 paramList;
		return detail::invokeDelegate(deleg_, stored_, paramList);
	}
};

template<class Param0, class DelegateClass, class StoredListClass>
class ConnectionEx1 : public Connection1<Param0>
{
public:
	typedef Connection1<Param0> BaseType;
	typedef ConnectionEx1<Param0,DelegateClass, StoredListClass> ThisType;

	ConnectionEx1(
		void const * sender, AbstractEvent * ev, void const * reciever,
		DelegateClass const & deleg, StoredListClass const & stored
	)
		: BaseType(sender, ev, reciever, deleg.GetMemento())
		, deleg_(deleg), stored_(stored)
	{
		BaseType::delegate_ = fastdelegate::MakeDelegate(this, &ThisType::invokeHelper);
	}
private:
	DelegateClass deleg_;
	StoredListClass stored_;

	void invokeHelper(Param0 p0) const
	{
		detail::ArgList1<Param0> paramList(p0);
		return detail::invokeDelegate(deleg_, stored_, paramList);
	}
};

template<class Param0, class Param1, class DelegateClass, class StoredListClass>
class ConnectionEx2 : public Connection2<Param0, Param1>
{
public:
	typedef Connection2<Param0, Param1> BaseType;
	typedef ConnectionEx2<Param0, Param1,DelegateClass, StoredListClass> ThisType;

	ConnectionEx2(
		void const * sender, AbstractEvent * ev, void const * reciever,
		DelegateClass const & deleg, StoredListClass const & stored
	)
		: BaseType(sender, ev, reciever, deleg.GetMemento())
		, deleg_(deleg), stored_(stored)
	{
		BaseType::delegate_ = fastdelegate::MakeDelegate(this, &ThisType::invokeHelper);
	}
private:
	DelegateClass deleg_;
	StoredListClass stored_;

	void invokeHelper(Param0 p0, Param1 p1) const
	{
		detail::ArgList2<Param0, Param1> paramList(p0, p1);
		return detail::invokeDelegate(deleg_, stored_, paramList);
	}
};

template<class Param0, class Param1, class Param2, class DelegateClass, class StoredListClass>
class ConnectionEx3 : public Connection3<Param0, Param1, Param2>
{
public:
	typedef Connection3<Param0, Param1, Param2> BaseType;
	typedef ConnectionEx3<Param0, Param1, Param2,DelegateClass, StoredListClass> ThisType;

	ConnectionEx3(
		void const * sender, AbstractEvent * ev, void const * reciever,
		DelegateClass const & deleg, StoredListClass const & stored
	)
		: BaseType(sender, ev, reciever, deleg.GetMemento())
		, deleg_(deleg), stored_(stored)
	{
		BaseType::delegate_ = fastdelegate::MakeDelegate(this, &ThisType::invokeHelper);
	}
private:
	DelegateClass deleg_;
	StoredListClass stored_;

	void invokeHelper(Param0 p0, Param1 p1, Param2 p2) const
	{
		detail::ArgList3<Param0, Param1, Param2> paramList(p0, p1, p2);
		return detail::invokeDelegate(deleg_, stored_, paramList);
	}
};

template<class Param0, class Param1, class Param2, class Param3, class DelegateClass, class StoredListClass>
class ConnectionEx4 : public Connection4<Param0, Param1, Param2, Param3>
{
public:
	typedef Connection4<Param0, Param1, Param2, Param3> BaseType;
	typedef ConnectionEx4<Param0, Param1, Param2, Param3,DelegateClass, StoredListClass> ThisType;

	ConnectionEx4(
		void const * sender, AbstractEvent * ev, void const * reciever,
		DelegateClass const & deleg, StoredListClass const & stored
	)
		: BaseType(sender, ev, reciever, deleg.GetMemento())
		, deleg_(deleg), stored_(stored)
	{
		BaseType::delegate_ = fastdelegate::MakeDelegate(this, &ThisType::invokeHelper);
	}
private:
	DelegateClass deleg_;
	StoredListClass stored_;

	void invokeHelper(Param0 p0, Param1 p1, Param2 p2, Param3 p3) const
	{
		detail::ArgList4<Param0, Param1, Param2, Param3> paramList(p0, p1, p2, p3);
		return detail::invokeDelegate(deleg_, stored_, paramList);
	}
};

template<class Param0, class Param1, class Param2, class Param3, class Param4, class DelegateClass, class StoredListClass>
class ConnectionEx5 : public Connection5<Param0, Param1, Param2, Param3, Param4>
{
public:
	typedef Connection5<Param0, Param1, Param2, Param3, Param4> BaseType;
	typedef ConnectionEx5<Param0, Param1, Param2, Param3, Param4,DelegateClass, StoredListClass> ThisType;

	ConnectionEx5(
		void const * sender, AbstractEvent * ev, void const * reciever,
		DelegateClass const & deleg, StoredListClass const & stored
	)
		: BaseType(sender, ev, reciever, deleg.GetMemento())
		, deleg_(deleg), stored_(stored)
	{
		BaseType::delegate_ = fastdelegate::MakeDelegate(this, &ThisType::invokeHelper);
	}
private:
	DelegateClass deleg_;
	StoredListClass stored_;

	void invokeHelper(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4) const
	{
		detail::ArgList5<Param0, Param1, Param2, Param3, Param4> paramList(p0, p1, p2, p3, p4);
		return detail::invokeDelegate(deleg_, stored_, paramList);
	}
};

template<class Param0, class Param1, class Param2, class Param3, class Param4, class Param5, class DelegateClass, class StoredListClass>
class ConnectionEx6 : public Connection6<Param0, Param1, Param2, Param3, Param4, Param5>
{
public:
	typedef Connection6<Param0, Param1, Param2, Param3, Param4, Param5> BaseType;
	typedef ConnectionEx6<Param0, Param1, Param2, Param3, Param4, Param5,DelegateClass, StoredListClass> ThisType;

	ConnectionEx6(
		void const * sender, AbstractEvent * ev, void const * reciever,
		DelegateClass const & deleg, StoredListClass const & stored
	)
		: BaseType(sender, ev, reciever, deleg.GetMemento())
		, deleg_(deleg), stored_(stored)
	{
		BaseType::delegate_ = fastdelegate::MakeDelegate(this, &ThisType::invokeHelper);
	}
private:
	DelegateClass deleg_;
	StoredListClass stored_;

	void invokeHelper(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) const
	{
		detail::ArgList6<Param0, Param1, Param2, Param3, Param4, Param5> paramList(p0, p1, p2, p3, p4, p5);
		return detail::invokeDelegate(deleg_, stored_, paramList);
	}
};

template<class Param0, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class DelegateClass, class StoredListClass>
class ConnectionEx7 : public Connection7<Param0, Param1, Param2, Param3, Param4, Param5, Param6>
{
public:
	typedef Connection7<Param0, Param1, Param2, Param3, Param4, Param5, Param6> BaseType;
	typedef ConnectionEx7<Param0, Param1, Param2, Param3, Param4, Param5, Param6,DelegateClass, StoredListClass> ThisType;

	ConnectionEx7(
		void const * sender, AbstractEvent * ev, void const * reciever,
		DelegateClass const & deleg, StoredListClass const & stored
	)
		: BaseType(sender, ev, reciever, deleg.GetMemento())
		, deleg_(deleg), stored_(stored)
	{
		BaseType::delegate_ = fastdelegate::MakeDelegate(this, &ThisType::invokeHelper);
	}
private:
	DelegateClass deleg_;
	StoredListClass stored_;

	void invokeHelper(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6) const
	{
		detail::ArgList7<Param0, Param1, Param2, Param3, Param4, Param5, Param6> paramList(p0, p1, p2, p3, p4, p5, p6);
		return detail::invokeDelegate(deleg_, stored_, paramList);
	}
};


#endif //CONNECTION_EX__HPP