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

/*
Goal:
  Check if it is possible to declare new inner type inside function declaration.

Motivation:
  InnerTestClass is a prototype for future event-ref class.

Results:
  * MSVC - PASSED
  * GCC  - FAILED, "{{TODO:: Write exact error message here}}"
*/

class OuterTestClass
{
public:
	class InnerTestClass
	{
	public:
		InnerTestClass(OuterTestClass * inst) : inst_(inst) {}
		int value() const { return inst_->x_; }
		void setValue(int v) { inst_->x_ = v; }
	private:
		OuterTestClass * inst_;
	} propertyX() { return this; }
private:
	int x_;
};

int main()
{
	OuterTestClass c;
	int q = c.propertyX().value();
	c.propertyX().setValue(q + 24);
	return 0;
}
