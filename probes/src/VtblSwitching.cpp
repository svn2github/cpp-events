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
   Ensure that vtable switching works according to the standard.

Motivation:
   In Qt's implementation of signal-slot mechanism also has problem of late automatic
   disconnection in base class destructor, but vtable switching masks this problem in Qt.

Expected output:
	BaseClass::BaseClass(): vtbl = XXXXXXXX
	BaseClass::print()
	DerivedClass::DerivedClass(): vtbl = YYYYYYYY
	DerivedClass::print()
	----------------------
	DerivedClass::print()
	----------------------
	DerivedClass::print()
	DerivedClass::~DerivedClass(): vtbl = YYYYYYYY
	BaseClass::print()
	BaseClass::~BaseClass(): vtbl = YYYYYYYY		

Results:
	MSVC - PASSED
*/

#include <iostream>

class BaseClass;

class Tester
{
public:
	Tester()
	{
		baseVtbl_ = 0;
		derivedVtbl_ = 0;
		failed_ = false;
	}

	void baseCtor(BaseClass * obj);
	void derivedCtor(BaseClass * obj);
	void derivedDtor(BaseClass * obj);
	void baseDtor(BaseClass * obj);

	bool isFailed() const { return failed_; }

	void assert(bool expr, char const * exprStr);
private:
	void * baseVtbl_;
	void * derivedVtbl_;
	bool failed_;

	static void * getVtbl(BaseClass * obj);
};

#define ASSERT(X) assert(X, #X)

enum ClassId { BaseClassId, DerivedClassId };

class BaseClass
{
public:
	BaseClass(Tester * tester)
		: tester_(tester)
	{
		tester->baseCtor(this);
	}

	virtual ~BaseClass()
	{
		tester_->baseDtor(this);
	}

	virtual void print()
	{
		std::cout << "BaseClass::print()" << std::endl;
	}

	virtual ClassId classId() { return BaseClassId; }
protected:
	Tester * const tester_;
};

class DerivedClass : public BaseClass
{
public:
	DerivedClass(Tester * tester)
		: BaseClass(tester)
	{
		tester_->derivedCtor(this);
	}

	virtual ~DerivedClass()
	{
		tester_->derivedDtor(this);
	}

	virtual void print()
	{
		std::cout << "DerivedClass::print()" << std::endl;
	}

	virtual ClassId classId() { return DerivedClassId; }
};

inline void * Tester::getVtbl(BaseClass * obj)
{
	return *reinterpret_cast<void**>(obj);
}

void Tester::baseCtor(BaseClass * obj)
{
	baseVtbl_ = getVtbl(obj);
	std::cout << "BaseClass::BaseClass(): vtbl = " << getVtbl(obj) << std::endl;
	obj->print();
	ASSERT(obj->classId() == BaseClassId);
}

void Tester::derivedCtor(BaseClass *obj)
{
	derivedVtbl_ = getVtbl(obj);
	ASSERT(derivedVtbl_ != baseVtbl_);
	std::cout << "DerivedClass::DerivedClass(): vtbl = " << getVtbl(obj) << std::endl;
	obj->print();
	ASSERT(obj->classId() == DerivedClassId);
}

void Tester::derivedDtor(BaseClass * obj)
{
	ASSERT(obj->classId() == DerivedClassId);
	obj->print();
	std::cout << "DerivedClass::~DerivedClass(): vtbl = " << getVtbl(obj) << std::endl;
	ASSERT(derivedVtbl_ == getVtbl(obj));
}

void Tester::baseDtor(BaseClass * obj)
{
	ASSERT(obj->classId() == BaseClassId);
	obj->print();
	std::cout << "BaseClass::~BaseClass(): vtbl = " << getVtbl(obj) << std::endl;
	ASSERT(baseVtbl_ == getVtbl(obj));
}

void Tester::assert(bool expr, char const * exprStr)
{
	if(!expr)
	{
		failed_ = true;
		std::cout << " -- FAILED: \"" << exprStr << "\"" << std::endl;
	}
}

int main(int argc, char * argv[])
{
	Tester tester;
	tester.ASSERT(false && "Test failure");
	{
		DerivedClass obj(&tester);
		std::cout << "----------------------" << std::endl;
		obj.print();
		std::cout << "----------------------" << std::endl;
	}
	return tester.isFailed() ? 1 : 0;
}
