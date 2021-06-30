#pragma once
#include "afxwin.h"

// CreateDirDlg 대화 상자입니다.

class CreateDirDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CreateDirDlg)

public:
	CreateDirDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CreateDirDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public :
	CString m_strDirName;

	
	afx_msg void OnBnClickedOk();
};
