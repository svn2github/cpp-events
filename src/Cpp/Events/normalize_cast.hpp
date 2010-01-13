#ifndef __CPP_EVENTS__NORMALIZE_CAST__HPP
#define __CPP_EVENTS__NORMALIZE_CAST__HPP

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

#endif //__CPP_EVENTS__NORMALIZE_CAST__HPP