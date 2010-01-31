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

#ifndef __CPP__EVENTS__NORMALIZE_CAST__HPP
#define __CPP__EVENTS__NORMALIZE_CAST__HPP

namespace Cpp {
namespace Private {
namespace Events {
//------------------------------------------------------------------------------
template<class T, int IsPolymorphic> struct Caster;

template<class T> struct Caster<T, 0>
{
	static void const * cast(T * ptr) { return static_cast<void const *>(ptr); }
};

template<class T> struct Caster<T, 1>
{
	static void const * cast(T * ptr) { return dynamic_cast<void const *>(ptr); }
};
//------------------------------------------------------------------------------
template<class T> class PolymorphicTestHelper : public T
{
	virtual ~PolymorphicTestHelper() = 0;
};

template<class T> struct IsPolymorphic
{
	enum { value = sizeof(PolymorphicTestHelper<T>) == sizeof(T) ? 1 : 0 };
};
//------------------------------------------------------------------------------
inline const void * normalize_cast(const void * ptr) { return ptr; }

template<class T> inline void const * normalize_cast(T * ptr)
{
	static char const object_has_imcomplete_type[sizeof(T) ? +1 : -1] = {};
	(void)sizeof(object_has_imcomplete_type);

	enum { isPolymorphic =  IsPolymorphic<T>::value };
	return Caster<T, isPolymorphic>::cast(ptr);
}
//------------------------------------------------------------------------------
} //namespace Events
} //namespace Private
} //namespace Cpp

#endif //__CPP__EVENTS__NORMALIZE_CAST__HPP