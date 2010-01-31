// Copyright (c) 2010 Nickolas Pohilets
//
// This file is a part of the unit test suit for the CppEvents library.
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

	if(!d) return;
	d->templateData[TestCase_InlineFunction].func =
		&TestTemplate<TestClass>::testInlineFunction;
	d->templateData[TestCase_OutlineFunction].func =
		&TestTemplate<TestClass>::testOutlineFunction;
	d->templateData[TestCase_InlineFunctionWithStaticVariable].func =
		&TestTemplate<TestClass>::testInlineFunctionWithStaticVariable;
	d->templateData[TestCase_OutlineFunctionWithStaticVariable].func =
		&TestTemplate<TestClass>::testOutlineFunctionWithStaticVariable;
	d->classData[TestCase_InlineFunction].func =
		&TestClass::testInlineFunction;
	d->classData[TestCase_OutlineFunction].func =
		&TestClass::testOutlineFunction;
	d->classData[TestCase_InlineFunctionWithStaticVariable].func =
		&TestClass::testInlineFunctionWithStaticVariable;
	d->classData[TestCase_OutlineFunctionWithStaticVariable].func =
		&TestClass::testOutlineFunctionWithStaticVariable;