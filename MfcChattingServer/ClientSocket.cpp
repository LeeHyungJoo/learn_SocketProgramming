// ClientSocket.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MfcChattingServer.h"
#include "ClientSocket.h"
//CListenSocket Ŭ���� ������ ����� ������� ����.
#include "ListenSocket.h"

// CClientSocket

CClientSocket::CClientSocket(CListenSocket &sock)
: m_Listen(sock)
{
}

CClientSocket::~CClientSocket()
{
}


// CClientSocket ��� �Լ�


void CClientSocket::OnClose(int nErrorCode)
{
	CSocket::OnClose(nErrorCode);
	//���� �ڵ带 �����ϸ� �� ���� ��ü�� �Ҹ��Ѵ�.
	m_Listen.CloseClient(this);
}


void CClientSocket::OnReceive(int nErrorCode)
{
	TCHAR szBuffer[1024] = { 0 };
	//�� Ŭ���̾�Ʈ�κ��� �޽����� �����ϸ�
	int nRecv = Receive(szBuffer, sizeof(szBuffer));
	if (nRecv > 0)
		//����� ��� Ŭ���̾�Ʈ���� �����Ѵ�.
		m_Listen.SendMessageAll(szBuffer, nRecv);

	CSocket::OnReceive(nErrorCode);
}
