
// MFC_FTP.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMFC_FTPApp:
// �� Ŭ������ ������ ���ؼ��� MFC_FTP.cpp�� �����Ͻʽÿ�.
//

class CMFC_FTPApp : public CWinApp
{
public:
	CMFC_FTPApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMFC_FTPApp theApp;