// Copyright (c) 2010 Nickolas Pohilets
//
// This file is a part of the probe project suit for the CppEvents library.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

/*
Goal:
   Check inverted method of detecting if class is polymorphic.

Motivation:
   This was used in earlier implementations of CppEvents for normalizing object
   pointers. Current implementation does not use this method.

Results:
	MSVC - PASSED
	GCC - FAILES, testVirtualInheritanceDoesNotMakeClassesPolymorphic()
*/

//------------------------------------------------------------------------------
//                         T E S T  C L A S S E S
//------------------------------------------------------------------------------
class ClassWithUndefinedPrivateCtorAndDtor
{
private:
	ClassWithUndefinedPrivateCtorAndDtor();
	~ClassWithUndefinedPrivateCtorAndDtor();
};
//------------------------------------------------------------------------------
template<int Size> class ClassOfSize { char data[Size]; };
template<> class ClassOfSize<0> {};
//------------------------------------------------------------------------------
class NonVirtualClass1 { char x; };
class NonVirtualClass2_1 : public NonVirtualClass1 { int y; };
class NonVirtualClass3_1 : public NonVirtualClass1 { char z[sizeof(void*)-1]; };
class NonVirtualClass4_2_3 : public NonVirtualClass2_1, public NonVirtualClass3_1 { int w; };
class NonVirtualClass2 { void* x[1]; };
class NonVirtualClass3 { void* x[3]; };
class NonVirtualClass4 { void* x[5]; };
class NonVirtualClass5 { void* x[7]; };
//------------------------------------------------------------------------------
class VirtualByDestructor
{
	virtual ~VirtualByDestructor() {}
};
//------------------------------------------------------------------------------
class VirtualByFunction
{
	virtual void func() {}
};
//------------------------------------------------------------------------------
class VirtualByPureFunction
{
	virtual void func() = 0;
};
//------------------------------------------------------------------------------
class VirtualBaseClass
{
public:
	virtual ~VirtualBaseClass() {}

	char x;
};
//------------------------------------------------------------------------------
class VirtualDerivedClass1 : public VirtualBaseClass
{
	int y;
};
//------------------------------------------------------------------------------
class VirtualDerivedClass2 : public VirtualBaseClass
{
	char z[sizeof(void*)-1];
};
//------------------------------------------------------------------------------
class VirtualCommonDerived : public VirtualDerivedClass1, public VirtualDerivedClass2
{
};
//------------------------------------------------------------------------------
class ClassThatAddsVirtuality1 : public NonVirtualClass1
{
	virtual ~ClassThatAddsVirtuality1() {}
};
//------------------------------------------------------------------------------
class ClassThatAddsVirtuality2 : public NonVirtualClass1, public VirtualBaseClass
{
};
//------------------------------------------------------------------------------
template<class T> class Virtualizer : public T
{
public:
	virtual void testFunc() = 0;
};
//------------------------------------------------------------------------------
class VirtualInhLeft : public virtual NonVirtualClass1
{
	int xxx;
};
//------------------------------------------------------------------------------
class VirtualInhRight : public virtual NonVirtualClass1
{
	int yyy;
};
//------------------------------------------------------------------------------
class  VirtualInhBottom : public VirtualInhLeft, public VirtualInhRight
{
	int zzz;
};
//------------------------------------------------------------------------------
class VirtualInhExtraL : public virtual VirtualBaseClass { int d; };
class VirtualInhExtraR : public virtual VirtualBaseClass { int e; };
//------------------------------------------------------------------------------
class VirtualInhExtraX : public VirtualInhExtraL, public virtual VirtualInhExtraR
{
	int q;
};
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//                      T E S T I N G   R O U T I N E S
//------------------------------------------------------------------------------
template<class T> struct IsPolymorphic
{
	class Helper : public T { virtual ~Helper() = 0; };
	enum { value = sizeof(Helper) == sizeof(T) ? 1 : 0 };
};
//------------------------------------------------------------------------------
template<bool> struct AssertFalse;
template<> struct AssertFalse<false> { static void isOk() {} };
#define ASSERT_FALSE(X) AssertFalse<X>::isOk()
//------------------------------------------------------------------------------
template<bool> struct AssertTrue;
template<> struct AssertTrue<true> { static void isOk() {} };
#define ASSERT_TRUE(X) AssertTrue<X>::isOk()
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//                                    T E S T S
//------------------------------------------------------------------------------
/*
	For checking polymorphy special template class is derived from class being tested.
	This potentially may cause compilation problems if some special members of base class are inaccessible.
	This test is designed for detecting these problems. Test is passed if it compiles.
*/
void testCompilability()
{
	bool const b = IsPolymorphic<ClassWithUndefinedPrivateCtorAndDtor>::value;
	(void)b;
}
//------------------------------------------------------------------------------
/*
	Class alignment may possibly cause false detection of polymorphic classes.
	This test is designed for detecting them.
*/
template<int n> void doTestAlignmentIssues(ClassOfSize<n> const & x)
{
	ASSERT_FALSE(IsPolymorphic< ClassOfSize<n> >::value);
}

