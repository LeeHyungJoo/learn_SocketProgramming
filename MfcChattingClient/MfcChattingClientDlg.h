
// MfcChattingClientDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
//헤더파일 추가
#include "ConnectSocket.h"

// CMfcChattingClientDlg 대화 상자
class CMfcChattingClientDlg : public CDialogEx
{
// 생성입니다.
public:
	CMfcChattingClientDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MFCCHATTINGCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_strMessage;
	CListBox m_List;
	//서버에 연결하기 위한 소켓 객체
	CConnectSocket	m_Socket;
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnBnClickedButtonClose();
};

