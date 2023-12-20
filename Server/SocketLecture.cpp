#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32")

DWORD WINAPI WorkerThread(LPVOID pParam)
{
	SOCKET hClient = (SOCKET)pParam;
	char szBuffer[128] = {};
	int nReceive = 0;

	puts("DBG : Connect New Client Success");

	while ((nReceive = ::recv(hClient, szBuffer, sizeof(szBuffer), 0)) > 0)
	{
		::send(hClient, szBuffer, sizeof(szBuffer), 0);
		puts(szBuffer);
		fflush(stdout);
		memset(szBuffer, 0, sizeof(szBuffer));
	}

	//4.3 클라이언트가 연결을 종료함

	puts("DBG : Disconneted Client");
	::closesocket(hClient);
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//윈도우 소켓 초기화 
	WSADATA wsa = { 0 };
	if (::WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		puts("ERR : Winsock initialize Failed");
		return 0;
	}

	//1. 접속 대기 소켓 생성 
	SOCKET hSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (hSocket == INVALID_SOCKET)
	{
		puts("ERR : Fail to Create socket");
		return 0;
	}

	//바인딩 전에 재사용 소켓 옵션 설정 (2개 띄워보기)
	BOOL bOption = TRUE;
	if (::setsockopt(hSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&bOption, sizeof(BOOL)) == SOCKET_ERROR)
	{
		puts("ERR : Failed to Set Sockopt");
		return 0;
	}

	//2. 포트 바인딩 
	SOCKADDR_IN	serverAddr = { 0 };
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(25000); 
	serverAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	if (::bind(hSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		puts("ERR : Fail to Bind Socket's IP / Port");
		return 0;
	}

	//소켓의 "송신" 버퍼의 크기를 확인
	int nBufSize = 0, nLen = sizeof(nBufSize);
	if (::getsockopt(hSocket, SOL_SOCKET, SO_SNDBUF, (char*)&nBufSize, &nLen) != SOCKET_ERROR)
	{
		printf("Send Buffer Size : %d \n", nBufSize);
	}

	//소켓의 "송신" 버퍼의 크기를 확인
	nBufSize = 0, nLen = sizeof(nBufSize);
	if (::getsockopt(hSocket, SOL_SOCKET, SO_RCVBUF, (char*)&nBufSize, &nLen) != SOCKET_ERROR)
	{
		printf("Recv Buffer Size : %d \n", nBufSize);
	}

	//3. 접속 대기 상태로 전환 
	if (::listen(hSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		puts("ERR : Fail to listen");
		return 0;
	}

	//4. 클라이언트 접속 처리 및 대응 
	SOCKADDR_IN clientAddr = { 0 };
	int nAddLen = sizeof(clientAddr);
	SOCKET hClient = 0;
	DWORD dwThreadID = 0;
	HANDLE hThread;

	//4-1. 클라이언트 연결 & 새로운 소켓 생성 (개방)
	while((hClient = accept(hSocket, (sockaddr*)&clientAddr, &nAddLen)) != INVALID_SOCKET)
	{
		//4-2 클라이언트와 통신하기 위한 스레드 생성. 클라이언트마다 새 스레드 생성
		hThread = ::CreateThread(
			NULL,
			0,
			WorkerThread,
			(LPVOID)hClient,
			0,
			&dwThreadID
		);

		if (hThread != NULL)
		{
			::CloseHandle(hThread);
		}
	}

	::WSACleanup();
	return 0;
}


