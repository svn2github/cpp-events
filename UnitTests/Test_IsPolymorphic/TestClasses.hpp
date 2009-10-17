#ifndef TEST__ABSTRACT_OBJECT_REF__TEST_CLASSES__HPP
#define TEST__ABSTRACT_OBJECT_REF__TEST_CLASSES__HPP

class ClassWithUndefinedPrivateCtorAndDtor
{
private:
	ClassWithUndefinedPrivateCtorAndDtor();
	~ClassWithUndefinedPrivateCtorAndDtor();
};

template<int Size> class ClassOfSize { char data[Size]; };
template<> class ClassOfSize<0> {};
//template<> class ClassOfSize<3> { virtual void testFail() {} };

class NonVirtualClass1 { char x; };
class NonVirtualClass2_1 : public NonVirtualClass1 { int y; };
class NonVirtualClass3_1 : public NonVirtualClass1 { char z[sizeof(void*)-1]; };
class NonVirtualClass4_2_3 : public NonVirtualClass2_1, public NonVirtualClass3_1 { int w; };
class NonVirtualClass2 { void* x[1]; };
class NonVirtualClass3 { void* x[3]; };
class NonVirtualClass4 { void* x[5]; };
class NonVirtualClass5 { void* x[7]; };

class VirtualByDestructor
{
	virtual ~VirtualByDestructor() {}
};

class VirtualByFunction
{
	virtual void func() {}
};

class VirtualByPureFunction
{
	virtual void func() = 0;
};

class VirtualBaseClass
{
public:
	virtual ~VirtualBaseClass() {}

	char x;
};

class VirtualDerivedClass1 : public VirtualBaseClass
{
	int y;
};

class VirtualDerivedClass2 : public VirtualBaseClass
{
	char z[sizeof(void*)-1];
};

class VirtualCommonDerived : public VirtualDerivedClass1, public VirtualDerivedClass2
{
};

class ClassThatAddsVirtuality1 : public NonVirtualClass1
{
	virtual ~ClassThatAddsVirtuality1() {}
};

class ClassThatAddsVirtuality2 : public NonVirtualClass1, public VirtualBaseClass
{
};

template<class T> class Virtualizer : public T
{
public:
	virtual void testFunc() = 0;
};

class VirtualInhLeft : public virtual NonVirtualClass1
{
	int xxx;
};

class VirtualInhRight : public virtual NonVirtualClass1
{
	int yyy;
};

class  VirtualInhBottom : public VirtualInhLeft, public VirtualInhRight
{
	int zzz;
};

class VirtualInhExtraL : public virtual VirtualBaseClass { int d; };
class VirtualInhExtraR : public virtual VirtualBaseClass { int e; };

class VirtualInhExtraX : public VirtualInhExtraL, public virtual VirtualInhExtraR
{
	int q;
};

#endif //TEST__ABSTRACT_OBJECT_REF__TEST_CLASSES__HPP
