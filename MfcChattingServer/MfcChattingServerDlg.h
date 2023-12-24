
// MfcChattingServerDlg.h : 헤더 파일
//

#pragma once
//CListenSocket 클래스의 선언이 기술된 헤더파일 포함.
#include "ListenSocket.h"

// CMfcChattingServerDlg 대화 상자
class CMfcChattingServerDlg : public CDialogEx
{
// 생성입니다.
public:
	CMfcChattingServerDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

	//클라이언트 접속을 비동기적으로 대기할 서버 소켓 객체.
	CListenSocket	m_ListenSocket;

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MFCCHATTINGSERVER_DIALOG };

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
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();
};
