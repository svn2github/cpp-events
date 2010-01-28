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

Client::Client()
: server_(), scope_()
{
}

Client::~Client()
{
}

void Client::setServer(Server * serv)
{
	if(server_)
	{
		scope_.disconnectOne(server_->dataArrived());
	}
	
	server_ = serv;
	
	if(server_)
	{
		scope_.connect(server_->dataArrived(), this, &Client::processData);
	}
}

void Client::test()
{
	static float const data[] = {1.24234f, 2.3423f, 5.35346f, 5.3546f, 7.43655235f };
	
	if(server_)
	{
		server_->processData(sizeof(data)/sizeof(data[0]), data);
	}
}

void Client::registerData(Server * server)
{
	printf("data from server \"%s\" arrived\n", server->name());
}

void Client::processData(float x)
{
	printf("Client::processData(%hf)\n", x);
}
