#pragma once

//클래스 선언에 대한 선언(Forward declaration)
class CListenSocket;

// CClientSocket 명령 대상입니다.

class CClientSocket : public CSocket
{
public:
	CClientSocket(CListenSocket &sock);
	virtual ~CClientSocket();

	CListenSocket &m_Listen;
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};


