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
		NULL, 			// 보안 속성 NULL 일 경우, 상속받겠다는 의미
		0,				// 스택 메모리. 0이면 기본 크기 (1MB)
		ThreadFunc, 	// 스레드로 실행할 함수 이름
		NULL,			// 함수에 전달할 매개변수
		0,				// 생성 플래그는 기본 값 사용
		&dwThreadID		// 생성된 스레드 ID 저장.
	);	

	for (int i = 0; i < 10; ++i)
		cout << "[main] " << i << endl;

	::CloseHandle(hThread);

	return 0;
}


