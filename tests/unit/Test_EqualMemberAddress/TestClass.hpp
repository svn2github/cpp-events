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

#ifndef TEST_CLASS__HPP
#define TEST_CLASS__HPP

#include <iostream>
#include <iomanip>

template<class T> class TestTemplate
{
public:
	int testInlineFunction() { return 0; }
	int testOutlineFunction();
	
	int testInlineFunctionWithStaticVariable()
	{
		static int staticVariable = 0;
		return ++staticVariable;
	}

	int testOutlineFunctionWithStaticVariable();
};

template<class T> int TestTemplate<T>::testOutlineFunction()
{
	int retVal = 0;
	for(int i=0; i<200 * sizeof(T); ++i)
	{
		std::cout << i << std::endl;
		retVal += i;
	}
	return retVal;
}

template<class T> int TestTemplate<T>::testOutlineFunctionWithStaticVariable()
{
	static int retVal = 14;
	retVal += (7 * sizeof(T) - retVal % 5);
	return retVal;
}

class TestClass
{
public:
	int testInlineFunction() { return someData_; }
	int testOutlineFunction();

	int testInlineFunctionWithStaticVariable()
	{
		static int staticVariable = 0;
		staticVariable += someData_; someData_ *= 2;
		return staticVariable;
	}

	int testOutlineFunctionWithStaticVariable();
private:
	char dummy[1];
	int someData_;
};

typedef int (TestClass::*TestClassFunction)();
typedef int (TestTemplate<TestClass>::*TestTemplateFunction)();

template<class T> union FunctionData
{
	T func;
	unsigned char rawData[sizeof(T)];
};

typedef FunctionData<TestClassFunction> TestClassFunctionData;
typedef FunctionData<TestTemplateFunction> TestTemplateFunctionData;

enum TestCases
{
	TestCase_InlineFunction,
	TestCase_OutlineFunction,
	TestCase_InlineFunctionWithStaticVariable,
	TestCase_OutlineFunctionWithStaticVariable,
	TestCaseCount
};

struct TestDataArray
{
	TestTemplateFunctionData templateData[TestCaseCount];
	TestClassFunctionData classData[TestCaseCount];
};

//Implemented in TestClass.cpp
extern void getTestData1(TestDataArray * d);
//Implemented in File1.cpp
extern void getTestData2(TestDataArray * d);
//Implemented in File2.cpp
extern void getTestData3(TestDataArray * d);
//Implemented in main.cpp
extern void getTestData4(TestDataArray * d);

#define GET_TEST_DATA_IMPL() \
	if(!d) return; \
	d->templateData[TestCase_InlineFunction].func = \
		&TestTemplate<TestClass>::testInlineFunction; \
	d->templateData[TestCase_OutlineFunction].func = \
		&TestTemplate<TestClass>::testOutlineFunction; \
	d->templateData[TestCase_InlineFunctionWithStaticVariable].func = \
		&TestTemplate<TestClass>::testInlineFunctionWithStaticVariable; \
	d->templateData[TestCase_OutlineFunctionWithStaticVariable].func = \
		&TestTemplate<TestClass>::testOutlineFunctionWithStaticVariable; \
	d->classData[TestCase_InlineFunction].func = \
		&TestClass::testInlineFunction; \
	d->classData[TestCase_OutlineFunction].func = \
		&TestClass::testOutlineFunction; \
	d->classData[TestCase_InlineFunctionWithStaticVariable].func = \
		&TestClass::testInlineFunctionWithStaticVariable; \
	d->classData[TestCase_OutlineFunctionWithStaticVariable].func = \
		&TestClass::testOutlineFunctionWithStaticVariable; \


#endif //TEST_CLASS__HPP
