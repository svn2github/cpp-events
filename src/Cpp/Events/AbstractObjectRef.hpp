#ifndef ABSTRACT_OBJECT_REF__HPP
#define ABSTRACT_OBJECT_REF__HPP

#include "normalize_cast.hpp"

//! Value type that represents pointer to arbitary C++ object.
class AbstractObjectRef
{
public:
	AbstractObjectRef() : ptr_() {}
	
	template<class T> AbstractObjectRef(T * x)
		: ptr_(normalize_cast(x))
	{}

	bool isNull() const { return !ptr_; }
	void clear() { ptr_ = 0; }

	bool operator<(AbstractObjectRef const & r) const { return ptr_ < r.ptr_; }
	bool operator>(AbstractObjectRef const & r) const { return ptr_ > r.ptr_; }
	bool operator==(AbstractObjectRef const & r) const { return ptr_ == r.ptr_; }
	bool operator!=(AbstractObjectRef const & r) const { return ptr_ != r.ptr_; }
	bool operator>=(AbstractObjectRef const & r) const { return ptr_ >= r.ptr_; }
	bool operator<=(AbstractObjectRef const & r) const { return ptr_ <= r.ptr_; }
private:
	void const * ptr_;
};

#endif //ABSTRACT_OBJECT_REF__HPP