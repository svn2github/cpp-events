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

namespace UnitTests {
namespace EqualMemberAddress {
//------------------------------------------------------------------------------
static int magic = 0x11223344;
//------------------------------------------------------------------------------
int TestClass::testOutlineFunction()
{
	return someData_ * (int)reinterpret_cast<size_t>(&magic);
}
//------------------------------------------------------------------------------
int TestClass::testOutlineFunctionWithStaticVariable()
{
	static int staticVar = -1;
	staticVar += testOutlineFunction();
	return staticVar;
}
//------------------------------------------------------------------------------
void getTestData1(TestDataArray * d)
{
#include "GetTestData.inl"
}
//------------------------------------------------------------------------------
} //namespace ConnectDisconnect
} //namespace UnitTests