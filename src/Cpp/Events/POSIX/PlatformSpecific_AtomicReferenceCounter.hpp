namespace Cpp {
//------------------------------------------------------------------------------
class AtomicReferenceCounter
{
public:
	AtomicReferenceCounter() : ref_() {}

	bool isNull() const { return !ref_; }

	void retain() { __sync_add_and_fetch(&ref_, 1); }
	bool release() { return !__sync_sub_and_fetch(&ref_, 1); }
private:
	unsigned ref_;
};
//------------------------------------------------------------------------------
} //namespace Cpp

