#ifndef __CPP_EVENTS__THREAD_DATA__HPP
#define __CPP_EVENTS__THREAD_DATA__HPP

#include "Threading.hpp"
#include "AtomicReferenceCounter.hpp"

namespace Cpp {
//------------------------------------------------------------------------------
class Threading::ThreadData
{
public:
	void lock();
	void unlock();

	void retain();
	void release();
private:
	ThreadData() {}
	~ThreadData() {}
};
//------------------------------------------------------------------------------
} //namespace Cpp

namespace Cpp {
namespace Private {
namespace Events {
//------------------------------------------------------------------------------
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
			ptr_->retain();
		}
	}

	ThreadDataRef(ThreadDataRef const & r)
		: ptr_(r.ptr_)
	{
		if(ptr_)
		{
			ptr_->retain();
		}
	}

	ThreadDataRef::~ThreadDataRef()
	{
		if(ptr_) ptr_->release();
	}

	ThreadDataRef & operator = (ThreadDataRef const & r)
	{
		if(r.ptr_) r.ptr_->retain();
		if(ptr_) ptr_->release();
		ptr_ = r.ptr_;
		return *this;
	}

	void clear()
	{
		if(ptr_)
		{
			ptr_->release();
			ptr_ = 0;
		}
	}

	void lock() { if(ptr_) ptr_->lock(); }
	void unlock() { if(ptr_) ptr_->unlock(); }

	void swap(ThreadDataRef & r)
	{
		Threading::ThreadData * d = ptr_;
		ptr_ = r.ptr_;
		r.ptr_ = d;
	}

	bool isBefore(ThreadDataRef const & r) const
	{
		return ptr_ < r.ptr_;
	}

	void makeBefore(ThreadDataRef & r)
	{
		if(r.isBefore(*this))
		{
			Threading::ThreadData * tmp = ptr_;
			ptr_ = r.ptr_; r.ptr_ = tmp;
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
		if(ptr_) ptr_->retain();
	}
};
//------------------------------------------------------------------------------
class ThreadDataLocker
{
public:
	ThreadDataLocker(ThreadDataRef const & x) : x_(x) { x_.lock(); }
	~ThreadDataLocker() { x_.unlock(); }
private:
	ThreadDataRef x_;
};
//------------------------------------------------------------------------------
class OrderedThreadDataLocker
{
public:
	OrderedThreadDataLocker(ThreadDataRef const & a, ThreadDataRef const & b)
		: outer_(a), inner_(b)
	{
		if(inner_.isBefore(outer_))
		{
			inner_.swap(outer_);
		}

		outer_.lock();
		inner_.lock();
	}

	~OrderedThreadDataLocker()
	{
		inner_.unlock();
		outer_.unlock();
	}
private:
	ThreadDataRef outer_;
	ThreadDataRef inner_;
};
//------------------------------------------------------------------------------
} //namespace Events
} //namespace Private
} //namespace Cpp

#endif //__CPP_EVENTS__THREAD_DATA__HPP