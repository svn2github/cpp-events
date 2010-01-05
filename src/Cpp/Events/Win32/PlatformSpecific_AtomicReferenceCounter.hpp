#ifndef __CPP_EVENTS__WIN32__ATOMIC_REFERENCE_COUNTER__HPP
#define __CPP_EVENTS__WIN32__ATOMIC_REFERENCE_COUNTER__HPP

#include <intrin.h>

#pragma intrinsic (_InterlockedIncrement)
#pragma intrinsic (_InterlockedDecrement)

class AtomicReferenceCounter
{
public:
	AtomicReferenceCounter() : ref_() {}

	void retain() { _InterlockedIncrement(&ref_); }
	bool release() { return !_InterlockedDecrement(&ref_); }
private:
	volatile long ref_;
};

#endif //__CPP_EVENTS__WIN32__ATOMIC_REFERENCE_COUNTER__HPP
