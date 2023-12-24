// ConnectSocket.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MfcChattingClient.h"
#include "ConnectSocket.h"
//대화상자 클래스에 대한 선언이 기술된 헤더파일을 포함한다.
#include "MfcChattingClientDlg.h"


// CConnectSocket

CConnectSocket::CConnectSocket()
{
}

CConnectSocket::~CConnectSocket()
{
}


// CConnectSocket 멤버 함수


void CConnectSocket::OnReceive(int nErrorCode)
{
	TCHAR szBuffer[1024] = { 0 };
	if (Receive(szBuffer, sizeof(szBuffer)) > 0)
	{
		//대화상자 윈도우 객체에 대한 주소를 알아낸다.
		CMfcChattingClientDlg *pDlg = NULL;
		pDlg = (CMfcChattingClientDlg*)AfxGetMainWnd();

		//리스트 박스에 출력된 문자열 항목의 개수를 확인한다.
		int nCount = pDlg->m_List.GetCount();
		//수신한 문자열을 리스트 박스에 추가한 후 선택한다.
		pDlg->m_List.InsertString(nCount, szBuffer);
		pDlg->m_List.SetCurSel(nCount);
	}

	CSocket::OnReceive(nErrorCode);
}


void CConnectSocket::OnClose(int nErrorCode)
{
	CMfcChattingClientDlg* pDlg = NULL;
	pDlg = (CMfcChattingClientDlg*)AfxGetMainWnd();
	int nCount = pDlg->m_List.GetCount();

	pDlg->m_List.InsertString(nCount, _T("ERROR: 서버와 연결이 끊겼습니다!"));
	pDlg->m_List.SetCurSel(nCount);

	CSocket::OnClose(nErrorCode);
}
