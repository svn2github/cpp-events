#include "TestClass.hpp"

static int magic = 0x11223344;

int TestClass::testOutlineFunction()
{
	return someData_ * (int)reinterpret_cast<size_t>(&magic);
}

int TestClass::testOutlineFunctionWithStaticVariable()
{
	static int staticVar = -1;
	staticVar += testOutlineFunction();
	return staticVar;
}

void getTestData1(TestDataArray * d)
{
	GET_TEST_DATA_IMPL();
}
