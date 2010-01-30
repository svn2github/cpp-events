// Copyright (c) 2010 Nickolas Pohilets
//
// This file is a part of the CppEvents library.
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

namespace Cpp {
//------------------------------------------------------------------------------
class POSIX_ThreadData
{
public:
	POSIX_ThreadData() { }
	~POSIX_ThreadData() { assert(ref_.isNull()); }

	void lock()
	{
		mutex_.lock();
	}

	void unlock()
	{
		mutex_.unlock();
	}

	void retain()
	{
		ref_.retain();
	}

	void release()
	{
		if(ref_.release())
		{
			delete this;
		}
	}

private:
	AtomicInt ref_;
	RecursiveMutex mutex_;
};
//------------------------------------------------------------------------------
typedef ThreadStorage<POSIX_ThreadData*> ThreadDataStorage;
static char storageBytes[sizeof(ThreadDataStorage)];
static ThreadDataStorage * storage = 0;
//------------------------------------------------------------------------------
void Threading::constructProcessData()
{
	assert(!storage);
	storage = new(storageBytes) ThreadDataStorage();
	constructThreadData();
}
//------------------------------------------------------------------------------
void Threading::destructProcessData()
{
	destructThreadData();
	assert(storage);
	storage->~ThreadDataStorage();
	storage = 0;
}
//------------------------------------------------------------------------------
void Threading::constructThreadData()
{
	assert(storage);
	assert(!storage->data());
	POSIX_ThreadData * data = new POSIX_ThreadData();
	data->retain();
	storage->setData(data);
}
//------------------------------------------------------------------------------
void Threading::destructThreadData()
{
	assert(storage);
	POSIX_ThreadData * data = storage->data();
	assert(data);
	data->release();
	storage->setData(0);
}
//------------------------------------------------------------------------------
Threading::ThreadData * Threading::currentThreadData()
{
	assert(storage);
	POSIX_ThreadData * data = storage->data();
	assert(data);
	return reinterpret_cast<Threading::ThreadData*>(data);
}
//------------------------------------------------------------------------------
void Threading::ThreadData::lock()
{
	reinterpret_cast<POSIX_ThreadData*>(this)->lock();
}
//------------------------------------------------------------------------------
void Threading::ThreadData::unlock()
{
	reinterpret_cast<POSIX_ThreadData*>(this)->lock();
}
//------------------------------------------------------------------------------
void Threading::ThreadData::retain()
{
	reinterpret_cast<POSIX_ThreadData*>(this)->retain();
}
//------------------------------------------------------------------------------
void Threading::ThreadData::release()
{
	reinterpret_cast<POSIX_ThreadData*>(this)->release();
}
//------------------------------------------------------------------------------
} //namespace Cpp
