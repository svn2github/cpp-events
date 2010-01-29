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
  Check if pointers to virtual member functions point to exact implementation
  of the specified function or to the thunk that performs virtual call.

Motivation:
  Can't find exact information.

Results:
  * MSVC - VIRTUAL
*/

#include <iostream>

enum ClassId { BaseClassId, DerivedClassId };

class BaseClass
{
public:
	virtual void print() { std::cout << "BaseClass::print()" << std::endl; }
	virtual ClassId classId() { return BaseClassId; }
};

class DerivedClass : public BaseClass
{
public:
	virtual void print() { std::cout << "DerivedClass::print()" << std::endl; }
	virtual ClassId classId() { return DerivedClassId; }
};

typedef void (BaseClass::*PrintFunc)();
typedef ClassId (BaseClass::*ClassIdFunc)();

int main(int argc, char * argv[])
{
	DerivedClass obj;
	BaseClass * pObj = &obj;
	PrintFunc printFunc = &BaseClass::print;
	ClassIdFunc classIdFunc = &BaseClass::classId;
	(pObj->*printFunc)();
	ClassId id = (pObj->*classIdFunc)();
	std::cout << ((id == DerivedClassId) ? "virtual" : "non-virtual") << std::endl;
	return (id == DerivedClassId) ? 0 : 1;
}
