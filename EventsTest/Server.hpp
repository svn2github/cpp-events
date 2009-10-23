#ifndef SERVER_HPP
#define SERVER_HPP

#include "../Events/Events.hpp"

class Server
{
public:
	Server(char const * name);
	virtual ~Server();

	char const * name() const { return name_; }

	EventRef1<float> dataArrived() { return &dataArrived_; }

	void processData(int count, float const * data);
private:
	char const * name_;
	Event1<float> dataArrived_;
};

#endif //SERVER_HPP