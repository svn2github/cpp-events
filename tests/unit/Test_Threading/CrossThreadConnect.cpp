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

#include <Cpp/Events.hpp>
#include <gtest/gtest.h>
#include <Cpp/Threading/Thread.hpp>
#include <Std/Assert.hpp>
#include <Std/Vector.hpp>

namespace /*anonymous*/ {

class Sender
{
public:
	void fire() { somethingHappened_.fire(); }
	Cpp::EventRef<> somethingHappened() { return somethingHappened_; }
private:
	Cpp::Event<> somethingHappened_;
};

class Reciever
{
public:
	Reciever() : val_() {}

	void increment() { ++val_; }
	void decrement() { --val_; }
	int value() const { return val_; }
	void setValue(int v) { val_ = v; }
private:
	int val_;
};

class WorkerThread : public Thread
{
public:
	WorkerThread() { }
	~WorkerThread() {}

	void start(Sender * sender)
	{
		sender_ = sender;
		Thread::start();
	}
protected:
	virtual void run();
private:
	Sender * sender_;
};

void WorkerThread::run()
{
	Cpp::Events::ThreadInit threadInit;

	Reciever r1, r2;
	Cpp::ConnectionScope scope;

	ASSERT_EQ(0, r1.value()); ASSERT_EQ(0, r2.value());
	sender_->fire();
	ASSERT_EQ(0, r1.value()); ASSERT_EQ(0, r2.value());

	scope.connect(sender_->somethingHappened(), &r1, &Reciever::increment);
	sender_->fire();	// +1-0 +0-0
	ASSERT_EQ(1, r1.value()); ASSERT_EQ(0, r2.value());
	sender_->fire();	// +1-0 +0-0
	ASSERT_EQ(2, r1.value()); ASSERT_EQ(0, r2.value());

	scope.connect(sender_->somethingHappened(), &r2, &Reciever::increment);
	sender_->fire();	// +1-0 +1-0
	ASSERT_EQ(3, r1.value()); ASSERT_EQ(1, r2.value());

	scope.connect(sender_->somethingHappened(), &r1, &Reciever::decrement);
	sender_->fire();	// +1-1 +1-0
	ASSERT_EQ(3, r1.value()); ASSERT_EQ(2, r2.value());

	scope.connect(sender_->somethingHappened(), &r1, &Reciever::decrement);
	sender_->fire();	// +1-2 +1-0
	ASSERT_EQ(2, r1.value()); ASSERT_EQ(3, r2.value());

	scope.connect(sender_->somethingHappened(), &r2, &Reciever::decrement);
	sender_->fire();	// +1-2 +1-1
	ASSERT_EQ(1, r1.value()); ASSERT_EQ(3, r2.value());

	scope.connect(sender_->somethingHappened(), &r2, &Reciever::increment);
	sender_->fire();	// +1-2 +2-1
	ASSERT_EQ(0, r1.value()); ASSERT_EQ(4, r2.value());

	sender_->somethingHappened().disconnectAll(&r2, &Reciever::decrement);
	sender_->fire();	// +1-2 +2-0
	ASSERT_EQ(-1, r1.value()); ASSERT_EQ(6, r2.value());

	sender_->somethingHappened().disconnectOne(&r1, &Reciever::decrement);
	sender_->fire();	// +1-1 +2-0
	ASSERT_EQ(-1, r1.value()); ASSERT_EQ(8, r2.value());

	sender_->somethingHappened().disconnectAll(&r1, &Reciever::increment);
	sender_->fire();	// +0-1 +2-0
	ASSERT_EQ(-2, r1.value()); ASSERT_EQ(10, r2.value());

	sender_->somethingHappened().disconnectOne(&r2, &Reciever::increment);
	sender_->fire();	// +0-1 +1-0
	ASSERT_EQ(-3, r1.value()); ASSERT_EQ(11, r2.value());

	sender_->somethingHappened().disconnectAll();
	sender_->fire();	// +0-0 +0-0
	ASSERT_EQ(-3, r1.value()); ASSERT_EQ(11, r2.value());
}

} //namespace /*anonymous*/

TEST(Test_Threading, CrossThreadConnect)
{
	Sender sender;
	WorkerThread thread;
	thread.start(&sender);
	thread.join();
}