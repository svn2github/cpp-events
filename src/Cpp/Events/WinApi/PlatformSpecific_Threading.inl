#include "Threading.hpp"
#include "ThreadData.hpp"
#include <cassert>
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
	AtomicReferenceCounter ref_;
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