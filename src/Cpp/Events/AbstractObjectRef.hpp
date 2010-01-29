// Copyright (c) 2010 Nickolas Pohilets
//
// This file is a part of the CppEvents library.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef __CPP_EVENTS__ABSTRACT_OBJECT_REF__HPP
#define __CPP_EVENTS__ABSTRACT_OBJECT_REF__HPP

#include <Cpp/Events/normalize_cast.hpp>

namespace Cpp {
//------------------------------------------------------------------------------
//! Value type that represents pointer to arbitrary C++ object.
class AbstractObjectRef
{
public:
	AbstractObjectRef() : ptr_() {}
	
	template<class T> AbstractObjectRef(T * x)
		: ptr_(Private::Events::normalize_cast(x))
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
//------------------------------------------------------------------------------
} //namespace Cpp

#endif //ABSTRACT_OBJECT_REF__HPP