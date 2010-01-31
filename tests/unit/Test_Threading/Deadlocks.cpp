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

#include "../Test_ConnectDisconnect/TestClasses.hpp"
#include <gtest/gtest.h>
#include <Cpp/Threading/Thread.hpp>
#include <Std/Assert.hpp>
#include <Std/Vector.hpp>

namespace UnitTests {
namespace Threading {
namespace Deadlocks {
//------------------------------------------------------------------------------
using UnitTests::ConnectDisconnect::Sender;
using UnitTests::ConnectDisconnect::Reciever;
using UnitTests::ConnectDisconnect::SenderEx;
using UnitTests::ConnectDisconnect::RecieverEx;
//------------------------------------------------------------------------------
/*
	This test checks deadlocks in basic connection management                          
*/
class ManualConnectDisconnectThread : public Cpp::Thread
{
public:
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
//------------------------------------------------------------------------------
void ManualConnectDisconnectThread::run()
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
//------------------------------------------------------------------------------
TEST(Test_Threading, ManualConnectDisconnectDeadlocks)
{
	Sender sender;
	ManualConnectDisconnectThread thread;
	thread.start(&sender);
	thread.join();
}
//------------------------------------------------------------------------------
/*
	This test checks deadlocks in automatic disconnection
*/
class AutomaticDisconnectThread_1_1_1 : public Cpp::Thread
{
public:
	void start(Sender * sender, Reciever * r1)
	{
		sender_ = sender;
		r1_ = r1;
		Thread::start();
	}
protected:
	virtual void run()
	{
		Cpp::Events::ThreadInit threadInit;

		Cpp::ConnectionScope scope1;
		scope1.connect(sender_->somethingHappened(), r1_, &Reciever::increment);
		ASSERT_EQ(0, r1_->value());
		sender_->fire();
		ASSERT_EQ(1, r1_->value());
	}
private:
	Sender * sender_;
	Reciever * r1_;
};
//------------------------------------------------------------------------------
class AutomaticDisconnectThread_1_1_2 : public Cpp::Thread
{
public:
	void start(Sender * sender, Reciever * r1)
	{
		sender_ = sender;
		r1_ = r1;
		Thread::start();
	}
protected:
	virtual void run()
	{
		Cpp::Events::ThreadInit threadInit;

		Cpp::ConnectionScope scope2;
		scope2.connect(sender_->somethingHappened(), r1_, &Reciever::decrement);
		ASSERT_EQ(1, r1_->value());
		sender_->fire();
		ASSERT_EQ(0, r1_->value());
	}
private:
	Sender * sender_;
	Reciever * r1_;
};
//------------------------------------------------------------------------------
class AutomaticDisconnectThread_1_1_3 : public Cpp::Thread
{
public:
	void start(Cpp::ConnectionScope * scope0, Sender * sender, Reciever * r0)
	{
		scope0_ = scope0;
		sender_ = sender;
		r0_ = r0;
		Thread::start();
	}
protected:
	virtual void run()
	{
		Cpp::Events::ThreadInit threadInit;

		scope0_->connect(sender_->somethingHappened(), r0_, &Reciever::setValue, 5);
		sender_->fire();
		ASSERT_EQ(5, r0_->value());
		r0_->setValue(-1);
		sender_->fire();
		ASSERT_EQ(5, r0_->value());
	}
private:
	Cpp::ConnectionScope * scope0_;
	Sender * sender_;
	Reciever * r0_;
};
//------------------------------------------------------------------------------
class AutomaticDisconnectThread_1_1 : public Cpp::Thread
{
public:
	void start(Cpp::ConnectionScope * scope0, Sender * sender, Reciever * r0)
	{
		scope0_ = scope0;
		sender_ = sender;
		r0_ = r0;
		Thread::start();
	}
protected:
	virtual void run()
	{
		Cpp::Events::ThreadInit threadInit;

		Reciever r1;
		{
			AutomaticDisconnectThread_1_1_1 thread;
			thread.start(sender_, &r1);
			thread.join();
		}
		sender_->fire();
		ASSERT_EQ(1, r1.value());
		{
			AutomaticDisconnectThread_1_1_2 thread;
			thread.start(sender_, &r1);
			thread.join();
		}
		sender_->fire();
		ASSERT_EQ(0, r1.value());

		{
			AutomaticDisconnectThread_1_1_3 thread;
			thread.start(scope0_, sender_, r0_);
			thread.join();
		}
	}
private:
	Cpp::ConnectionScope * scope0_;
	Sender * sender_;
	Reciever * r0_;
};
//------------------------------------------------------------------------------
class AutomaticDisconnectThread_1 : public Cpp::Thread
{
public:
	void start(Cpp::ConnectionScope * scope0, Reciever * r0)
	{
		scope0_ = scope0;
		r0_ = r0;
		Thread::start();
	}
protected:
	virtual void run()
	{
		Cpp::Events::ThreadInit threadInit;

		Sender sender;

		sender.fire();
		{
			AutomaticDisconnectThread_1_1 thread;
			thread.start(scope0_, &sender, r0_);
			thread.join();
		}
		r0_->setValue(-1);
		sender.fire();
		ASSERT_EQ(5, r0_->value());
		ASSERT_NE(0, scope0_->connectionCount());
	}
private:
	Cpp::ConnectionScope * scope0_;
	Reciever * r0_;
};
//------------------------------------------------------------------------------
TEST(Test_Threading, AutomaticDisconnectDeadlocks)
{
	Cpp::ConnectionScope scope0;
	Reciever r0;
	{
		AutomaticDisconnectThread_1 thread;
		thread.start(&scope0, &r0);
		thread.join();
	}
	ASSERT_EQ(0, scope0.connectionCount());
}
//------------------------------------------------------------------------------
/*
	This test ensures that adding connections inside delegate does not cause deadlock.
*/
class ConnectFromDelegateThread : public Cpp::Thread
{
public:
	static int const arraySize = 8;
	typedef RecieverEx RecieverArray[arraySize];

