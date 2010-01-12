#ifndef __CPP_EVENTS__THREADING__HPP
#define __CPP_EVENTS__THREADING__HPP

namespace Cpp {
//------------------------------------------------------------------------------
class Threading
{
public:
	// Implementation-specific
	class ThreadData;
	
	static ThreadData * currentThreadData();
	
	static void constructProcessData();
	static void destructProcessData();

	static void constructThreadData();
	static void destructThreadData();

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