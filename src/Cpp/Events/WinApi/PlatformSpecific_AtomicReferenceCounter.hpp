#include <intrin.h>

#pragma intrinsic (_InterlockedIncrement)
#pragma intrinsic (_InterlockedDecrement)

namespace Cpp {
//------------------------------------------------------------------------------
class AtomicReferenceCounter
{
public:
	AtomicReferenceCounter() : ref_() {}

	bool isNull() const { return !ref_; }

	void retain() { _InterlockedIncrement(&ref_); }
	bool release() { return !_InterlockedDecrement(&ref_); }
private:
	volatile long ref_;
};
//------------------------------------------------------------------------------
} //namespace Cpp
