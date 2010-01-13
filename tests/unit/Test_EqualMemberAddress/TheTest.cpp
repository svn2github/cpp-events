#include "TestClass.hpp"
#include <gtest/gtest.h>

void getTestData4(TestDataArray * d)
{
	GET_TEST_DATA_IMPL();
}

typedef void (*TestDataFunc)(TestDataArray *);
static TestDataFunc const testDataFuncs[] = 
{
	&getTestData1, &getTestData2,
	&getTestData3, &getTestData4,
};

static int const testDataFuncCount = sizeof(testDataFuncs) / sizeof(testDataFuncs[0]);

template<class T> bool operator==(FunctionData<T> const & a, FunctionData<T> const & b)
{
	for(int i = 0; i<sizeof(T); ++i)
	{
		if(a.rawData[i] != b.rawData[i])
			return false;
	}
	return true;
}

template<class T> std::ostream & operator << (std::ostream & os, FunctionData<T> const & b)
{
	for(int j = sizeof(T); j > 0; )
	{
		--j;
		os << std::hex << std::setw(2) << std::setfill('0') << (int)b.rawData[j];
	}
	return os;
}

////////////////////////////////////////////////////////////////////////////////
// This test ensures that member functions generated in different translation
// units have have equal addresses.
TEST(Test_EqualMemberAddress, TheTest)
{
	TestDataArray a;
	TestDataArray b;

	(*testDataFuncs[0])(&a);

	for(int i=1; i<testDataFuncCount; ++i)
	{
		(*testDataFuncs[i])(&b);

		//if(i == 1) ++b.templateData[2].rawData[0];

		for(int j=0; j<TestCaseCount; ++j)
		{
			ASSERT_EQ(a.classData[j], b.classData[j]);
			ASSERT_EQ(a.templateData[j], b.templateData[j]);
		}
	}
}
