#ifndef ATOMIC_REFERENCE_COUNTER__WIN32__HPP
#define ATOMIC_REFERENCE_COUNTER__WIN32__HPP

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

#endif //ATOMIC_REFERENCE_COUNTER__WIN32__HPP
