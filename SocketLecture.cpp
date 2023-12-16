#include <iostream>
#include <Windows.h>

using namespace std;

DWORD WINAPI ThreadFunc(LPVOID pParam)
{
	cout << "[ThreadFunc] Start" << endl;

	for (int i = 0; i < 10; i++)
	{
		cout << "[ThreadFunc] " << i << endl;
	}

	cout << "[ThreadFunc] End" << endl;
	return 0;
}

int main()
{
	DWORD dwThreadID = 0;
	HANDLE hThread = ::CreateThread(
		NULL,
		0,
		ThreadFunc,
		NULL,
		0,
		&dwThreadID
	);

	for (int i = 0; i < 10; ++i)
		cout << "[main] " << i << endl;

	::CloseHandle(hThread);

	return 0;
}


