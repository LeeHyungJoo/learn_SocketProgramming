#pragma once

// CListenSocket ��� ����Դϴ�.

class CListenSocket : public CAsyncSocket
{
public:
	CListenSocket();
	virtual ~CListenSocket();

	//����� Ŭ���̾�Ʈ�� ���� ��ü�� �����ϱ� ���� ���� ����Ʈ.
	CPtrList	m_listClient;
	virtual void OnAccept(int nErrorCode);
	void CloseClient(CSocket* pClient);
	void SendMessageAll(TCHAR* pszMessage, int nSize);
	void CloseAll();
};


