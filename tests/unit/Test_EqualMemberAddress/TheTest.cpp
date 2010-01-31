// Copyright (c) 2010 Nickolas Pohilets
//
// This file is a part of the unit test suit for the CppEvents library.
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

#include "TestClass.hpp"
#include <gtest/gtest.h>

namespace UnitTests {
namespace EqualMemberAddress {
//------------------------------------------------------------------------------
void getTestData4(TestDataArray * d)
{
#include "GetTestData.inl"
}
//------------------------------------------------------------------------------
typedef void (*TestDataFunc)(TestDataArray *);
static TestDataFunc const testDataFuncs[] = 
{
	&getTestData1, &getTestData2,
	&getTestData3, &getTestData4,
};
static int const testDataFuncCount = sizeof(testDataFuncs) / sizeof(testDataFuncs[0]);
//------------------------------------------------------------------------------
template<class T> bool operator==(FunctionData<T> const & a, FunctionData<T> const & b)
{
	for(int i = 0; i<sizeof(T); ++i)
	{
		if(a.rawData[i] != b.rawData[i])
			return false;
	}
	return true;
}
//------------------------------------------------------------------------------
template<class T> std::ostream & operator << (std::ostream & os, FunctionData<T> const & b)
{
	for(int j = sizeof(T); j > 0; )
	{
		--j;
		os << std::hex << std::setw(2) << std::setfill('0') << (int)b.rawData[j];
	}
	return os;
}
//------------------------------------------------------------------------------
/*
	This test ensures that member functions generated in different translation
	units have have equal addresses.
*/
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
//------------------------------------------------------------------------------
} //namespace ConnectDisconnect
} //namespace UnitTests