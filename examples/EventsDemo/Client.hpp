#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <Cpp/Events.hpp>

class ISomeInterface
{
protected:
	ISomeInterface() {}
	~ISomeInterface() {}
public:
	virtual Cpp::EventRef<bool> testEvent1() = 0;
};

class BaseClass
{
public:
	BaseClass() {}
	virtual ~BaseClass() {}

	virtual Cpp::EventRef<int> testEvent2() { return testEvent2_.ref(); }

	void fireEvent2(int x) { testEvent2_.fire(x); }
private:
	Cpp::Event<int> testEvent2_;
};

class DerivedClass : public BaseClass, public ISomeInterface
{
public:
	DerivedClass()
		: BaseClass()
	{
		scope_.connectEvent(BaseClass::testEvent2(), &testEvent2x_);
		scope_.connectEvent(BaseClass::testEvent2(), &eventEx_, 3.14);
	}
	~DerivedClass() {}

	virtual Cpp::EventRef<int> testEvent2() { return testEvent2x_.ref(); }
	virtual Cpp::EventRef<bool> testEvent1() { return testEvent1_.ref(); }
private:
	Cpp::Event<bool> testEvent1_;
	Cpp::Event<int> testEvent2x_;
	Cpp::Event<double, int> eventEx_;
	Cpp::ConnectionScope scope_;
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

	Cpp::ConnectionScope * tracker() { return &scope_; }
private:
	Server * server_;
	Cpp::ConnectionScope scope_;

	void processData(float x);
};

#pragma pack(pop)

#endif //CLIENT_HPP