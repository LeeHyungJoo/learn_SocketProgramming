
// MfcChattingServerDlg.h : ��� ����
//

#pragma once
//CListenSocket Ŭ������ ������ ����� ������� ����.
#include "ListenSocket.h"

// CMfcChattingServerDlg ��ȭ ����
class CMfcChattingServerDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CMfcChattingServerDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

	//Ŭ���̾�Ʈ ������ �񵿱������� ����� ���� ���� ��ü.
	CListenSocket	m_ListenSocket;

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MFCCHATTINGSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();
};