void testAlignmentIssues(ClassOfSize<0> const & x)
{
	doTestAlignmentIssues(x);
}

template<int n> void testAlignmentIssues(ClassOfSize<n> const & x)
{
	doTestAlignmentIssues(x);
	testAlignmentIssues(ClassOfSize<n-1>());
}

void testAlignmentIssues()
{
	testAlignmentIssues(ClassOfSize< sizeof(void*) * 2 >());
}
//------------------------------------------------------------------------------
/*
	This test checks classes that are naturally non-polymorphic.
	The TestAlignmentIssues does the same but does it better.
	Thus this test is not much useful but let it be.
*/
void testNaturallyNonPolymorphic()
{
	ASSERT_FALSE(IsPolymorphic< NonVirtualClass1 >::value);
	ASSERT_FALSE(IsPolymorphic< NonVirtualClass2_1 >::value);
	ASSERT_FALSE(IsPolymorphic< NonVirtualClass3_1 >::value);
	ASSERT_FALSE(IsPolymorphic< NonVirtualClass4_2_3 >::value);
	ASSERT_FALSE(IsPolymorphic< NonVirtualClass2 >::value);
	ASSERT_FALSE(IsPolymorphic< NonVirtualClass3 >::value);
	ASSERT_FALSE(IsPolymorphic< NonVirtualClass4 >::value);
	ASSERT_FALSE(IsPolymorphic< NonVirtualClass5 >::value);
}
//------------------------------------------------------------------------------
/*
	This test ensures that all naturally polymorphic classes are detected as polymorphic.
*/
void testNaturallyPolymorphic()
{
	//This class are naturally polymorphic
	ASSERT_TRUE(IsPolymorphic< VirtualByDestructor >::value);
	ASSERT_TRUE(IsPolymorphic< VirtualByFunction >::value);
	ASSERT_TRUE(IsPolymorphic< VirtualByPureFunction >::value);
	ASSERT_TRUE(IsPolymorphic< VirtualBaseClass >::value);
	ASSERT_TRUE(IsPolymorphic< VirtualDerivedClass1 >::value);
	ASSERT_TRUE(IsPolymorphic< VirtualDerivedClass2 >::value);
	ASSERT_TRUE(IsPolymorphic< VirtualCommonDerived >::value);
}
//------------------------------------------------------------------------------
/*
	This test ensures that classes that have non-virtual hierarchy root and have
	added virtuality later in the hierarchy tree are detected as polymorphic.
*/
void testPolymorphized()
{
	//This classes 
	ASSERT_TRUE(IsPolymorphic< ClassThatAddsVirtuality1 >::value);
	ASSERT_TRUE(IsPolymorphic< ClassThatAddsVirtuality2 >::value);
	ASSERT_TRUE(IsPolymorphic< Virtualizer<NonVirtualClass1> >::value);
	ASSERT_TRUE(IsPolymorphic< Virtualizer<NonVirtualClass2_1> >::value);
	ASSERT_TRUE(IsPolymorphic< Virtualizer<NonVirtualClass3_1> >::value);
	ASSERT_TRUE(IsPolymorphic< Virtualizer<NonVirtualClass4_2_3> >::value);
	ASSERT_TRUE(IsPolymorphic< Virtualizer<NonVirtualClass2> >::value);
	ASSERT_TRUE(IsPolymorphic< Virtualizer<NonVirtualClass3> >::value);
	ASSERT_TRUE(IsPolymorphic< Virtualizer<NonVirtualClass4> >::value);
	ASSERT_TRUE(IsPolymorphic< Virtualizer<NonVirtualClass5> >::value);
}
//------------------------------------------------------------------------------
/*
	This test ensures that classes that use virtual inheritance, but does not
	have any virtual functions are detected as non-polymorphic.
*/
void testVirtualInheritanceDoesNotMakeClassesPolymorphic()
{
	ASSERT_FALSE(IsPolymorphic< VirtualInhLeft >::value);
	ASSERT_FALSE(IsPolymorphic< VirtualInhRight >::value);
	ASSERT_FALSE(IsPolymorphic< VirtualInhBottom >::value);
}
//------------------------------------------------------------------------------
/*
	This test ensures that classes that have virtual functions, but use virtual
	inheritance still are polymorphic.
*/
void testVirtualInheritanceDoesNotExcludePolymorphism()
{
	ASSERT_TRUE(IsPolymorphic< VirtualInhExtraL >::value);
	ASSERT_TRUE(IsPolymorphic< VirtualInhExtraR >::value);
	ASSERT_TRUE(IsPolymorphic< VirtualInhExtraX >::value);
}
//------------------------------------------------------------------------------
int main()
{
	testCompilability();
	testAlignmentIssues();
	testNaturallyNonPolymorphic();
	testNaturallyPolymorphic();
	testPolymorphized();
	testVirtualInheritanceDoesNotMakeClassesPolymorphic();
	testVirtualInheritanceDoesNotExcludePolymorphism();
	return 0;
}