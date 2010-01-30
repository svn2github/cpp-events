// Copyright (c) 2010 Nickolas Pohilets
//
// This file is a part of the CppEvents library.
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

#include <Windows.h>
#include <Std/Assert.hpp>

class Thread
{
public:
	Thread() : hThread_() {}
	~Thread() { CloseHandle(hThread_); }

	bool start()
	{
		assert(!hThread_);

		hThread_ = ::CreateThread(
			NULL, 0,
			&Thread::threadProc,
			reinterpret_cast<void*>(this),
			0, NULL
		);

		return (hThread_ != 0);
	}

	void join()
	{
		::WaitForSingleObject(hThread_, INFINITE);
	}
protected:
	virtual void run() = 0;
private:
	HANDLE hThread_;

	static DWORD WINAPI threadProc(LPVOID param)
	{
		reinterpret_cast<Thread*>(param)->run();
		return 0;
	}
};
