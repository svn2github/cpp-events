#include <Cpp/Events.hpp>
#include <gtest/gtest.h>
#include <locale>

int main(int argc, char * argv[])
{
	setlocale(LC_ALL, "");
	::testing::InitGoogleTest(&argc, argv);
	Cpp::Threading::ProcessInit processInit;
	return RUN_ALL_TESTS();
}
