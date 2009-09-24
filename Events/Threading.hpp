#ifndef THREADING__HPP
#define THREADING__HPP

#include <cassert>

class Threading
{
public:
	// Implementation-specific
	class ThreadData;

	static void processInit();
	static void processDone();

	static void threadInit();
	static void threadDone();

	static ThreadData * currentThreadData();
	static void lock(ThreadData *);
	static void unlock(ThreadData *);

	static void retain(ThreadData *);
	static void release(ThreadData *);
};

class Process
{
public:
	Process() { Threading::processInit(); }
	~Process() { Threading::processDone(); }
};

class Thread
{
public:
	Thread() { Threading::threadInit(); }
	~Thread() { Threading::threadDone(); }
};

class ThreadDataRef
{
public:
	struct null {};
	struct current {};

	ThreadDataRef(null)
		: ptr_()
	{}
	
	ThreadDataRef(current)
		: ptr_(Threading::currentThreadData())
	{
		if(ptr_)
		{
			Threading::retain(ptr_);
		}
	}

	ThreadDataRef(ThreadDataRef const & r)
		: ptr_(r.ptr_)
	{
		if(ptr_)
		{
			Threading::retain(ptr_);
		}
	}

	ThreadDataRef::~ThreadDataRef()
	{
		clear();
	}

	ThreadDataRef & operator = (ThreadDataRef const & r)
	{
		if(r.ptr_) Threading::retain(r.ptr_);
		if(ptr_) Threading::release(ptr_);
		ptr_ = r.ptr_;
		return *this;
	}

	void clear()
	{
		if(ptr_)
		{
			Threading::release(ptr_);
			ptr_ = 0;
		}
	}

	void lock() { if(ptr_) Threading::lock(ptr_); }
	void unlock() { if(ptr_) Threading::unlock(ptr_); }

	void swap(ThreadDataRef & r)
	{
		Threading::ThreadData * d = ptr_;
		ptr_ = r.ptr_;
		r.ptr_ = d;
	}

	void order(ThreadDataRef & r)
	{
		if(ptr_ > r.ptr_)
		{
			swap(r);
		}
		else if(ptr_ == r.ptr_)
		{
			r.clear();
		}
	}

	bool operator==(ThreadDataRef const & r) const { return ptr_ == r.ptr_; }
	bool operator!=(ThreadDataRef const & r) const { return ptr_ != r.ptr_; }
	bool operator <(ThreadDataRef const & r) const { return ptr_  < r.ptr_; }
	bool operator >(ThreadDataRef const & r) const { return ptr_  > r.ptr_; }
	bool operator<=(ThreadDataRef const & r) const { return ptr_ <= r.ptr_; }
	bool operator>=(ThreadDataRef const & r) const { return ptr_ >= r.ptr_; }
private:
	Threading::ThreadData * ptr_;

	ThreadDataRef(Threading::ThreadData * p)
		: ptr_(p)
	{
		if(ptr_) Threading::retain(ptr_);
	}
};

class ThreadDataLocker
{
public:
	ThreadDataLocker(ThreadDataRef const & x) : x_(x) { x_.lock(); }
	~ThreadDataLocker() { x_.unlock(); }
private:
	ThreadDataRef x_;
};

#endif //THREADING__HPP