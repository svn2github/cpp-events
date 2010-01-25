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
