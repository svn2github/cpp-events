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
	pthread_key_create(&tlsKey, NULL);
	constructThreadData();
}
//------------------------------------------------------------------------------
void Threading::destructProcessData()
{
	destructThreadData();
	assert(tlsKey);
	pthread_key_delete(tlsKey);
	tlsKey = 0;
}
//------------------------------------------------------------------------------
void Threading::constructThreadData()
{
	assert(tlsKey);
	assert(!pthread_getspecific(tlsKey));
	POSIX_ThreadData * data = new POSIX_ThreadData();
	data->retain();
	void * pvTlsData = reinterpret_cast<void*>(data);
	pthread_setspecific(tlsKey, pvTlsData);
}
//------------------------------------------------------------------------------
void Threading::destructThreadData()
{
	assert(tlsKey);
	void * pvTlsData = pthread_getspecific(tlsKey);
	assert(pvTlsData);
	POSIX_ThreadData * data = reinterpret_cast<POSIX_ThreadData*>(pvTlsData);
	data->release();
	pthread_setspecific(tlsKey, NULL);
}
//------------------------------------------------------------------------------
Threading::ThreadData * Threading::currentThreadData()
{
	assert(tlsKey);
	void * pvTlsData = pthread_getspecific(tlsKey);
	assert(pvTlsData);
	POSIX_ThreadData * data = reinterpret_cast<POSIX_ThreadData*>(pvTlsData);
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
