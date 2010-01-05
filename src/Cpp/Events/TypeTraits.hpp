#ifndef TYPE_TRAITS__HPP
#define TYPE_TRAITS__HPP

#include "TypeArithmetic.hpp"

template<class T> struct SizeOf { typedef TypeForInt<sizeof(T)> Type; };

template<class T> struct IsSigned { typedef FalseType Type; };
template<> struct IsSigned<char> { typedef TypeForBool<(char(int(-1)) < 0)> Type; };
template<> struct IsSigned<signed char>      { typedef TrueType Type; };
template<> struct IsSigned<signed short>     { typedef TrueType Type; };
template<> struct IsSigned<signed int>       { typedef TrueType Type; };
template<> struct IsSigned<signed long>      { typedef TrueType Type; };
template<> struct IsSigned<signed long long> { typedef TrueType Type; };

template<class T> struct IsUnsigned { typedef FalseType Type; };
template<> struct IsUnsigned<char> { typedef BoolNot<IsSigned<char>::Type>::Type Type; };
template<> struct IsUnsigned<unsigned char>      { typedef TrueType Type; };
template<> struct IsUnsigned<unsigned short>     { typedef TrueType Type; };
template<> struct IsUnsigned<unsigned int>       { typedef TrueType Type; };
template<> struct IsUnsigned<unsigned long>      { typedef TrueType Type; };
template<> struct IsUnsigned<unsigned long long> { typedef TrueType Type; };

template<class T> struct IsChar { typedef FalseType Type; };
template<> struct IsChar<char>          { typedef TrueType Type; };
template<> struct IsChar<signed char>   { typedef TrueType Type; };
template<> struct IsChar<unsigned char> { typedef TrueType Type; };

template<class T> struct IsWChar { typedef FalseType Type; };
template<> struct IsWChar<wchar_t>          { typedef TrueType Type; };
//template<> struct IsWChar<signed wchar_t>   { typedef TrueType Type; };
//template<> struct IsWChar<unsigned wchar_t> { typedef TrueType Type; };

template<class T> struct IsCharType
{
	typedef typename BoolOr<
		typename IsChar<T>::Type,
		typename IsWChar<T>::Type
	>::Type Type;
};

template<class T> struct IsShort { typedef FalseType Type; };
//template<> struct IsShort<short>          { typedef TrueType Type; };
template<> struct IsShort<signed short>   { typedef TrueType Type; };
template<> struct IsShort<unsigned short> { typedef TrueType Type; };

template<class T> struct IsInt { typedef FalseType Type; };
//template<> struct IsInt<int>          { typedef TrueType Type; };
template<> struct IsInt<signed int>   { typedef TrueType Type; };
template<> struct IsInt<unsigned int> { typedef TrueType Type; };

template<class T> struct IsLong { typedef FalseType Type; };
//template<> struct IsLong<long>          { typedef TrueType Type; };
template<> struct IsLong<signed long>   { typedef TrueType Type; };
template<> struct IsLong<unsigned long> { typedef TrueType Type; };

template<class T> struct IsLongLong { typedef FalseType Type; };
//template<> struct IsLongLong<long long>          { typedef TrueType Type; };
template<> struct IsLongLong<signed long long>   { typedef TrueType Type; };
template<> struct IsLongLong<unsigned long long> { typedef TrueType Type; };

template<class T> struct IsInteger
{
	typedef typename BoolOr<
		typename IsSigned<T>::Type,
		typename IsUnsigned<T>::Type
	>::Type Type;
};

template<class T> struct IsFloating { typedef FalseType Type; };
template<> struct IsFloating<float>       { typedef TrueType Type; };
template<> struct IsFloating<double>      { typedef TrueType Type; };
template<> struct IsFloating<long double> { typedef TrueType Type; };

template<class T> struct IsBool { typedef FalseType Type; };
template<> struct IsBool<bool> { typedef TrueType Type; };

template<class T> struct IsVoid { typedef FalseType Type; };
template<> struct IsVoid<void> { typedef TrueType Type; };

template<class T> struct IsFundamental
{
	typedef typename BoolOr<
		typename IsVoid<T>::Type,
		typename IsBool<T>::Type,
		typename IsChar<T>::Type,
		typename IsInteger<T>::Type,
		typename IsFloating<T>::Type
	>::Type Type;
};

template<class T> struct IsPointer { typedef FalseType Type; };
template<class T> struct IsPointer<T*> { typedef TrueType Type; };

template<class T> struct UnPointer { typedef T Type; };
template<class T> struct UnPointer<T*> { typedef T Type; };

template<class T> struct IsReference { typedef FalseType Type; };
template<class T> struct IsReference<T&> { typedef TrueType Type; };

template<class T> struct UnReference { typedef T Type; };
template<class T> struct UnReference<T&> { typedef T Type; };

template<class T> struct IsConst { typedef FalseType Type; };
template<class T> struct IsConst<T const> { typedef TrueType Type; };

template<class T> struct UnConst { typedef T Type; };
template<class T> struct UnConst<T const> { typedef T Type; };

template<class T> struct IsVolatile { typedef FalseType Type; };
template<class T> struct IsVolatile<T volatile> { typedef TrueType Type; };

template<class T> struct UnVolatile { typedef T Type; };
template<class T> struct UnVolatile<T volatile> { typedef T Type; };

template<class T> struct Simplified
{
	typedef typename UnVolatile<
		typename UnConst<T>::Type
	>::Type Type;
};

template<class T> struct ParameterType
{
	typedef typename TypeIf<
		typename IsReference<T>::Type, T,
		typename TypeIf<
			typename BoolOr<
				typename IsFundamental<T>::Type,
				typename IsPointer<T>::Type
			>::Type, T const, T const &
		>::Type
	>::Type Type;
};

template<class T> struct StorageType
{
	typedef typename Simplified<
		typename UnReference<T>::Type
	>::Type Type;
};

template<class T> struct IsSmall { typedef TypeForBool<sizeof(T) <= sizeof(void*)> Type; };

template<class T> struct IsPOD { typedef FalseType Type; };

template<class T> struct IsPrimitive
{
	typedef typename BoolOr<
		typename IsFundamental<T>::Type,
		typename IsPointer<T>::Type,
		typename IsPOD<T>::Type
	>::Type Type;
};

template<class T> struct IsCopiable
{
	typedef typename IsPrimitive<T>::Type Type;
};

template<class T> struct IsMovable
{
	typedef typename IsCopiable<T>::Type Type;
};

template<class T> struct IsComplex
{
	typedef typename BoolNot<typename IsMovable<T>::Type>::Type Type;
};

template<class T0, class T1> struct CanConvert
{
private:
	static T0 makeSrc();
	static SmallType convertTestHelper(T1);
	static BigType convertTestHelper(...);
public:
	typedef TypeForBool<sizeof(convertTestHelper(makeSrc())) == sizeof(SmallType)> Type;
};

template<class T0, class T1> struct AreIdentical { typedef FalseType Type; };
template<class T> struct AreIdentical<T, T> { typedef TrueType Type; };

template<class T0, class T1> struct IsSubclass
{
	typedef typename BoolAnd<
		typename CanConvert<T0 const*, T1 const*>::Type, 
		typename BoolNot<
			typename AreIdentical<T1 const *, void const *>::Type
		>::Type
	>::Type Type;
};

#endif //TYPE_TRAITS__HPP