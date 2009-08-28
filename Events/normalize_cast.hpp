#ifndef NORMALIZE_CAST__HPP
#define NORMALIZE_CAST__HPP

namespace detail {

template<class T, int IsPolymorphic> struct Caster;

template<class T> struct Caster<T, 0>
{
	static void const * cast(T * ptr) { return static_cast<void const *>(ptr); }
};

template<class T> struct Caster<T, 1>
{
	static void const * cast(T * ptr) { return dynamic_cast<void const *>(ptr); }
};

template<class T> class PolymorphicTestHelper : public T
{
	virtual ~PolymorphicTestHelper() = 0;
};

} //namespace detail

template<class T> inline void const * normalize_cast(T * ptr)
{
	static char const object_has_imcomplete_type[sizeof(T) ? +1 : -1] = {};
	(void)sizeof(object_has_imcomplete_type);

	enum { isPolymorphic = sizeof(detail::PolymorphicTestHelper<T>) == sizeof(T) ? 1 : 0 };
	return detail::Caster<T, isPolymorphic>::cast(ptr);
}

#endif //NORMALIZE_CAST__HPP