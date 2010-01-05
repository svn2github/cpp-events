#ifndef TYPE_ARITHMETIC
#define TYPE_ARITHMETIC

struct NullType {};
struct InvalidType {};

typedef char SmallType;
struct BigType { char dummy[16]; };

template<class T> struct TypeForType { typedef T Type;};
template<int N> struct TypeForInt { enum { value = N }; };
template<bool b> struct TypeForBool { enum { value = b}; };

typedef TypeForBool<true> TrueType;
typedef TypeForBool<false> FalseType;

template<class T> struct BoolNot { typedef TypeForBool<!T::value> Type; };
template<class T> struct IntNeg  { typedef TypeForInt<-T::value> Type; };
template<class T> struct IntInv  { typedef TypeForInt<~int(T::value)> Type; };
template<class T> struct IntInc  { typedef TypeForInt<T::value + 1> Type; };
template<class T> struct IntDec  { typedef TypeForInt<T::value - 1> Type; };

template<
	class T0, class T1,
	class T2 = TrueType,
	class T3 = TrueType,
	class T4 = TrueType,
	class T5 = TrueType,
	class T6 = TrueType,
	class T7 = TrueType
> struct BoolAnd
{
	typedef TypeForBool<
		T0::value && T1::value 
		&& T2::value && T3::value
		&& T4::value && T5::value
		&& T6::value && T7::value
	> Type;
};

template<
	class T0, class T1,
	class T2 = FalseType,
	class T3 = FalseType,
	class T4 = FalseType,
	class T5 = FalseType,
	class T6 = FalseType,
	class T7 = FalseType
> struct BoolOr
{
	typedef TypeForBool<
		T0::value || T1::value 
		|| T2::value || T3::value
		|| T4::value || T5::value
		|| T6::value || T7::value
	> Type;
};

namespace Private {
	namespace BoolXorPrivate {

		template<class T0, class T1> struct BoolXorHelper2
		{
			typedef TypeForBool<(T0::value && !T1::value) || (!T0::value && T1::value)> Type;
		};

		template<class T0, class T1, class T2> struct BoolXorHelper3
		{
			typedef typename BoolXorHelper2<typename BoolXorHelper2<T0, T1>::Type, T2>::Type Type;
		};

		template<class T0, class T1, class T2, class T3> struct BoolXorHelper4
		{
			typedef typename BoolXorHelper2<typename BoolXorHelper3<T0, T1, T2>::Type, T3>::Type Type;
		};

		template<class T0, class T1, class T2, class T3, class T4> struct BoolXorHelper5
		{
			typedef typename BoolXorHelper2<typename BoolXorHelper4<T0, T1, T2, T3>::Type, T4>::Type Type;
		};

		template<class T0, class T1, class T2, class T3, class T4, class T5> struct BoolXorHelper6
		{
			typedef typename BoolXorHelper2<typename BoolXorHelper5<T0, T1, T2, T3, T4>::Type, T5>::Type Type;
		};

		template<class T0, class T1, class T2, class T3, class T4, class T5, class T6> struct BoolXorHelper7
		{
			typedef typename BoolXorHelper2<typename BoolXorHelper6<T0, T1, T2, T3, T4, T5>::Type, T6>::Type Type;
		};

		template<class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7> struct BoolXorHelper8
		{
			typedef typename BoolXorHelper2<typename BoolXorHelper7<T0, T1, T2, T3, T4, T5, T6>::Type, T7>::Type Type;
		};

	} //namespace BoolXorPrivate
} //namespace Private

template<
	class T0, class T1,
	class T2 = FalseType,
	class T3 = FalseType,
	class T4 = FalseType,
	class T5 = FalseType,
	class T6 = FalseType,
	class T7 = FalseType
> struct BoolXor
{
	typedef typename Private::BoolXorPrivate::BoolXorHelper8<T0, T1, T2, T3, T4, T5, T6, T7>::Type Type;
};

template<
	class T0, class T1,
	class T2 = TypeForInt<0>,
	class T3 = TypeForInt<0>,
	class T4 = TypeForInt<0>,
	class T5 = TypeForInt<0>,
	class T6 = TypeForInt<0>,
	class T7 = TypeForInt<0>
> struct IntAdd
{
	typedef typename TypeForInt<
		T0::value + T1::value
		+ T2::value + T3::value
		+ T4::value + T5::value
		+ T6::value + T7::value
	>::Type Type;
};

template<
	class T0, class T1,
	class T2 = TypeForInt<1>,
	class T3 = TypeForInt<1>,
	class T4 = TypeForInt<1>,
	class T5 = TypeForInt<1>,
	class T6 = TypeForInt<1>,
	class T7 = TypeForInt<1>
> struct IntMul
{
	typedef typename TypeForInt<
		T0::value * T1::value
		* T2::value * T3::value
		* T4::value * T5::value
		* T6::value * T7::value
	>::Type Type;
};

template<class T0, class T1> struct IntSub { typedef TypeForInt<T0::value - T1::value> Type; };
template<class T0, class T1> struct IntDiv { typedef TypeForInt<T0::value / T1::value> Type; };
template<class T0, class T1> struct IntMod { typedef TypeForInt<T0::value % T1::value> Type; };

template<class T0, class T1> struct IntPow
{
	typedef typename IntMul<T0, typename IntPow<T0, typename IntDec<T1>::Type>::Type>::Type Type;
};
template<class T0> struct IntPow<T0, TypeForInt<0> > { typedef TypeForInt<1> Type; };

template<class T0, class T1> struct IntCompare
{
	enum 
	{
		isEqual      = (T0::value == T1::value),
		isNotEqual   = (T0::value != T1::value),
		isLess       = (T0::value <  T1::value),
		isNotLess    = (T0::value >= T1::value),
		isGreater    = (T0::value <  T1::value),
		isNotGreater = (T0::value >= T1::value),
	};

	typedef TypeForBool<isEqual>      Equal;
	typedef TypeForBool<isNotEqual>   NotEqual;
	typedef TypeForBool<isLess>       Less;
	typedef TypeForBool<isNotLess>    NotLess;
	typedef TypeForBool<isGreater>    Greater;
	typedef TypeForBool<isNotGreater> NotGreater;
};

namespace Private {
	namespace TypeIfPrivate {
		template<class T, class Y> struct TypeIfHelper;
		template<class Y> struct TypeIfHelper<TrueType, Y> { typedef Y Type; };
		template<class Y> struct TypeIfHelper<FalseType, Y> { };
	} //namespace TypeIfPrivate
} //namespace Private

template<class Cond, class ThenClass, class ElseClass> struct TypeIf
	: public Private::TypeIfPrivate::TypeIfHelper<Cond, ThenClass>
	, public Private::TypeIfPrivate::TypeIfHelper<typename BoolNot<Cond>::Type, ElseClass>
{};

#endif //TYPE_ARITHMETIC