// ListenSocket.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MfcChattingServer.h"
#include "ListenSocket.h"
//CClientSocket 클래스의 선언이 기술된 헤더파일 포함.
#include "ClientSocket.h"

// CListenSocket

CListenSocket::CListenSocket()
{
}

CListenSocket::~CListenSocket()
{
}


// CListenSocket 멤버 함수


void CListenSocket::OnAccept(int nErrorCode)
{
	CSocket *pNewClient = new CClientSocket(*this);
	if (Accept(*pNewClient))
		//연결 리스트에 새로 연결된 클라이언트 소켓 객체를 추가.
		m_listClient.AddTail(pNewClient);
	else
	{
		delete pNewClient;
		AfxMessageBox(_T("ERROR: 클라이언트 연결을 받는데 실패했습니다."));
	}

	CAsyncSocket::OnAccept(nErrorCode);
}


void CListenSocket::CloseClient(CSocket* pClient)
{
	//연결 리스트에서 삭제할 소켓 객제를 찾아 제거한다.
	POSITION pos = m_listClient.Find(pClient);
	if (pos != NULL)
		m_listClient.RemoveAt(pos);

	//연결을 끊고 객체를 삭제한다.
	pClient->ShutDown();
	pClient->Close();
	delete pClient;
}


void CListenSocket::SendMessageAll(TCHAR* pszMessage, int nSize)
{
	//연결 리스트의 더미 헤드 노드를 찾는다.
	POSITION pos = m_listClient.GetHeadPosition();
	CSocket *pClient = NULL;

	//연결 리스트 전체 노드에 접근하고 같은 메시지를 전송한다.
	while (pos != NULL)
	{
		//현재 노드의 주소를 반환하고 다음 노드로 넘어간다.
		pClient = (CSocket*)m_listClient.GetNext(pos);
		if (pClient != NULL)
			pClient->Send(pszMessage, nSize);
	}
}


void CListenSocket::CloseAll()
{
	//접속 대기 서버 소켓을 닫는다.
	ShutDown();
	Close();

	//모든 클라이언트와의 연결을 끝내고 객체를 소멸시킨다.
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
