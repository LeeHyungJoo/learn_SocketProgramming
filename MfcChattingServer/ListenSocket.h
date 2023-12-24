#pragma once

// CListenSocket 명령 대상입니다.

class CListenSocket : public CAsyncSocket
{
public:
	CListenSocket();
	virtual ~CListenSocket();

	//연결된 클라이언트들 소켓 객체를 관리하기 위한 연결 리스트.
	CPtrList	m_listClient;
	virtual void OnAccept(int nErrorCode);
	void CloseClient(CSocket* pClient);
	void SendMessageAll(TCHAR* pszMessage, int nSize);
	void CloseAll();
};


