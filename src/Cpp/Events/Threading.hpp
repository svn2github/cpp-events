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
//------------------------------------------------------------------------------
class Process
{
public:
	Process() { Threading::processInit(); }
	~Process() { Threading::processDone(); }
};
//------------------------------------------------------------------------------
class Thread
{
public:
	Thread() { Threading::threadInit(); }
	~Thread() { Threading::threadDone(); }
};
//------------------------------------------------------------------------------
} //namespace Cpp

#endif //__CPP_EVENTS__THREADING__HPP