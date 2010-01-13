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

