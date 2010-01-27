// Copyright (c) 2010 Nickolas Pohilets
//
// This file is a part of the probe project suit for the CppEvents library.
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

int main()
{
	(void)AssertEqual<TestTraits::MyTrait<float, double>::value, GeneralTemplateInsideClass>::isOk;
	(void)AssertEqual<TestTraits::MyTrait<char, char>::value, PartialSpecializationInsideClass>::isOk;
	(void)AssertEqual<TestTraits::MyTrait<float, float>::value, EqualClassesOutsideClass>::isOk;
	(void)AssertEqual<TestTraits::MyTrait<int, double>::value, IntAndClassOutsideClass>::isOk;
	(void)AssertEqual<TestTraits::MyTrait<char, bool>::value, CharAndBoolOutsideClass>::isOk;
	return 0;
}
