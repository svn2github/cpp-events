#include <pthread.h>

namespace Cpp {
//------------------------------------------------------------------------------
class POSIX_ThreadData
{
public:
	POSIX_ThreadData()
	{
		pthread_mutexattr_init(&attr_);
		pthread_mutexattr_settype(&attr_, PTHREAD_MUTEX_RECURSIVE_NP);
		pthread_mutex_init(&mutex_, &attr_);
	}

	~POSIX_ThreadData()
	{
		assert(ref_.isNull());
		pthread_mutex_destroy(&mutex_);
		pthread_mutexattr_destroy(&attr_);
	}

	void lock()
	{
		pthread_mutex_lock(&mutex_);
	}

	void unlock()
	{
		pthread_mutex_unlock(&mutex_);
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
	pthread_mutexattr_t attr_;
	pthread_mutex_t mutex_;
};
//------------------------------------------------------------------------------
static pthread_key_t tlsKey;
//------------------------------------------------------------------------------
void Threading::constructProcessData()
{
	assert(!tlsKey);
	pthread_create_key(&tlsKey, NULL);
	constructThreadData();
}
//------------------------------------------------------------------------------
void Threading::destructProcessData()
{
	destructThreadData();
	assert(tlsKey);
	pthread_key_delete(tlsKey);
}
//------------------------------------------------------------------------------
void Threading::constructThreadData()
{
	assert(tlsKey);
	assert(!pthread_getspecific(tlsKey));
	WinApi_ThreadData * data = new WinApi_ThreadData();
	data->retain();
	LPVOID pvTlsData = reinterpret_cast<LPVOID>(data);
	pthread_setspecific(tlsKey, pvTlsData);
}
//------------------------------------------------------------------------------
void Threading::destructThreadData()
{
	assert(tlsKey);
	LPVOID pvTlsData = pthread_getspecific(tlsKey);
	assert(pvTlsData);
	WinApi_ThreadData * data = reinterpret_cast<WinApi_ThreadData*>(pvTlsData);
	data->release();
	pthread_setspecific(tlsKey, NULL);
}
//------------------------------------------------------------------------------
Threading::ThreadData * Threading::currentThreadData()
{
	assert(tlsKey);
	LPVOID pvTlsData = pthread_getspecific(tlsKey);
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