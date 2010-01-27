// Copyright (c) 2010 Nickolas Pohilets
//
// This file is a part of the benchmarking suit for the CppEvents library and
// its analogues.
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

#include <ctime>
#include <stdio.h>

#include <set>
#include <list>

#define MAKE_NS_1(X) namespace_##X
#define MAKE_NS_2(X) MAKE_NS_1(X)
#define MAKE_NS(X) MAKE_NS_2(X)

namespace MAKE_NS(SIGSLOT_DEFAULT_MT_POLICY) {

#include "sigslot.h"

class MyReciever : public sigslot::has_slots<>
{
public:
	void processFloat(float x) {}
	void processDouble(float x) {}
};

void test(unsigned N)
{
	sigslot::signal1<float> s1;
	MyReciever rcv;

	unsigned X1 = 0, X2 = 0, X3 = 0;

	for(int j=0; j<8; ++j)
	{
		clock_t c0 = clock();

		for(unsigned i = 0; i< N; ++i)
		{
			s1.connect(&rcv, &MyReciever::processFloat);
		}

		clock_t c1 = clock();

		for(int k=0; k<100; ++k)
		{
			s1(3.14f);
		}

		clock_t c2 = clock();

		s1.disconnect_all();

		clock_t c3 = clock();

		X1 += (unsigned)(c1 - c0);
		X2 += (unsigned)(c2 - c1);
		X3 += (unsigned)(c3 - c2);
	}
	printf("%8u\t%06u\t%06u\t%06u\n", N, X1, X2, X3);
}

#define XX_1(X) #X
#define XX_2(X) XX_1(X)
#define XX(X) XX_2(X)

void runTest()
{
	printf("SigSlot.%s speed test\n", XX(SIGSLOT_DEFAULT_MT_POLICY));
	printf("  Repetitions   Connect Invoke Disconnect\n");
	for(unsigned a = 1000; a < 100000; )
	{
		unsigned x = a;
		for(unsigned i=0; i<9; ++i)
		{
			test(x);
			x += a;
		}
		a = x;
	}
}

} // namespace MAKE_NS(SIGSLOT_DEFAULT_MT_POLICY)

using namespace MAKE_NS(SIGSLOT_DEFAULT_MT_POLICY);

