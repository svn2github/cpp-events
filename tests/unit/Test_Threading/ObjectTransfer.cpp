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

namespace UnitTests {
namespace Threading {
namespace ObjectTransfer {
//------------------------------------------------------------------------------
class EventSender
{
public:
	EventSender() {}
	~EventSender() {}

	Cpp::EventRef<> testEvent() { return testEvent_; }

	void fireEvent() { testEvent_.fire(); }
private:
	Cpp::Event<> testEvent_;
};
//------------------------------------------------------------------------------
typedef std::vector<EventSender*> ObjectArray;
//------------------------------------------------------------------------------
class ObjectMakerThread : public Thread
{
public:
	ObjectMakerThread() { }
	~ObjectMakerThread() {}

	void takeObjects(ObjectArray & retVal)
	{
		retVal.swap(objects_);
		objects_.clear();
	}

	void start(int objectCount)
	{
		objectCount_ = objectCount;
		Thread::start();
	}
protected:
	virtual void run()
	{
		Cpp::Events::ThreadInit threadInit;

		while(objectCount_ > 0)
		{
			objects_.push_back(new EventSender());
			--objectCount_;
		}
	}
private:
	ObjectArray objects_;
	int objectCount_;
};
//------------------------------------------------------------------------------
class EventHandler
{
public:
	EventHandler() { counter_ = 0; }
	int counter() const { return counter_; }

	void handle() { ++counter_; }
private:
	int counter_;
};
//------------------------------------------------------------------------------
/*
	This test if object created in one thread can be used in the another thread,
	when original thread is already finished.
*/
TEST(Test_Threading, ObjectTransfer)
{
	for(int objectCount=0; objectCount<=4; ++objectCount)
	{
		ObjectArray objects;
		{
			ObjectMakerThread thread;
			thread.start(objectCount);
			thread.join();
			thread.takeObjects(objects);
		}

		assert(objects.size() == objectCount);

		EventHandler handler;
		Cpp::ConnectionScope scope;

		for(size_t j=0; j<objects.size(); ++j)
		{
			scope.connect(objects[j]->testEvent(), &handler, &EventHandler::handle);
		}

		for(size_t j=0; j<objects.size(); ++j)
		{
			objects[j]->fireEvent();
		}

		ASSERT_EQ(objects.size(), handler.counter());

		for(size_t j=0; j<objects.size(); ++j)
		{
			delete objects[j];
		}
	}
}
//------------------------------------------------------------------------------
} //namespace ObjectTransfer
} //namespace Threading
} //namespace UnitTests
