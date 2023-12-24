// ListenSocket.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MfcChattingServer.h"
#include "ListenSocket.h"
//CClientSocket Ŭ������ ������ ����� ������� ����.
#include "ClientSocket.h"

// CListenSocket

CListenSocket::CListenSocket()
{
}

CListenSocket::~CListenSocket()
{
}


// CListenSocket ��� �Լ�


void CListenSocket::OnAccept(int nErrorCode)
{
	CSocket *pNewClient = new CClientSocket(*this);
	if (Accept(*pNewClient))
		//���� ����Ʈ�� ���� ����� Ŭ���̾�Ʈ ���� ��ü�� �߰�.
		m_listClient.AddTail(pNewClient);
	else
	{
		delete pNewClient;
		AfxMessageBox(_T("ERROR: Ŭ���̾�Ʈ ������ �޴µ� �����߽��ϴ�."));
	}

	CAsyncSocket::OnAccept(nErrorCode);
}


void CListenSocket::CloseClient(CSocket* pClient)
{
	//���� ����Ʈ���� ������ ���� ������ ã�� �����Ѵ�.
	POSITION pos = m_listClient.Find(pClient);
	if (pos != NULL)
		m_listClient.RemoveAt(pos);

	//������ ���� ��ü�� �����Ѵ�.
	pClient->ShutDown();
	pClient->Close();
	delete pClient;
}


void CListenSocket::SendMessageAll(TCHAR* pszMessage, int nSize)
{
	//���� ����Ʈ�� ���� ��� ��带 ã�´�.
	POSITION pos = m_listClient.GetHeadPosition();
	CSocket *pClient = NULL;

	//���� ����Ʈ ��ü ��忡 �����ϰ� ���� �޽����� �����Ѵ�.
	while (pos != NULL)
	{
		//���� ����� �ּҸ� ��ȯ�ϰ� ���� ���� �Ѿ��.
		pClient = (CSocket*)m_listClient.GetNext(pos);
		if (pClient != NULL)
			pClient->Send(pszMessage, nSize);
	}
}


void CListenSocket::CloseAll()
{
	//���� ��� ���� ������ �ݴ´�.
	ShutDown();
	Close();

	//��� Ŭ���̾�Ʈ���� ������ ������ ��ü�� �Ҹ��Ų��.
	CSocket *pClient = NULL;
	POSITION pos = m_listClient.GetHeadPosition();
	while (pos != NULL)
	{
		pClient = (CSocket*)m_listClient.GetNext(pos);
		if (pClient != NULL)
		{
			pClient->ShutDown();
			pClient->Close();
			delete pClient;
		}
	}

	m_listClient.RemoveAll();
}
