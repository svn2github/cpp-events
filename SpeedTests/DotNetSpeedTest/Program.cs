using System;
using System.Collections.Generic;
using System.Text;

namespace MyNamespace
{
    public delegate void TestDelegate(object obj);
    public delegate float MathDelegate(float x);
    public delegate void ClickDelegate(object sender, EventArgs e);
}

namespace DotNetSpeedTest
{
    class Program
    {
        public static void testFunc(float x)
        {
        }

        class Sender
        {
            public delegate void TestEvent(float x);  // {1}

            public event TestEvent testEvent;  // {2}

            public void fire(float x) { testEvent(x); }

            public void check()
            {
                TestEvent e1 = this.fire;
                TestEvent e2 = this.fire;
                testEvent = e1 + e2;
            }
        }

        class Reciever
        {
            public void handleFloat(float x) {}
        }

        static void test(uint N)
        {
            Sender sender = new Sender();
            Reciever rcv = new Reciever();

            TimeSpan X1 = TimeSpan.Zero;
            TimeSpan X2 = TimeSpan.Zero;
            TimeSpan X3 = TimeSpan.Zero;

            for(int j=0; j<8; ++j)
	        {
		        DateTime c0 = DateTime.Now;

		        for(uint i = 0; i< N; ++i)
		        {
                    sender.testEvent += rcv.handleFloat;
		        }

		        DateTime c1 = DateTime.Now;

		        for(int k=0; k<100; ++k)
		        {
			        sender.fire(3.14f);
		        }

		        DateTime c2 = DateTime.Now;

		        for(uint i = 0; i< N; ++i)
		        {
                    sender.testEvent -= rcv.handleFloat;
		        }

		        DateTime c3 = DateTime.Now;

		        X1 = X1.Add(c1.Subtract(c0));
                X2 = X2.Add(c2.Subtract(c1));
		        X3 = X3.Add(c3.Subtract(c3));
	        }
	        System.Console.WriteLine("{0,8}\t{1}\t{2}\t{3}", N, X1.Milliseconds, X2.Milliseconds, X3.Milliseconds);
        }

        static void Main(string[] args)
        {
            System.Console.WriteLine("C#/.NET speed test");
            for(uint a = 1000; a < 100000; )
            {
                uint x = a;
                for(uint i = 0; i < 9; ++i)
                {
                    test(x);
                    x += a;
                }
                a = x;
            }
         }
    }
}

