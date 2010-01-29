// Copyright (c) 2010 Nickolas Pohilets
//
// This file is a part of the sandbox project for the CppEvents library.

// It is used for development purposes only and is not a part of the
// public distribution.
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

#include "Client.hpp"
#include "Server.hpp"
#include <stdio.h>

/* Try#1 */
/*
typedef char False;
typedef struct { char data[100]; } True;

template<class T> True is_polymorphic(T * ptr, void const * retVal = dynamic_cast<void const*>(ptr));
False is_polymorphic(...);
*/

/* Try #2 */
template<class T> class PolymorphicTestHelper : T
{
	virtual ~PolymorphicTestHelper() = 0;
};

template<class T> inline bool isPolymorphic()
{
	return sizeof(PolymorphicTestHelper<T>) == sizeof(T);
}

class TestClass
{
private:
	TestClass();
	~TestClass();
};

void main()
{
	Cpp::Events::ProcessInit processInit;

	bool x = isPolymorphic<TestClass>();

	int const size_of_Client = sizeof(Client);
	int const size_of_PolymorphicTestHelper = sizeof(PolymorphicTestHelper<Client>);

	if(isPolymorphic<Client>())
		printf("Client - polymorphic\n");
	else
		printf("Client - non-polymorphic\n");

	if(isPolymorphic<Server>())
		printf("Server - polymorphic\n");
	else
		printf("Server - non-polymorphic\n");

	Server * server1 = new Server("Server1");
	Server * server2 = new Server("Server2");

	{
		Client client;
		client.setServer(server1);
		printf("{1}\n");
		client.test();
	}

	static float const data1[] = {1.1111f, 2.2222f };
	static float const data2[] = {3.3333f, 4.4444f };
	static float const data3[] = {5.5555f, 6.6666f };

	server1->processData(2, data1);

	{
		Client client;
		
		client.tracker()->connect(server1->dataArrived(), &client, &Client::registerData, server1);
		client.tracker()->connect(server2->dataArrived(), &client, &Client::registerData, server2);

		printf("{2}\n");
		server1->processData(2, data2);
		server2->processData(2, data3);
		printf("{3}\n");
		client.test();
		printf("{4}\n");
		client.setServer(server1);
		server1->processData(2, data2);
		server2->processData(2, data3);
		printf("{5}\n");
		client.setServer(server2);
		server1->processData(2, data2);
		server2->processData(2, data3);
		printf("{6}\n");
		client.setServer(0);
		server1->processData(2, data2);
		server2->processData(2, data3);
		printf("{7}\n");

		server2->dataArrived().disconnectOne(&client, &Client::registerData);
		server1->dataArrived().disconnectOne(&client, &Client::registerData);
	}

	server1->processData(2, data2);
	server2->processData(2, data3);

	printf("{8}\n");

	delete server1; delete server2;

	DerivedClass obj;
	obj.fireEvent2(211);
}