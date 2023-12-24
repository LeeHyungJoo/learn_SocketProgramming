
// MfcChattingClientDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
//������� �߰�
#include "ConnectSocket.h"

// CMfcChattingClientDlg ��ȭ ����
class CMfcChattingClientDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CMfcChattingClientDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MFCCHATTINGCLIENT_DIALOG };

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
	CString m_strMessage;
	CListBox m_List;
	//������ �����ϱ� ���� ���� ��ü
	CConnectSocket	m_Socket;
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnBnClickedButtonClose();
};