	void start(Cpp::ConnectionScope * scope, RecieverArray * rcvArr)
	{
		scope_ = scope;
		rcvArr_ = rcvArr;
	}
protected:
	virtual void run()
	{
		Cpp::Events::ThreadInit threadInit;

		SenderEx sender;

		RecieverArray & rcv = *rcvArr_;

		rcv[0].connect(0, arraySize, &sender, scope_);

		ASSERT_EQ(0, rcv[0].value());
		ASSERT_EQ(0, rcv[1].value());
		ASSERT_EQ(0, rcv[2].value());
		ASSERT_EQ(0, rcv[3].value());
		ASSERT_EQ(0, rcv[4].value());
		ASSERT_EQ(0, rcv[5].value());
		ASSERT_EQ(0, rcv[6].value());
		ASSERT_EQ(0, rcv[7].value());
		ASSERT_EQ(1, sender.somethingHappened().connectionCount());

		sender.runStage();
		ASSERT_EQ(1, rcv[0].value());
		ASSERT_EQ(0, rcv[1].value());
		ASSERT_EQ(0, rcv[2].value());
		ASSERT_EQ(0, rcv[3].value());
		ASSERT_EQ(0, rcv[4].value());
		ASSERT_EQ(0, rcv[5].value());
		ASSERT_EQ(0, rcv[6].value());
		ASSERT_EQ(0, rcv[7].value());
		ASSERT_EQ(2, sender.somethingHappened().connectionCount());

		sender.runStage();
		ASSERT_EQ(2, rcv[0].value());
		ASSERT_EQ(1, rcv[1].value());
		ASSERT_EQ(0, rcv[2].value());
		ASSERT_EQ(0, rcv[3].value());
		ASSERT_EQ(0, rcv[4].value());
		ASSERT_EQ(0, rcv[5].value());
		ASSERT_EQ(0, rcv[6].value());
		ASSERT_EQ(0, rcv[7].value());
		ASSERT_EQ(4, sender.somethingHappened().connectionCount());

		sender.runStage();
		ASSERT_EQ(3, rcv[0].value());
		ASSERT_EQ(2, rcv[1].value());
		ASSERT_EQ(1, rcv[2].value());
		ASSERT_EQ(1, rcv[3].value());
		ASSERT_EQ(0, rcv[4].value());
		ASSERT_EQ(0, rcv[5].value());
		ASSERT_EQ(0, rcv[6].value());
		ASSERT_EQ(0, rcv[7].value());
		ASSERT_EQ(8, sender.somethingHappened().connectionCount());

		sender.runStage();
		ASSERT_EQ(4, rcv[0].value());
		ASSERT_EQ(3, rcv[1].value());
		ASSERT_EQ(2, rcv[2].value());
		ASSERT_EQ(2, rcv[3].value());
		ASSERT_EQ(1, rcv[4].value());
		ASSERT_EQ(1, rcv[5].value());
		ASSERT_EQ(1, rcv[6].value());
		ASSERT_EQ(1, rcv[7].value());
		ASSERT_EQ(8, sender.somethingHappened().connectionCount());
	}
private:
	Cpp::ConnectionScope * scope_;
	RecieverArray * rcvArr_;
};
//------------------------------------------------------------------------------
TEST(Test_Threading, ConnectFromDelegateDeadlocks)
{
	ConnectFromDelegateThread::RecieverArray rcv;
	Cpp::ConnectionScope scope;

	ConnectFromDelegateThread thread;
	thread.start(&scope, &rcv);
	thread.join();
}
//------------------------------------------------------------------------------
} //namespace Deadlocks
} //namespace Threading
} //namespace UnitTests