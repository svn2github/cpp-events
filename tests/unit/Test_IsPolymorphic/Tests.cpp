#include "../../../src/Cpp/Events/AbstractObjectRef.hpp"
#include "TestClasses.hpp"
#include <gtest/gtest.h>

using Cpp::Private::Events::IsPolymorphic;

////////////////////////////////////////////////////////////////////////////////
// For checking polymorphy special template class is derived from class being tested.
// This potentially may cause compilation problems if some special members of base class are inaccessible.
// This test is designed for detecting these problems. Test is passed if it compiles.
TEST(Test_IsPolymorphic, Compilability)
{
	bool const b = IsPolymorphic<ClassWithUndefinedPrivateCtorAndDtor>::value;
	(void)b;
}

////////////////////////////////////////////////////////////////////////////////
// Class alignment may possibly cause false detection of polymorphic classes.
// This test is designed for detecting them.

namespace {
	template<int n> void doTestAlignmentIssues(ClassOfSize<n> const & x)
	{
		ASSERT_FALSE(IsPolymorphic< ClassOfSize<n> >::value);
	}

	template<int n> void testAlignmentIssues(ClassOfSize<n> const & x)
	{
		doTestAlignmentIssues(x);
		testAlignmentIssues(ClassOfSize<n-1>());
	}

	void testAlignmentIssues(ClassOfSize<0> const & x)
	{
		doTestAlignmentIssues(x);
	}
}


TEST(Test_IsPolymorphic, AlignmentIssues)
{
	testAlignmentIssues(ClassOfSize< sizeof(void*) * 2 >());
}

////////////////////////////////////////////////////////////////////////////////
// This test checks classes that are naturally non-polymorphic.
// The TestAlignmentIssues does the same but does it better.
// Thus this test is not much useful but let it be.
TEST(Test_IsPolymorphic, NaturallyNonPolymorphic)
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

////////////////////////////////////////////////////////////////////////////////
// This test ensures that all naturally polymorphic classes are detected as polymorphic.
TEST(Test_IsPolymorphic, NaturallyPolymorphic)
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

////////////////////////////////////////////////////////////////////////////////
// This test ensures that classes that have non-virtual hierarchy root and have
// added virtuality later in the hierarchy tree are detected as polymorphic.
TEST(Test_IsPolymorphic, Polymorphized)
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

////////////////////////////////////////////////////////////////////////////////
// This test ensures that classes that use virtual inheritance, but does not
// have any virtual functions are detected as non-polymorphic.
TEST(Test_IsPolymorphic, VirtualInheritanceDoesNotMakeClassesPolymorphic)
{
	ASSERT_FALSE(IsPolymorphic< VirtualInhLeft >::value);
	ASSERT_FALSE(IsPolymorphic< VirtualInhRight >::value);
	ASSERT_FALSE(IsPolymorphic< VirtualInhBottom >::value);
}

////////////////////////////////////////////////////////////////////////////////
// This test ensures that classes that have virtual functions, but use virtual
// inheritance still are polymorphic.
TEST(Test_IsPolymorphic, VirtualInheritanceDoesNotExcludePolymorphism)
{
	ASSERT_TRUE(IsPolymorphic< VirtualInhExtraL >::value);
	ASSERT_TRUE(IsPolymorphic< VirtualInhExtraR >::value);
	ASSERT_TRUE(IsPolymorphic< VirtualInhExtraX >::value);
}
