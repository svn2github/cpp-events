#ifndef EXTRA_DELEGATE_DATA__HPP
#define EXTRA_DELEGATE_DATA__HPP

#include "ConnectionList.hpp"
#include "ArgList.hpp"

template<class DelegateClass, class StoredListClass>
class ExtraDelegateData0 : public ExtraDelegateData
{
public:
	ExtraDelegateData0(DelegateClass const & deleg, StoredListClass const & stored)
		: ExtraDelegateData(deleg)
		, deleg_(deleg)
		, stored_(stored)
	{
	}
	
	void invokeHelper() const
	{
		detail::ArgList0 paramList;
		return detail::invokeDelegate(deleg_, stored_, paramList);
	}
private:
	DelegateClass deleg_;
	StoredListClass stored_;
};

template<class Param0, class DelegateClass, class StoredListClass>
class ExtraDelegateData1 : public ExtraDelegateData
{
public:
	ExtraDelegateData1(DelegateClass const & deleg, StoredListClass const & stored)
		: ExtraDelegateData(deleg)
		, deleg_(deleg)
		, stored_(stored)
	{
	}
	
	void invokeHelper(Param0 p0) const
	{
		detail::ArgList1<Param0> paramList(p0);
		return detail::invokeDelegate(deleg_, stored_, paramList);
	}
private:
	DelegateClass deleg_;
	StoredListClass stored_;
};

template<class Param0, class Param1, class DelegateClass, class StoredListClass>
class ExtraDelegateData2 : public ExtraDelegateData
{
public:
	ExtraDelegateData2(DelegateClass const & deleg, StoredListClass const & stored)
		: ExtraDelegateData(deleg)
		, deleg_(deleg)
		, stored_(stored)
	{
	}
	
	void invokeHelper(Param0 p0, Param1 p1) const
	{
		detail::ArgList2<Param0, Param1> paramList(p0, p1);
		return detail::invokeDelegate(deleg_, stored_, paramList);
	}
private:
	DelegateClass deleg_;
	StoredListClass stored_;
};

template<class Param0, class Param1, class Param2, class DelegateClass, class StoredListClass>
class ExtraDelegateData3 : public ExtraDelegateData
{
public:
	ExtraDelegateData3(DelegateClass const & deleg, StoredListClass const & stored)
		: ExtraDelegateData(deleg)
		, deleg_(deleg)
		, stored_(stored)
	{
	}
	
	void invokeHelper(Param0 p0, Param1 p1, Param2 p2) const
	{
		detail::ArgList3<Param0, Param1, Param2> paramList(p0, p1, p2);
		return detail::invokeDelegate(deleg_, stored_, paramList);
	}
private:
	DelegateClass deleg_;
	StoredListClass stored_;
};

template<class Param0, class Param1, class Param2, class Param3, class DelegateClass, class StoredListClass>
class ExtraDelegateData4 : public ExtraDelegateData
{
public:
	ExtraDelegateData4(DelegateClass const & deleg, StoredListClass const & stored)
		: ExtraDelegateData(deleg)
		, deleg_(deleg)
		, stored_(stored)
	{
	}
	
	void invokeHelper(Param0 p0, Param1 p1, Param2 p2, Param3 p3) const
	{
		detail::ArgList4<Param0, Param1, Param2, Param3> paramList(p0, p1, p2, p3);
		return detail::invokeDelegate(deleg_, stored_, paramList);
	}
private:
	DelegateClass deleg_;
	StoredListClass stored_;
};

template<class Param0, class Param1, class Param2, class Param3, class Param4, class DelegateClass, class StoredListClass>
class ExtraDelegateData5 : public ExtraDelegateData
{
public:
	ExtraDelegateData5(DelegateClass const & deleg, StoredListClass const & stored)
		: ExtraDelegateData(deleg)
		, deleg_(deleg)
		, stored_(stored)
	{
	}
	
	void invokeHelper(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4) const
	{
		detail::ArgList5<Param0, Param1, Param2, Param3, Param4> paramList(p0, p1, p2, p3, p4);
		return detail::invokeDelegate(deleg_, stored_, paramList);
	}
private:
	DelegateClass deleg_;
	StoredListClass stored_;
};

template<class Param0, class Param1, class Param2, class Param3, class Param4, class Param5, class DelegateClass, class StoredListClass>
class ExtraDelegateData6 : public ExtraDelegateData
{
public:
	ExtraDelegateData6(DelegateClass const & deleg, StoredListClass const & stored)
		: ExtraDelegateData(deleg)
		, deleg_(deleg)
		, stored_(stored)
	{
	}
	
	void invokeHelper(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) const
	{
		detail::ArgList6<Param0, Param1, Param2, Param3, Param4, Param5> paramList(p0, p1, p2, p3, p4, p5);
		return detail::invokeDelegate(deleg_, stored_, paramList);
	}
private:
	DelegateClass deleg_;
	StoredListClass stored_;
};

template<class Param0, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class DelegateClass, class StoredListClass>
class ExtraDelegateData7 : public ExtraDelegateData
{
public:
	ExtraDelegateData7(DelegateClass const & deleg, StoredListClass const & stored)
		: ExtraDelegateData(deleg)
		, deleg_(deleg)
		, stored_(stored)
	{
	}
	
	void invokeHelper(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6) const
	{
		detail::ArgList7<Param0, Param1, Param2, Param3, Param4, Param5, Param6> paramList(p0, p1, p2, p3, p4, p5, p6);
		return detail::invokeDelegate(deleg_, stored_, paramList);
	}
private:
	DelegateClass deleg_;
	StoredListClass stored_;
};

#endif //EXTRA_DELEGATE_DATA__HPP