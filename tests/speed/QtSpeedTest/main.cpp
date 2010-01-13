#include <QtCore/QCoreApplication>
#include "Objects.hpp"
#include <ctime>
#include <stdio.h>

#define CASE_NO(X) X##1
#define CASE_NAME "Normalized signatures"
#define CONNECT_STRING QObject::connect(&sender, SIGNAL(testSignal(float)), &rcv, SLOT(processFloat(float)));
#include "test.inl"
#undef CASE_NO
#undef CASE_NAME
#undef CONNECT_STRING

#define CASE_NO(X) X##2
#define CASE_NAME "Denormalized signatures"
#define CONNECT_STRING QObject::connect(&sender, SIGNAL(testSignal(float const &)), &rcv, SLOT(processFloat(float const &)));
#include "test.inl"
#undef CASE_NO
#undef CASE_NAME
#undef CONNECT_STRING

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	runTest1();
	runTest2();
	return 0;
}

