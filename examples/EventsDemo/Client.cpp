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
