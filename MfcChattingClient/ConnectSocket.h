#pragma once

// CConnectSocket ��� ����Դϴ�.

class CConnectSocket : public CSocket
{
public:
	CConnectSocket();
	virtual ~CConnectSocket();
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};


