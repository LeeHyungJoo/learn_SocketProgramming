#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32")

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
	char szBuffer[128] = {};
	int nReceive = 0;

	//4-1. 클라이언트 연결 & 새로운 소켓 생성 (개방)
	while((hClient = accept(hSocket, (sockaddr*)&clientAddr, &nAddLen)) != INVALID_SOCKET)
	{
		puts("DBG : Connect New Client Success");
		fflush(stdout);

		//4-2. 클라이언트로부터 문자열을 수신함. 
		while ((nReceive = ::recv(hClient, szBuffer, sizeof(szBuffer), 0)) > 0)
		{
			//4-3. 수신한 문자열 그대로 반향 전송. 
			::send(hClient, szBuffer, sizeof(szBuffer), 0);
			puts(szBuffer); 
			fflush(stdout);
			memset(szBuffer, 0, sizeof(szBuffer));
		}

		//4.3 클라이언트가 연결을 종료함
		::shutdown(hSocket, SD_BOTH);
		::closesocket(hClient);
		puts("DBG : Disconneted Client");
		fflush(stdout);
	}


	return 0;
}


