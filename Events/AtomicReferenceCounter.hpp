#ifndef ATOMIC_REFERENCE_COUNTER__HPP
#define ATOMIC_REFERENCE_COUNTER__HPP

#include <cstddef>

class AtomicReferenceCounter
{
public:
	AtomicReferenceCounter() : ref_() {}

	void retain() { ++ref_; }
	bool release() { return !--ref_; }
private:
	size_t ref_;
};


#endif //ATOMIC_REFERENCE_COUNTER__HPP