
// MfcChattingServer.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMfcChattingServerApp:
// �� Ŭ������ ������ ���ؼ��� MfcChattingServer.cpp�� �����Ͻʽÿ�.
//

class CMfcChattingServerApp : public CWinApp
{
public:
	CMfcChattingServerApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMfcChattingServerApp theApp;