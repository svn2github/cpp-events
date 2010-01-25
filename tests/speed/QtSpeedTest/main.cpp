// Copyright (c) 2010 Nickolas Pohilets
//
// This file is a part of the benchmarking suit for the CppEvents library and
// its analogues.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

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

