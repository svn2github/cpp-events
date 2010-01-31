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
#include <Cpp/Threading/Thread.hpp>
#include <Cpp/Threading/RecursiveMutex.hpp>
#include <Cpp/Utils/Random.hpp>
#include <gtest/gtest.h>

namespace UnitTests {
namespace Threading {
namespace SyncOneToMany {
//------------------------------------------------------------------------------
class EventSender
{
public:
	Cpp::EventRef<> theEvent() { return theEvent_; }
	void fire() { theEvent_.fire(); }
private:
	Cpp::Event<> theEvent_;
};
//------------------------------------------------------------------------------
class EventHandler
{
public:
	EventHandler()
	{
		connectionCount_ = 0;
		callbackCounter_ = 0;
	}

	void trigger()
	{
		callbackCounter_ = connectionCount_;
	}
	
	void onEvent()
	{
		--callbackCounter_;
	}
	
	void check()
	{
		if(callbackCounter_)
		{
			ASSERT_EQ(0, callbackCounter_);
		}
	}

	void connect(Cpp::ConnectionScope * scope, EventSender * sender)
	{
		scope->connect(sender->theEvent(), this, &EventHandler::onEvent);
		++connectionCount_;
	}

	void disconnect(Cpp::ConnectionScope * scope, EventSender * sender)
	{
		bool ok = scope->disconnectOne(sender->theEvent());
		if(ok) --connectionCount_;
	}

	void disconneclAll(Cpp::ConnectionScope * scope)
	{
		scope->disconnectAll();
		connectionCount_ = 0;
	}
private:
	int connectionCount_;
	int callbackCounter_;
};
//------------------------------------------------------------------------------
class HandlerThread : public Cpp::Thread
{
public:
	Cpp::RecursiveMutex mutex_;
	EventHandler handler_;

	void start(EventSender * sender, Cpp::AtomicInt * threadCounter, unsigned long z, unsigned long w, bool isMain)
	{
		sender_ = sender;
		isMain_ = isMain;
		threadCounter_ = threadCounter;
		m_z = z; m_w = w;
		Thread::start();
	}
protected:
	virtual void run()
	{
		Cpp::Events::ThreadInit threadInit;

		Cpp::ConnectionScope scope;

		Cpp::WikiRandom rnd(m_z, m_w);

		for(int i=0; i<100; ++i)
		{
			if(isMain_)
			{
				std::cout << i << "% " << std::flush;
				if((i % 10) == 9) std::cout << std::endl;
			}


			for(int j=0; j<500; ++j)
			{
				mutex_.lock();

				unsigned long k = rnd.generate() % 7;

				if(k < 4) // 0,1,2,3
					handler_.connect(&scope, sender_);
				else // 4,5,6
					handler_.disconnect(&scope, sender_);

				mutex_.unlock();
			}
		}

		mutex_.lock();
		handler_.disconneclAll(&scope);
		mutex_.unlock();

		threadCounter_->release();
	}
private:
	EventSender * sender_;
	bool isMain_;
	Cpp::AtomicInt * threadCounter_;

	unsigned long m_z;
	unsigned long m_w;
};
//------------------------------------------------------------------------------
/*
	This test check synchronization in the ConnectionScope class.
*/
TEST(Test_Threading, SyncOneToMany)
{
	static int const threadCount = 4;

	HandlerThread threads[threadCount];
	Cpp::RecursiveMutex * mutexArr[threadCount];
	EventSender sender;

	Cpp::AtomicInt threadCounter(threadCount);

	for(int i=0; i<threadCount; ++i)
	{
		mutexArr[i] = &threads[i].mutex_;
	}

	std::cout << "Running test in " << threadCount << " threads." << std::endl;
	std::cout << "This may take up to several minutes, please wait..." << std::endl;

	Cpp::WikiRandom rnd(1234, 5678);

	unsigned long prevX = rnd.generate();

	for(int i=0; i<threadCount; ++i)
	{
		unsigned long x = rnd.generate();
		threads[i].start(&sender, &threadCounter, prevX, x, (i==0));
		prevX = x;
	}

	while(!threadCounter.isNull())
	{
		// Lock all mutexes
		for(int i=0; i<threadCount; ++i)
		{
			mutexArr[i]->lock();
		}

		for(int i=0; i<threadCount; ++i)
		{
			threads[i].handler_.trigger();
		}

		sender.fire();

		for(int i=0; i<threadCount; ++i)
		{
			threads[i].handler_.check();
		}

		// Unlock all mutexes
		for(int i=0; i<threadCount; ++i)
		{
			mutexArr[i]->unlock();
		}

		// Rotate mutexes
		Cpp::RecursiveMutex * tmp = mutexArr[0];
		for(int i=1; i<threadCount; ++i)
		{
			mutexArr[i-1] = mutexArr[i];
		}
		mutexArr[threadCount-1] = tmp;
	}

	for(int i=0; i<threadCount; ++i)
	{
		threads[i].join();
	}

	std::cout << "Done!" << std::endl;
}
//------------------------------------------------------------------------------
} //namespace SyncOneToMany
} //namespace Threading
} //namespace UnitTests
