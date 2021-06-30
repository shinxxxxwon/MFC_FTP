
// MFC_FTPDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include <afxinet.h>
#include <windows.h>
#include "CreateDirDlg.h"


// CMFC_FTPDlg ��ȭ ����
class CMFC_FTPDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CMFC_FTPDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MFC_FTP_DIALOG };

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
	
	CString m_strIP, m_strID, m_strPass, m_strFileName;
	CString m_strPath, m_strFileClass, m_strAllPath, m_strTitle;
	CString m_strFtpFile, m_strLocalFile;
	CString m_strRemoveTitle;

	BOOL m_bConnect, m_bThreadStart;

	int m_nPort;

	CInternetSession m_Session;
	CFtpConnection* m_pConnection;
	CFtpFileFind* m_pFileFind;
	CInternetFile* m_pFile;
	CWinThread* m_Thread;

	CButton m_BtnConnectStat;
	CButton m_BtnUpload;
	CListBox m_List;

	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnLbnDblclkList();
	afx_msg void OnBnClickedButtonUpload();
	afx_msg void OnMenuRemove();
	afx_msg void OnMenuCreatedir();

	void ShowList();
	void DownLoad();
	void ChangeDirectory();
	void UpLoad();
	void Connect();
	void Remove();
	void CreateDir();
	void RemoveFile(CString strPath);
	void RemoveDir(CString strPath/*CString strFileName*/);

	static UINT ThreadFunction1(LPVOID pParam);
	afx_msg void OnBnClickedButtonDownload();
};

UINT ThreadDownLoad(LPVOID pParam);
UINT ThreadUpLoad(LPVOID pParam);
UINT ThreadRemove(LPVOID pParam);
UINT ThreadCreateDir(LPVOID pParam);
UINT ThreadConnect(LPVOID pParam);