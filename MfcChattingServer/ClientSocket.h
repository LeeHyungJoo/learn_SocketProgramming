#pragma once

//Ŭ���� ���� ���� ����(Forward declaration)
class CListenSocket;

// CClientSocket ��� ����Դϴ�.

class CClientSocket : public CSocket
{
public:
	CClientSocket(CListenSocket &sock);
	virtual ~CClientSocket();

	CListenSocket &m_Listen;
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};


