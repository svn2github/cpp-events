#include <iostream>

class BaseClass;

void printer(BaseClass * pbase);

class BaseClass
{
public:
	BaseClass()
	{
		std::cout << "BaseClass::BaseClass(): vtbl = " << *(void**)this << std::endl;
		printer(this);
	}

	virtual ~BaseClass()
	{
		printer(this);
		std::cout << "BaseClass::~BaseClass(): vtbl = " << *(void**)this << std::endl;
	}

	virtual void print()
	{
		std::cout << "BaseClass::print()" << std::endl;
	}
};

class DerivedClass : public BaseClass
{
public:
	DerivedClass()
		: BaseClass()
	{
		std::cout << "DerivedClass::DerivedClass(): vtbl = " << *(void**)this << std::endl;
		printer(this);
	}

	virtual ~DerivedClass()
	{
		printer(this);
		std::cout << "DerivedClass::~DerivedClass(): vtbl = " << *(void**)this << std::endl;
	}

	virtual void print()
	{
		std::cout << "DerivedClass::print()" << std::endl;
	}
};

void printer(BaseClass * pbase)
{
	pbase->print();
}

int main()
{
	DerivedClass cls;
	std::cout << "----------------------" << std::endl;
	cls.print();
	std::cout << "----------------------" << std::endl;
	return 0;
}
