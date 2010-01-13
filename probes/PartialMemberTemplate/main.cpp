enum Cases
{
	GeneralTemplateInsideClass,
	PartialSpecializationInsideClass,
	EqualClassesOutsideClass,
	IntAndClassOutsideClass,
	CharAndBoolOutsideClass,
};

class TestTraits
{
public:
	template<class T1, class T2> struct MyTrait { enum { value = GeneralTemplateInsideClass }; };
	template<> struct MyTrait<char, char> { enum { value = PartialSpecializationInsideClass }; };
};

template<class T> struct TestTraits::MyTrait<T, T> { enum { value = EqualClassesOutsideClass }; };
template<class T> struct TestTraits::MyTrait<int, T> { enum { value = IntAndClassOutsideClass }; };
template<> struct TestTraits::MyTrait<char, bool> { enum { value = CharAndBoolOutsideClass }; };

template<int N1, int N2> struct AssertEqual;
template<int N> struct AssertEqual<N, N> { enum { isOk = true }; };

void main()
{
	(void)AssertEqual<TestTraits::MyTrait<float, double>::value, GeneralTemplateInsideClass>::isOk;
	(void)AssertEqual<TestTraits::MyTrait<char, char>::value, PartialSpecializationInsideClass>::isOk;
	(void)AssertEqual<TestTraits::MyTrait<float, float>::value, EqualClassesOutsideClass>::isOk;
	(void)AssertEqual<TestTraits::MyTrait<int, double>::value, IntAndClassOutsideClass>::isOk;
	(void)AssertEqual<TestTraits::MyTrait<char, bool>::value, CharAndBoolOutsideClass>::isOk;
}