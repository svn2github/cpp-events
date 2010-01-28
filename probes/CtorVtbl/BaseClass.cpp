#include "BaseClass.hpp"
#include "Tester.hpp"

class BaseClass
{
public:
	BaseClass(Tester * tester)
		: tester_;
	{
		tester->baseCtor(this);
	}

	virtual ~BaseClass()
	{
		Tester
	}

	virtual void print()
	{
		std::cout << "BaseClass::print()" << std::endl;
	}

	virtual ClassId classId() { return BaseClassId; }

};