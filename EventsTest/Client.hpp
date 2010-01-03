#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../Events/CppEvents.hpp"

class ISomeInterface
{
protected:
	ISomeInterface() {}
	~ISomeInterface() {}
public:
	virtual EventRef1<bool> testEvent1() = 0;
};

class BaseClass
{
public:
	BaseClass() {}
	virtual ~BaseClass() {}

	virtual EventRef1<int> testEvent2() { return &testEvent2_; }

	void fireEvent2(int x) { testEvent2_.fire(x); }
private:
	Event1<int> testEvent2_;
};

class DerivedClass : public BaseClass, public ISomeInterface
{
public:
	DerivedClass()
		: BaseClass()
	{
		BaseClass::testEvent2().connectEvent(&list_, &testEvent2x_);
		BaseClass::testEvent2().connectEvent(&list_, &eventEx_, 3.14);
	}
	~DerivedClass() {}

	virtual EventRef1<int> testEvent2() { return &testEvent2x_; }
	virtual EventRef1<bool> testEvent1() { return &testEvent1_; }
private:
	Event1<bool> testEvent1_;
	Event1<int> testEvent2x_;
	Event2<double, int> eventEx_;
	ConnectionList list_;
};

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

	ConnectionList * tracker() { return &connections_; }
private:
	Server * server_;
	ConnectionList connections_;

	void processData(float x);
};

#pragma pack(pop)

#endif //CLIENT_HPP