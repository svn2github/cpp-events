#include <Cpp/Events.hpp>
#include <gtest/gtest.h>
#include <locale>

int main(int argc, char * argv[])
{
	setlocale(LC_ALL, "");
	::testing::InitGoogleTest(&argc, argv);
	Cpp::Process proc;
	return RUN_ALL_TESTS();
}
