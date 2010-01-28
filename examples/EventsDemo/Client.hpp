// Copyright (c) 2010 Nickolas Pohilets
//
// This file is a part of the sandbox project for the CppEvents library.
//
// It is used for development purposes only and is not a part of the
// public distribution.
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

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <Cpp/Events.hpp>

class ISomeInterface
{
protected:
	ISomeInterface() {}
	~ISomeInterface() {}
public:
	virtual Cpp::EventRef<bool> testEvent1() = 0;
};

class BaseClass
{
public:
	BaseClass() {}
	virtual ~BaseClass() {}

	virtual Cpp::EventRef<int> testEvent2() { return testEvent2_ ; }

	void fireEvent2(int x) { testEvent2_.fire(x); }
private:
	Cpp::Event<int> testEvent2_;
};

class DerivedClass : public BaseClass, public ISomeInterface
{
public:
	DerivedClass()
		: BaseClass()
	{
		scope_.connectEvent(BaseClass::testEvent2(), &testEvent2x_);
		scope_.connectEvent(BaseClass::testEvent2(), &eventEx_, 3.14);
	}
	~DerivedClass() {}

	virtual Cpp::EventRef<int> testEvent2() { return testEvent2x_ ; }
	virtual Cpp::EventRef<bool> testEvent1() { return testEvent1_ ; }
private:
	Cpp::Event<bool> testEvent1_;
	Cpp::Event<int> testEvent2x_;
	Cpp::Event<double, int> eventEx_;
	Cpp::ConnectionScope scope_;
};

class Server;

class Client
{
public:
	Client();
	~Client();

	Server * server() const { return server_; }
	void setServer(Server * serv);

	void test();

	void registerData(Server * server);

	Cpp::ConnectionScope * tracker() { return &scope_; }
private:
	Server * server_;
	Cpp::ConnectionScope scope_;

	void processData(float x);
};

#endif //CLIENT_HPP