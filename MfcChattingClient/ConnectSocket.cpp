// ConnectSocket.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MfcChattingClient.h"
#include "ConnectSocket.h"
//��ȭ���� Ŭ������ ���� ������ ����� ��������� �����Ѵ�.
#include "MfcChattingClientDlg.h"


// CConnectSocket

CConnectSocket::CConnectSocket()
{
}

CConnectSocket::~CConnectSocket()
{
}


// CConnectSocket ��� �Լ�


void CConnectSocket::OnReceive(int nErrorCode)
{
	TCHAR szBuffer[1024] = { 0 };
	if (Receive(szBuffer, sizeof(szBuffer)) > 0)
	{
		//��ȭ���� ������ ��ü�� ���� �ּҸ� �˾Ƴ���.
		CMfcChattingClientDlg *pDlg = NULL;
		pDlg = (CMfcChattingClientDlg*)AfxGetMainWnd();

		//����Ʈ �ڽ��� ��µ� ���ڿ� �׸��� ������ Ȯ���Ѵ�.
		int nCount = pDlg->m_List.GetCount();
		//������ ���ڿ��� ����Ʈ �ڽ��� �߰��� �� �����Ѵ�.
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

	pDlg->m_List.InsertString(nCount, _T("ERROR: ������ ������ ������ϴ�!"));
	pDlg->m_List.SetCurSel(nCount);

	CSocket::OnClose(nErrorCode);
}
