
// MfcChattingClient.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMfcChattingClientApp:
// �� Ŭ������ ������ ���ؼ��� MfcChattingClient.cpp�� �����Ͻʽÿ�.
//

class CMfcChattingClientApp : public CWinApp
{
public:
	CMfcChattingClientApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMfcChattingClientApp theApp;