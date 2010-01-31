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

#include "TestClasses.hpp"
#include <gtest/gtest.h>

namespace UnitTests {
namespace ConnectDisconnect {
//------------------------------------------------------------------------------
/*
	This test checks basic connection management                          
*/
TEST(Test_ConnectDisconnect, ManualConnectDisconnect)
{
	Sender sender;
	Reciever r1, r2;
	Cpp::ConnectionScope scope;

	ASSERT_EQ(0, r1.value()); ASSERT_EQ(0, r2.value());
	sender.fire();
	ASSERT_EQ(0, r1.value()); ASSERT_EQ(0, r2.value());
	
	scope.connect(sender.somethingHappened(), &r1, &Reciever::increment);
	sender.fire();	// +1-0 +0-0
	ASSERT_EQ(1, r1.value()); ASSERT_EQ(0, r2.value());
	sender.fire();	// +1-0 +0-0
	ASSERT_EQ(2, r1.value()); ASSERT_EQ(0, r2.value());
	
	scope.connect(sender.somethingHappened(), &r2, &Reciever::increment);
	sender.fire();	// +1-0 +1-0
	ASSERT_EQ(3, r1.value()); ASSERT_EQ(1, r2.value());

	scope.connect(sender.somethingHappened(), &r1, &Reciever::decrement);
	sender.fire();	// +1-1 +1-0
	ASSERT_EQ(3, r1.value()); ASSERT_EQ(2, r2.value());

	scope.connect(sender.somethingHappened(), &r1, &Reciever::decrement);
	sender.fire();	// +1-2 +1-0
	ASSERT_EQ(2, r1.value()); ASSERT_EQ(3, r2.value());

	scope.connect(sender.somethingHappened(), &r2, &Reciever::decrement);
	sender.fire();	// +1-2 +1-1
	ASSERT_EQ(1, r1.value()); ASSERT_EQ(3, r2.value());

	scope.connect(sender.somethingHappened(), &r2, &Reciever::increment);
	sender.fire();	// +1-2 +2-1
	ASSERT_EQ(0, r1.value()); ASSERT_EQ(4, r2.value());

	sender.somethingHappened().disconnectAll(&r2, &Reciever::decrement);
	sender.fire();	// +1-2 +2-0
	ASSERT_EQ(-1, r1.value()); ASSERT_EQ(6, r2.value());

	sender.somethingHappened().disconnectOne(&r1, &Reciever::decrement);
	sender.fire();	// +1-1 +2-0
	ASSERT_EQ(-1, r1.value()); ASSERT_EQ(8, r2.value());

	sender.somethingHappened().disconnectAll(&r1, &Reciever::increment);
	sender.fire();	// +0-1 +2-0
	ASSERT_EQ(-2, r1.value()); ASSERT_EQ(10, r2.value());

	sender.somethingHappened().disconnectOne(&r2, &Reciever::increment);
	sender.fire();	// +0-1 +1-0
	ASSERT_EQ(-3, r1.value()); ASSERT_EQ(11, r2.value());

	sender.somethingHappened().disconnectAll();
	sender.fire();	// +0-0 +0-0
	ASSERT_EQ(-3, r1.value()); ASSERT_EQ(11, r2.value());
}
//------------------------------------------------------------------------------
/*
	This test checks automatic disconnection
*/
TEST(Test_ConnectDisconnect, AutomaticDisconnect)
{
	Cpp::ConnectionScope scope0;
	Reciever r0;
	{
		Sender sender;

		sender.fire();
		{
			Reciever r1;
			{
				Cpp::ConnectionScope scope1;
				scope1.connect(sender.somethingHappened(), &r1, &Reciever::increment);
				ASSERT_EQ(0, r1.value());
				sender.fire();
				ASSERT_EQ(1, r1.value());
			}
			sender.fire();
			ASSERT_EQ(1, r1.value());
			{
				Cpp::ConnectionScope scope2;
				scope2.connect(sender.somethingHappened(), &r1, &Reciever::decrement);
				ASSERT_EQ(1, r1.value());
				sender.fire();
				ASSERT_EQ(0, r1.value());
			}
			sender.fire();
			ASSERT_EQ(0, r1.value());

			{
				scope0.connect(sender.somethingHappened(), &r0, &Reciever::setValue, 5);
				sender.fire();
				ASSERT_EQ(5, r0.value());
				r0.setValue(-1);
				sender.fire();
				ASSERT_EQ(5, r0.value());
			}
		}
		r0.setValue(-1);
		sender.fire();
		ASSERT_EQ(5, r0.value());
		ASSERT_NE(0, scope0.connectionCount());
	}
	ASSERT_EQ(0, scope0.connectionCount());
}
//------------------------------------------------------------------------------
/*
	This test ensures that adding connections inside delegate works fine.
*/
TEST(Test_ConnectDisconnect, ConnectFromDelegate)
{
	int const arraySize= 8;
	RecieverEx rcv[arraySize];
	Cpp::ConnectionScope scope;
	SenderEx sender;

	rcv[0].connect(0, arraySize, &sender, &scope);

	ASSERT_EQ(0, rcv[0].value());
	ASSERT_EQ(0, rcv[1].value());
	ASSERT_EQ(0, rcv[2].value());
	ASSERT_EQ(0, rcv[3].value());
	ASSERT_EQ(0, rcv[4].value());
	ASSERT_EQ(0, rcv[5].value());
	ASSERT_EQ(0, rcv[6].value());
	ASSERT_EQ(0, rcv[7].value());
	ASSERT_EQ(1, sender.somethingHappened().connectionCount());
	
	sender.runStage();
	ASSERT_EQ(1, rcv[0].value());
	ASSERT_EQ(0, rcv[1].value());
	ASSERT_EQ(0, rcv[2].value());
	ASSERT_EQ(0, rcv[3].value());
	ASSERT_EQ(0, rcv[4].value());
	ASSERT_EQ(0, rcv[5].value());
	ASSERT_EQ(0, rcv[6].value());
	ASSERT_EQ(0, rcv[7].value());
	ASSERT_EQ(2, sender.somethingHappened().connectionCount());

	sender.runStage();
	ASSERT_EQ(2, rcv[0].value());
	ASSERT_EQ(1, rcv[1].value());
	ASSERT_EQ(0, rcv[2].value());
	ASSERT_EQ(0, rcv[3].value());
	ASSERT_EQ(0, rcv[4].value());
	ASSERT_EQ(0, rcv[5].value());
	ASSERT_EQ(0, rcv[6].value());
	ASSERT_EQ(0, rcv[7].value());
	ASSERT_EQ(4, sender.somethingHappened().connectionCount());

	sender.runStage();
	ASSERT_EQ(3, rcv[0].value());
	ASSERT_EQ(2, rcv[1].value());
	ASSERT_EQ(1, rcv[2].value());
	ASSERT_EQ(1, rcv[3].value());
	ASSERT_EQ(0, rcv[4].value());
	ASSERT_EQ(0, rcv[5].value());
	ASSERT_EQ(0, rcv[6].value());
	ASSERT_EQ(0, rcv[7].value());
	ASSERT_EQ(8, sender.somethingHappened().connectionCount());

	sender.runStage();
	ASSERT_EQ(4, rcv[0].value());
	ASSERT_EQ(3, rcv[1].value());
	ASSERT_EQ(2, rcv[2].value());
	ASSERT_EQ(2, rcv[3].value());
	ASSERT_EQ(1, rcv[4].value());
	ASSERT_EQ(1, rcv[5].value());
	ASSERT_EQ(1, rcv[6].value());
	ASSERT_EQ(1, rcv[7].value());
	ASSERT_EQ(8, sender.somethingHappened().connectionCount());
}
//------------------------------------------------------------------------------
} //namespace ConnectDisconnect
} //namespace UnitTests