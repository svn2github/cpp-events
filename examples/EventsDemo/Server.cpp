#include "Server.hpp"

Server::Server(char const * name) : name_(name) {}
Server::~Server() {}

void Server::processData(int count, float const * data)
{
	for(int i=0; i<count; ++i)
	{
		dataArrived_.fire(data[i]);
	}
}
