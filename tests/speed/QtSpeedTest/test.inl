void CASE_NO(test)(unsigned N)
{
	Sender sender;
	Reciever rcv;

	unsigned X1 = 0, X2 = 0, X3 = 0;

	for(int j=0; j<8; ++j)
	{
		clock_t c0 = clock();

		for(unsigned i = 0; i< N; ++i)
		{
			CONNECT_STRING		
		}

		clock_t c1 = clock();

		for(int k=0; k<100; ++k)
		{
			sender.fire(3.14f);
		}

		clock_t c2 = clock();

		QObject::disconnect(&sender, 0, &rcv, 0);

		clock_t c3 = clock();

		X1 += (unsigned)(c1 - c0);
		X2 += (unsigned)(c2 - c1);
		X3 += (unsigned)(c3 - c2);
	}
	printf("%8u\t%06u\t%06u\t%06u\n", N, X1, X2, X3);
}

void CASE_NO(runTest)()
{
	printf("Qt speed test. " CASE_NAME "\n");
	for(unsigned a = 1000; a < 100000; )
	{
		unsigned x = a;
		for(unsigned i=0; i<9; ++i)
		{
			CASE_NO(test)(x);
			x += a;
		}
		a = x;
	}
}

