// CreateDirDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFC_FTP.h"
#include "CreateDirDlg.h"
#include "afxdialogex.h"


// CreateDirDlg ��ȭ �����Դϴ�.

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


// CreateDirDlg �޽��� ó�����Դϴ�.


void CreateDirDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	GetDlgItemText(IDC_EDIT_DIRNAME, m_strDirName);
	CDialogEx::OnOK();
}
