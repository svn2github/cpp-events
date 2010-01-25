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

#include <sigc++/sigc++.h>
#include <ctime>
#include <stdio.h>

class MyReciever : public sigc::trackable
{
public:
	void processFloat(float x) {}
	void processDouble(float x) {}
};

void test(unsigned N)
{
	MyReciever rcv;

	unsigned X1 = 0, X2 = 0;

	for(int j=0; j<8; ++j)
	{
		clock_t c0, c1, c2;

		{
			sigc::signal1<void,float> s1;
			
			c0 = clock();

			for(unsigned i = 0; i< N; ++i)
			{
				s1.connect(sigc::mem_fun1(&rcv, &MyReciever::processFloat));
			}

			c1 = clock();

		}

		c2 = clock();

		X1 += (unsigned)(c1 - c0);
		X2 += (unsigned)(c2 - c1);
	}
	printf("%8u\t%06u\t%06u\n", N, X1, X2);
}

int main()
{
	printf("LibSigC++ speed test\n");
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
	return 0;
}

