#include "Threading.hpp"
#include <cassert>
#include <windows.h>
#include <intrin.h>

#pragma intrinsic (_InterlockedIncrement)
#pragma intrinsic (_InterlockedDecrement)

namespace Cpp {
//------------------------------------------------------------------------------
// Implementation-specific
class Threading::ThreadData
{
public:
	volatile LONG refCounter;
	CRITICAL_SECTION cs;

	ThreadData()
	{
		refCounter = 0;
		InitializeCriticalSection(&cs);
	}

	~ThreadData()
	{
		assert(!refCounter);
		DeleteCriticalSection(&cs);
	}

	void lock()
	{
		EnterCriticalSection(&cs);
	}

	void unlock()
	{
		LeaveCriticalSection(&cs);
	}

	void retain()
	{
		_InterlockedIncrement(&refCounter);
	}

	void release()
	{
		LONG n = _InterlockedDecrement(&refCounter);
		if(!n)
		{
			delete this;
		}
	}
};
//------------------------------------------------------------------------------
static DWORD dwTlsIndex = 0;
//------------------------------------------------------------------------------
void Threading::processInit()
{
	assert(!dwTlsIndex);
	dwTlsIndex = TlsAlloc();
	threadInit();
}
//------------------------------------------------------------------------------
void Threading::processDone()
{
	threadDone();
	assert(dwTlsIndex);
	TlsFree(dwTlsIndex);
}
//------------------------------------------------------------------------------
void Threading::threadInit()
{
	assert(dwTlsIndex);
	assert(!TlsGetValue(dwTlsIndex));
	ThreadData * data = new ThreadData();
	data->retain();
	LPVOID pvTlsData = reinterpret_cast<LPVOID>(data);
	TlsSetValue(dwTlsIndex, pvTlsData);
}
//------------------------------------------------------------------------------
void Threading::threadDone()
{
	assert(dwTlsIndex);
	LPVOID pvTlsData = TlsGetValue(dwTlsIndex);
	assert(pvTlsData);
	ThreadData * data = reinterpret_cast<ThreadData *>(pvTlsData);
	data->release();
	TlsSetValue(dwTlsIndex, NULL);
}
//------------------------------------------------------------------------------
Threading::ThreadData * Threading::currentThreadData()
{
	assert(dwTlsIndex);
	LPVOID pvTlsData = TlsGetValue(dwTlsIndex);
	assert(pvTlsData);
	return reinterpret_cast<ThreadData *>(pvTlsData);
}
//------------------------------------------------------------------------------
void Threading::lock(ThreadData * data)
{
	data->lock();
}
//------------------------------------------------------------------------------
void Threading::unlock(ThreadData * data)
{
	data->unlock();
}
//------------------------------------------------------------------------------
void Threading::retain(ThreadData * data)
{
	data->retain();
}
//------------------------------------------------------------------------------
void Threading::release(ThreadData * data)
{
	data->release();
}
//------------------------------------------------------------------------------
} //namespace Cpp