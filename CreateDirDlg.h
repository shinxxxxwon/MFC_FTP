#pragma once
#include "afxwin.h"

// CreateDirDlg ��ȭ �����Դϴ�.

class CreateDirDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CreateDirDlg)

public:
	CreateDirDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CreateDirDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public :
	CString m_strDirName;

	
	afx_msg void OnBnClickedOk();
};
