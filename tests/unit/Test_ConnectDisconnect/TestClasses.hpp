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

namespace UnitTests {
namespace ConnectDisconnect {
//------------------------------------------------------------------------------
class Sender
{
public:
	void fire() { somethingHappened_.fire(); }
	Cpp::EventRef<> somethingHappened() { return somethingHappened_; }
private:
	Cpp::Event<> somethingHappened_;
};
//------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------
class SenderEx : public Sender
{
public:
	SenderEx()
	{
		stageNo_ = 0; // 1 2 3 4 ...
		stageStep_ = 1; // 2 4 8 16 ...
	}

	int stageNo() const { return stageNo_; }
	int stageStep() const { return stageStep_; }

	void runStage()
	{
		fire();
		++stageNo_;
		stageStep_ *= 2;
	}
private:
	int stageNo_;
	int stageStep_;
};
//------------------------------------------------------------------------------
class RecieverEx
{
public:
	RecieverEx()
		: sender_()
		, scope_()
		, index_(-1)
		, val_()
	{}

	int index() const { return index_; }
	int value() const { return val_; }

	void connect(int ind, int arraySize, SenderEx * sender, Cpp::ConnectionScope * scope)
	{
		index_ = ind;
		arraySize_ = arraySize;
		sender_ = sender;
		scope_ = scope;
		scope->connect(sender->somethingHappened(), this, &RecieverEx::work);
	}

	void work()
	{
		++val_;

		int step = sender_->stageStep();
		int nextIndex = index_ + step;
		if(nextIndex < arraySize_)
		{
			RecieverEx * next = this + step;
			next->connect(nextIndex, arraySize_, sender_, scope_);
		}
	}
private:
	SenderEx * sender_;
	Cpp::ConnectionScope * scope_;
	int index_;
	int arraySize_;
	int val_;
};
//------------------------------------------------------------------------------
} //namespace ConnectDisconnect
} //namespace UnitTests