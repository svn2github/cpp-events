#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "AbstractConnection.hpp"

class Connection0 : public AbstractConnection
{
protected:
	virtual ~Connection0() {}
public:
	typedef fastdelegate::FastDelegate0<void> DelegateType;
	
	Connection0(
		void const * sender, AbstractEvent * ev, 
		void const * reciever, DelegateType const & deleg
	)
		: AbstractConnection(sender, ev, reciever, deleg.GetMemento())
		, delegate_(deleg)
	{}

	void invoke() const { delegate_(); }
protected:
	DelegateType delegate_;

	Connection0(
		void const * sender, AbstractEvent * ev, 
		void const * reciever, fastdelegate::DelegateMemento const & memento
	)
		: AbstractConnection(sender, ev, reciever, memento)
		, delegate_()
	{}
};

template<class Param0> class Connection1 : public AbstractConnection
{
protected:
	virtual ~Connection1() {}
public:
	typedef fastdelegate::FastDelegate1<Param0, void> DelegateType;
	
	Connection1(
		void const * sender, AbstractEvent * ev, 
		void const * reciever, DelegateType const & deleg
	)
		: AbstractConnection(sender, ev, reciever, deleg.GetMemento())
		, delegate_(deleg)
	{}

	void invoke(Param0 p0) const { delegate_(p0); }
protected:
	DelegateType delegate_;

	Connection1(
		void const * sender, AbstractEvent * ev, 
		void const * reciever, fastdelegate::DelegateMemento const & memento
	)
		: AbstractConnection(sender, ev, reciever, memento)
		, delegate_()
	{}
};

template<class Param0, class Param1> class Connection2 : public AbstractConnection
{
protected:
	virtual ~Connection2() {}
public:
	typedef fastdelegate::FastDelegate2<Param0, Param1, void> DelegateType;
	
	Connection2(
		void const * sender, AbstractEvent * ev, 
		void const * reciever, DelegateType const & deleg
	)
		: AbstractConnection(sender, ev, reciever, deleg.GetMemento())
		, delegate_(deleg)
	{}

	void invoke(Param0 p0, Param1 p1) const { delegate_(p0, p1); }
protected:
	DelegateType delegate_;

	Connection2(
		void const * sender, AbstractEvent * ev, 
		void const * reciever, fastdelegate::DelegateMemento const & memento
	)
		: AbstractConnection(sender, ev, reciever, memento)
		, delegate_()
	{}
};

template<class Param0, class Param1, class Param2> class Connection3 : public AbstractConnection
{
protected:
	virtual ~Connection3() {}
public:
	typedef fastdelegate::FastDelegate3<Param0, Param1, Param2, void> DelegateType;
	
	Connection3(
		void const * sender, AbstractEvent * ev, 
		void const * reciever, DelegateType const & deleg
	)
		: AbstractConnection(sender, ev, reciever, deleg.GetMemento())
		, delegate_(deleg)
	{}

	void invoke(Param0 p0, Param1 p1, Param2 p2) const { delegate_(p0, p1, p2); }
protected:
	DelegateType delegate_;

	Connection3(
		void const * sender, AbstractEvent * ev, 
		void const * reciever, fastdelegate::DelegateMemento const & memento
	)
		: AbstractConnection(sender, ev, reciever, memento)
		, delegate_()
	{}
};

template<class Param0, class Param1, class Param2, class Param3> class Connection4 : public AbstractConnection
{
protected:
	virtual ~Connection4() {}
public:
	typedef fastdelegate::FastDelegate4<Param0, Param1, Param2, Param3, void> DelegateType;
	
	Connection4(
		void const * sender, AbstractEvent * ev, 
		void const * reciever, DelegateType const & deleg
	)
		: AbstractConnection(sender, ev, reciever, deleg.GetMemento())
		, delegate_(deleg)
	{}

	void invoke(Param0 p0, Param1 p1, Param2 p2, Param3 p3) const { delegate_(p0, p1, p2, p3); }
protected:
	DelegateType delegate_;

	Connection4(
		void const * sender, AbstractEvent * ev, 
		void const * reciever, fastdelegate::DelegateMemento const & memento
	)
		: AbstractConnection(sender, ev, reciever, memento)
		, delegate_()
	{}
};

template<class Param0, class Param1, class Param2, class Param3, class Param4> class Connection5 : public AbstractConnection
{
protected:
	virtual ~Connection5() {}
public:
	typedef fastdelegate::FastDelegate5<Param0, Param1, Param2, Param3, Param4, void> DelegateType;
	
	Connection5(
		void const * sender, AbstractEvent * ev, 
		void const * reciever, DelegateType const & deleg
	)
		: AbstractConnection(sender, ev, reciever, deleg.GetMemento())
		, delegate_(deleg)
	{}

	void invoke(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4) const { delegate_(p0, p1, p2, p3, p4); }
protected:
	DelegateType delegate_;

	Connection5(
		void const * sender, AbstractEvent * ev, 
		void const * reciever, fastdelegate::DelegateMemento const & memento
	)
		: AbstractConnection(sender, ev, reciever, memento)
		, delegate_()
	{}
};

template<class Param0, class Param1, class Param2, class Param3, class Param4, class Param5> class Connection6 : public AbstractConnection
{
protected:
	virtual ~Connection6() {}
public:
	typedef fastdelegate::FastDelegate6<Param0, Param1, Param2, Param3, Param4, Param5, void> DelegateType;
	
	Connection6(
		void const * sender, AbstractEvent * ev, 
		void const * reciever, DelegateType const & deleg
	)
		: AbstractConnection(sender, ev, reciever, deleg.GetMemento())
		, delegate_(deleg)
	{}

	void invoke(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) const { delegate_(p0, p1, p2, p3, p4, p5); }
protected:
	DelegateType delegate_;

	Connection6(
		void const * sender, AbstractEvent * ev, 
		void const * reciever, fastdelegate::DelegateMemento const & memento
	)
		: AbstractConnection(sender, ev, reciever, memento)
		, delegate_()
	{}
};

template<class Param0, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6> class Connection7 : public AbstractConnection
{
protected:
	virtual ~Connection7() {}
public:
	typedef fastdelegate::FastDelegate7<Param0, Param1, Param2, Param3, Param4, Param5, Param6, void> DelegateType;
	
	Connection7(
		void const * sender, AbstractEvent * ev, 
		void const * reciever, DelegateType const & deleg
	)
		: AbstractConnection(sender, ev, reciever, deleg.GetMemento())
		, delegate_(deleg)
	{}

	void invoke(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6) const { delegate_(p0, p1, p2, p3, p4, p5, p6); }
protected:
	DelegateType delegate_;

	Connection7(
		void const * sender, AbstractEvent * ev, 
		void const * reciever, fastdelegate::DelegateMemento const & memento
	)
		: AbstractConnection(sender, ev, reciever, memento)
		, delegate_()
	{}
};


#endif //CONNECTION_HPP