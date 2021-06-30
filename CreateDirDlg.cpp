// CreateDirDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFC_FTP.h"
#include "CreateDirDlg.h"
#include "afxdialogex.h"


// CreateDirDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CreateDirDlg, CDialogEx)

CreateDirDlg::CreateDirDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CreateDirDlg::IDD, pParent)
{

}

CreateDirDlg::~CreateDirDlg()
{
}

void CreateDirDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CreateDirDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CreateDirDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CreateDirDlg 메시지 처리기입니다.


void CreateDirDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItemText(IDC_EDIT_DIRNAME, m_strDirName);
	CDialogEx::OnOK();
}
