
#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32")

int _tmain(int argc, _TCHAR* argv[])
{
	// 윈도우 소켓 초기화 
	WSADATA wsa = { 0 };
	if (::WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		puts("ERR : Failed To Initailiz Winsock");
		return 0;
	}

	// 1. 접속 대기 소켓 생성
	SOCKET hSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (hSocket == INVALID_SOCKET)
	{
		puts("ERR : Failed To Create Socket! ");
		return 0;
	}

	// 2. 포트 바인딩 및 연결
	SOCKADDR_IN serverAddr = { 0 };
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(25000);
	serverAddr.sin_addr.S_un.S_addr = inet_addr("222.98.33.167");
	if (::connect(hSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		puts("ERR : Failed To Connet to Server");
		return 0;
	}

	// 3. 채팅 메세지 송/수신
	char szBuffer[128] = { 0 };
	while (true)
	{
		gets_s(szBuffer);
		if (strcmp(szBuffer, "QUIT") == 0)break;

		::send(hSocket, szBuffer, strlen(szBuffer) + 1, 0);
		memset(szBuffer, 0, sizeof(szBuffer));
		::recv(hSocket, szBuffer, sizeof(szBuffer), 0);
		printf("From Server : %s \n", szBuffer);
	}

	// 4. 소켓을 닫고 종료. 
	::closesocket(hSocket);
	::WSACleanup();
	return 0;
}
