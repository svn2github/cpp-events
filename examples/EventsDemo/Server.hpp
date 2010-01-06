#ifndef SERVER_HPP
#define SERVER_HPP

#include <Cpp/Events.hpp>

class Server
{
public:
	Server(char const * name);
	virtual ~Server();

	char const * name() const { return name_; }

	Cpp::EventRef<float> dataArrived() { return dataArrived_.ref(); }

	void processData(int count, float const * data);
private:
	char const * name_;
	Cpp::Event<float> dataArrived_;
};

#endif //SERVER_HPP