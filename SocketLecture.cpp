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

	cout << "Event Set In Thread" << endl;
	SetEvent((HANDLE)pParam);
	cout << "Event Set End In Thread" << endl;

	cout << "[ThreadFunc] End" << endl;
	return 0;
}

int main()
{
	HANDLE hEvent = CreateEvent(
		NULL,	//보안 속성. 상속 어쩌구.. 인데 아직 뭔지 모르겠음.
		FALSE,	//Set 상태가 되었을때 Set 상태 유지할 것인지 옵션.
		FALSE,	//초기 상태 (reset 상태)
		NULL	//프로세스가 여러개일 때 사용한다. 커널 오브젝트에 이름 붙일때 사용.
	);

	DWORD dwThreadID = 0;
	HANDLE hThread = CreateThread(
		NULL, 			// 보안 속성 NULL 일 경우, 상속받겠다는 의미
		0,				// 스택 메모리. 0이면 기본 크기 (1MB)
		ThreadFunc, 	// 스레드로 실행할 함수 이름
		hEvent,			// 함수에 전달할 매개변수
		0,				// 생성 플래그는 기본 값 사용
		&dwThreadID		// 생성된 스레드 ID 저장.
	);	

	for (int i = 0; i < 10; ++i)
	{
		cout << "[main] " << i << endl;
		//main thread - i 가 3이 될때, hEvent 가 Set 될때까지 기다림.
		if (i == 3 && WaitForSingleObject(hEvent, INFINITE) == WAIT_OBJECT_0)
		{
			cout << "[main] wait for event" << endl;
		}
	}

	CloseHandle(hThread);

	return 0;
}


