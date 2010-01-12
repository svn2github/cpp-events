#ifndef __CPP_EVENTS__THREADING__HPP
#define __CPP_EVENTS__THREADING__HPP

namespace Cpp {
//------------------------------------------------------------------------------
class Threading
{
public:
	// Implementation-specific
	// TODO: make reference counter public for better inlining
	class ThreadData;

	static void constructProcessData();
	static void destructProcessData();

	static void constructThreadData();
	static void destructThreadData();

	static ThreadData * currentThreadData();
	static void lock(ThreadData *);
	static void unlock(ThreadData *);

	static void retain(ThreadData *);
	static void release(ThreadData *);

	class ProcessInit
	{
	public:
		ProcessInit() { constructProcessData(); }
		~ProcessInit() { destructProcessData(); }
	};

	class ThreadInit
	{
	public:
		ThreadInit() { constructThreadData(); }
		~ThreadInit() { destructThreadData(); }
	};
};
//------------------------------------------------------------------------------
} //namespace Cpp

#endif //__CPP_EVENTS__THREADING__HPP