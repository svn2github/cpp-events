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
#include <Cpp/Utils/Random.hpp>
#include <gtest/gtest.h>

namespace UnitTests {
namespace Threading {
namespace SyncManyToOne {
//------------------------------------------------------------------------------
class EventSender;
//------------------------------------------------------------------------------
class EventHandler
{
public:
	Cpp::ConnectionScope scope;

	void onEvent(EventSender * sender);
};
//------------------------------------------------------------------------------
class EventSender
{
public:
	EventSender()
	{
		connectionCount_ = 0;
		callbackCounter_ = 0;
	}

	Cpp::EventRef<> theEvent() { return theEvent_; }
	
	void recieverCallback()
	{
		--callbackCounter_;
	}

	void connect(EventHandler * handler)
	{
		++connectionCount_;
		handler->scope.connect(this->theEvent(), handler, &EventHandler::onEvent, this);
	}

	void disconnect(EventHandler * handler)
	{
		bool ok = handler->scope.disconnectOne(this->theEvent());
		if(ok) --connectionCount_;
	}

	void fire()
	{
		callbackCounter_ = connectionCount_;
		theEvent_.fire();
		ASSERT_EQ(0, callbackCounter_);
	}
private:
	Cpp::Event<> theEvent_;
	int connectionCount_;
	int callbackCounter_;
};
//------------------------------------------------------------------------------
void EventHandler::onEvent(EventSender * sender)
{
	sender->recieverCallback();
}
//------------------------------------------------------------------------------
class SenderThread : public Cpp::Thread
{
public:
	void start(EventHandler * handler, unsigned long z, unsigned long w, bool isMain)
	{
		handler_ = handler;
		isMain_ = isMain;
		m_z = z; m_w = w;
		Thread::start();
	}
protected:
	virtual void run()
	{
		Cpp::Events::ThreadInit threadInit;

		EventSender sender;

		Cpp::WikiRandom rnd(m_z, m_w);

		for(int i=0; i<100; ++i)
		{
			if(isMain_) std::cout << i << "% " << std::flush;

			for(int j=0; j<500; ++j)
			{
				unsigned long k = rnd.generate() % 10;

				if(k < 4) // 0,1,2,3
					sender.connect(handler_);
				else if(k < 7) // 4,5,6
					sender.disconnect(handler_);
				else	// 7,8,9
					sender.fire();
			}
		}

		if(isMain_) std::cout << std::endl;
	}
private:
	EventHandler * handler_;

	bool isMain_;

	unsigned long m_z;
	unsigned long m_w;
};
//------------------------------------------------------------------------------
/*
	This test check synchronization in the ConnectionScope class.
*/
TEST(Test_Threading, SyncManyToOne)
{
	static int const threadCount = 12;

	SenderThread threads[threadCount];
	EventHandler handler;

	std::cout << "This test may take up to several minutes, please wait..." << std::endl;

	Cpp::WikiRandom rnd(1234, 5678);

	unsigned long prevX = rnd.generate();

	for(int i=0; i<threadCount; ++i)
	{
		unsigned long x = rnd.generate();
		threads[i].start(&handler, prevX, x, (i==0));
		prevX = x;
	}

	for(int i=0; i<threadCount; ++i)
	{
		threads[i].join();
	}

	std::cout << "Done!" << std::endl;
}
//------------------------------------------------------------------------------
} //namespace SyncManyToOne
} //namespace Threading
} //namespace UnitTests
