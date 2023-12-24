// ClientSocket.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MfcChattingServer.h"
#include "ClientSocket.h"
//CListenSocket 클래스 선언이 기술된 헤더파일 포함.
#include "ListenSocket.h"

// CClientSocket

CClientSocket::CClientSocket(CListenSocket &sock)
: m_Listen(sock)
{
}

CClientSocket::~CClientSocket()
{
}


// CClientSocket 멤버 함수


void CClientSocket::OnClose(int nErrorCode)
{
	CSocket::OnClose(nErrorCode);
	//다음 코드를 실행하면 이 소켓 객체는 소멸한다.
	m_Listen.CloseClient(this);
}


void CClientSocket::OnReceive(int nErrorCode)
{
	TCHAR szBuffer[1024] = { 0 };
	//한 클라이언트로부터 메시지를 수신하면
	int nRecv = Receive(szBuffer, sizeof(szBuffer));
	if (nRecv > 0)
		//연결된 모든 클라이언트에게 전송한다.
		m_Listen.SendMessageAll(szBuffer, nRecv);

	CSocket::OnReceive(nErrorCode);
}
