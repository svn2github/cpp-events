#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../Events/ConnectionList.hpp"

class Server;

#pragma pack(push, 16)

class Client
{
public:
	Client();
	~Client();

	Server * server() const { return server_; }
	void setServer(Server * serv);

	void test();

	void registerData(Server * server);
private:
	Server * server_;
	ConnectionList connections_;

	void processData(float x);
};

#pragma pack(pop)

#endif //CLIENT_HPP