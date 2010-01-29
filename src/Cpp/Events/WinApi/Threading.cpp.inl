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

#include <windows.h>

namespace Cpp {
//------------------------------------------------------------------------------
class WinApi_ThreadData
{
public:
	WinApi_ThreadData()
	{
		InitializeCriticalSection(&cs_);
	}

	~WinApi_ThreadData()
	{
		assert(ref_.isNull());
		DeleteCriticalSection(&cs_);
	}

	void lock()
	{
		EnterCriticalSection(&cs_);
	}

	void unlock()
	{
		LeaveCriticalSection(&cs_);
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
	CRITICAL_SECTION cs_;
};
//------------------------------------------------------------------------------
static DWORD dwTlsIndex = 0;
//------------------------------------------------------------------------------
void Threading::constructProcessData()
{
	assert(!dwTlsIndex);
	dwTlsIndex = TlsAlloc();
	constructThreadData();
}
//------------------------------------------------------------------------------
void Threading::destructProcessData()
{
	destructThreadData();
	assert(dwTlsIndex);
	TlsFree(dwTlsIndex);
}
//------------------------------------------------------------------------------
void Threading::constructThreadData()
{
	assert(dwTlsIndex);
	assert(!TlsGetValue(dwTlsIndex));
	WinApi_ThreadData * data = new WinApi_ThreadData();
	data->retain();
	LPVOID pvTlsData = reinterpret_cast<LPVOID>(data);
	TlsSetValue(dwTlsIndex, pvTlsData);
}
//------------------------------------------------------------------------------
void Threading::destructThreadData()
{
	assert(dwTlsIndex);
	LPVOID pvTlsData = TlsGetValue(dwTlsIndex);
	assert(pvTlsData);
	WinApi_ThreadData * data = reinterpret_cast<WinApi_ThreadData*>(pvTlsData);
	data->release();
	TlsSetValue(dwTlsIndex, NULL);
}
//------------------------------------------------------------------------------
Threading::ThreadData * Threading::currentThreadData()
{
	assert(dwTlsIndex);
	LPVOID pvTlsData = TlsGetValue(dwTlsIndex);
	assert(pvTlsData);
	WinApi_ThreadData * data = reinterpret_cast<WinApi_ThreadData*>(pvTlsData);
	return reinterpret_cast<Threading::ThreadData*>(data);
}
//------------------------------------------------------------------------------
void Threading::ThreadData::lock()
{
	reinterpret_cast<WinApi_ThreadData*>(this)->lock();
}
//------------------------------------------------------------------------------
void Threading::ThreadData::unlock()
{
	reinterpret_cast<WinApi_ThreadData*>(this)->lock();
}
//------------------------------------------------------------------------------
void Threading::ThreadData::retain()
{
	reinterpret_cast<WinApi_ThreadData*>(this)->retain();
}
//------------------------------------------------------------------------------
void Threading::ThreadData::release()
{
	reinterpret_cast<WinApi_ThreadData*>(this)->release();
}
//------------------------------------------------------------------------------
} //namespace Cpp