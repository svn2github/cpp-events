#ifndef ABSTRACT_DELEGATE__HPP
#define ABSTRACT_DELEGATE__HPP

#include "../FastDelegate/src/FastDelegate.h"

//! Abstract class that represents arbitary delegate in a common form.
class AbstractDelegate
{
public:
	AbstractDelegate() : d_() {}
	AbstractDelegate(fastdelegate::DelegateMemento const & d) : d_(d) {}

	template<class T, class Y> AbstractDelegate(T obj, Y pmf)
		: d_(fastdelegate::MakeDelegate(obj, pmf))
	{}

	bool isNull() const { return d_.empty(); }
	void clear() { d_.clear(); }

	bool operator<(AbstractDelegate const & r) const { return d_.IsLess(r.d_); }
	bool operator>(AbstractDelegate const & r) const { return r.d_.IsLess(d_); }
	bool operator==(AbstractDelegate const & r) const { return d_.IsEqual(r.d_); }
	bool operator!=(AbstractDelegate const & r) const { return !d_.IsEqual(r.d_); }
	bool operator>=(AbstractDelegate const & r) const { return !d_.IsLess(r.d_); }
	bool operator<=(AbstractDelegate const & r) const { return !r.d_.IsLess(d_); }
private:
	fastdelegate::DelegateMemento d_;
};

#endif //ABSTRACT_DELEGATE__HPP