
// MFC_FTPDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MFC_FTP.h"
#include "MFC_FTPDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFC_FTPDlg ��ȭ ����



CMFC_FTPDlg::CMFC_FTPDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFC_FTPDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC_FTPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Control(pDX, IDC_BUTTON_CONNECT, m_BtnConnectStat);
	DDX_Control(pDX, IDC_BUTTON_UPLOAD, m_BtnUpload);
}

BEGIN_MESSAGE_MAP(CMFC_FTPDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CMFC_FTPDlg::OnBnClickedButtonConnect)
	ON_WM_RBUTTONDOWN()
	ON_WM_CONTEXTMENU()
	ON_LBN_DBLCLK(IDC_LIST, &CMFC_FTPDlg::OnLbnDblclkList)
	ON_BN_CLICKED(IDC_BUTTON_UPLOAD, &CMFC_FTPDlg::OnBnClickedButtonUpload)
	ON_WM_MENUSELECT()
	ON_COMMAND(ID_MENU_REMOVE, &CMFC_FTPDlg::OnMenuRemove)
	ON_COMMAND(ID_MENU_CREATEDIR, &CMFC_FTPDlg::OnMenuCreatedir)
	ON_BN_CLICKED(IDC_BUTTON_DOWNLOAD, &CMFC_FTPDlg::OnBnClickedButtonDownload)
END_MESSAGE_MAP()


// CMFC_FTPDlg �޽��� ó����

BOOL CMFC_FTPDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	m_pConnection = NULL;
	m_pFile = NULL;
	m_bConnect = FALSE;
	m_BtnConnectStat.SetWindowText(_T("Connect"));
	m_strAllPath = "/";
	SetDlgItemText(IDC_STATIC_PATH, m_strAllPath);
	GetDlgItem(IDC_BUTTON_UPLOAD)->ShowWindow(SW_HIDE);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CMFC_FTPDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMFC_FTPDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CMFC_FTPDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




//======================================
//On Message
//======================================
void CMFC_FTPDlg::OnBnClickedButtonConnect()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_Thread = AfxBeginThread(ThreadConnect, this);
	if(m_Thread == NULL)
	{
		MessageBox(_T("Thread Fail"), NULL, MB_OK);
		return;
	}
}



void CMFC_FTPDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	CMenu popup;
	CMenu* pMenu;

	popup.LoadMenu(IDR_MENU1);
	pMenu = popup.GetSubMenu(0);

	pMenu->TrackPopupMenu(TPM_LEFTALIGN || TPM_RIGHTBUTTON, point.x, point.y, this);


}

void CMFC_FTPDlg::OnLbnDblclkList()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	m_pConnection->GetCurrentDirectory(m_strPath);
	int nIndex = m_List.GetCurSel();

	if(nIndex < 0)
		return;

	m_List.GetText(nIndex, m_strTitle);

	if(m_strTitle.Left(3) == "[F]")
	{
		m_Thread = AfxBeginThread(ThreadDownLoad, this);
		if(m_Thread == NULL)
		{
			MessageBox(_T("Thread Fail"), NULL, MB_OK);
			return;
		}
	}
	else if(m_strTitle.Left(3) == "[D]" || m_strTitle.Left(3) == "..")
	{
		ChangeDirectory();
	}
}

void CMFC_FTPDlg::OnBnClickedButtonDownload()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_pConnection->GetCurrentDirectory(m_strPath);
	int nIndex = m_List.GetCurSel();

	if(nIndex < 0)
		return;

	m_List.GetText(nIndex, m_strTitle);

	if(m_strTitle.Left(3) == "[F]")
	{
		m_Thread = AfxBeginThread(ThreadDownLoad, this);
		if(m_Thread == NULL)
		{
			MessageBox(_T("Thread Fail"), NULL, MB_OK);
			return;
		}
	}
}



void CMFC_FTPDlg::OnBnClickedButtonUpload()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_Thread = AfxBeginThread(ThreadUpLoad, this);
	if(m_Thread == NULL)
	{
		MessageBox(_T("Thread Fail"), NULL, MB_OK);
		return;
	}
}

void CMFC_FTPDlg::OnMenuRemove()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_Thread = AfxBeginThread(ThreadRemove, this);
	if(m_Thread == NULL)
	{
		MessageBox(_T("Tread Fail"), NULL, MB_OK);
		return;
	}
}

void CMFC_FTPDlg::OnMenuCreatedir()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_Thread = AfxBeginThread(ThreadCreateDir, this);

	if(m_Thread == NULL)
	{
		MessageBox(_T("Tread Fail"), NULL, MB_OK);
		return;
	}	
}

//==============================================
//METHOD
//==============================================
void CMFC_FTPDlg::ShowList()
{
	m_List.ResetContent();

	m_pFileFind = new CFtpFileFind(m_pConnection);
	CString strFileName;
	m_pConnection->SetCurrentDirectory(m_strPath);
	BOOL bWorking = m_pFileFind->FindFile(_T("*"));
	m_List.InsertString(-1, _T(".."));
	while(bWorking)
	{
		bWorking = m_pFileFind->FindNextFile();
		if(m_pFileFind->IsNormal())
		{
			m_strFileClass = _T("[F]");
			m_strFileName = m_pFileFind->GetFileName();
			strFileName = m_strFileClass + m_strFileName;
			m_List.InsertString(-1, strFileName);
		}
		else if(m_pFileFind->IsDirectory())
		{
			m_strFileClass = _T("[D]");
			m_strFileName = m_pFileFind->GetFileName();
			strFileName = m_strFileClass + m_strFileName;
			m_List.InsertString(-1, strFileName);
		}
	}
	delete m_pFileFind;
}

void CMFC_FTPDlg::DownLoad()
{
	CString strPath = _T("C:\\test");
	m_strTitle.Delete(0,3);
	m_strFtpFile.Format(_T("%s/%s"), m_strPath, m_strTitle);
	m_strLocalFile.Format(_T("%s\\%s"), strPath, m_strTitle);
	BOOL bGetResult = m_pConnection->GetFile(m_strFtpFile, m_strLocalFile, FALSE,FILE_ATTRIBUTE_NORMAL,FTP_TRANSFER_TYPE_ASCII | INTERNET_FLAG_RELOAD,NULL);

	if(bGetResult)
	{
		MessageBox(_T("DownLoad Success!"));
		return;
	}
	else
	{
		MessageBox(_T("DownLoad Fail!"));
		return;
	}
}

void CMFC_FTPDlg::ChangeDirectory()
{
	CString strTemp;
	if(m_strTitle.Left(3) == "[D]")
	{
		m_strTitle.Delete(0,3);
	
		m_pConnection->SetCurrentDirectory(m_strTitle);
		m_pConnection->GetCurrentDirectory(m_strPath);
		if(m_strPath.Right(1) != "/")
		{
			m_strPath.Format(m_strPath+"/");
		}
		m_strAllPath.Format(m_strPath);
		m_pConnection->GetCurrentDirectory(m_strPath);
		SetDlgItemText(IDC_STATIC_PATH, m_strAllPath);
	}
	else if(m_strTitle == "..")
	{		
		int nTotalLength = m_strAllPath.GetLength();
		//int nCount = m_strAllPath.ReverseFind('/');
		//m_strAllPath.Delete(nCount+1, nTotalLength);
		//strTmp = m_strAllPath;

		int nCount = m_strAllPath.Find(m_strFileName);
		m_strAllPath.Delete(nCount, nTotalLength);

		if(m_strAllPath == "")
		{
			m_pConnection->SetCurrentDirectory(_T("/"));
			m_pConnection->GetCurrentDirectory(m_strPath);
			m_pConnection->GetCurrentDirectory(m_strAllPath);
			SetDlgItemText(IDC_STATIC_PATH, _T("/"));
		}
		else
		{
		m_pConnection->SetCurrentDirectory(m_strAllPath);
		m_pConnection->GetCurrentDirectory(m_strPath);
		SetDlgItemText(IDC_STATIC_PATH, m_strAllPath);
		}
	}
	UpdateWindow();	
	ShowList();
}

void CMFC_FTPDlg::UpLoad()
{
	static TCHAR BASED_CODE szFilter[] = _T("�������(*.*)|*.*||");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);

	if(IDOK == dlg.DoModal())
	{
		m_strLocalFile = dlg.GetPathName();
		m_strFileName = dlg.GetFileName();
	}
	m_strFtpFile.Format(_T("%s/%s"), m_strPath, m_strFileName);
	BOOL bPutResult = m_pConnection->PutFile(m_strLocalFile, m_strFtpFile);

	if(bPutResult)
	{
		MessageBox(_T("UpLoad Success!"));
		ShowList();
		return;
	}
	else
	{
		MessageBox(_T("UpLoad Fail!"));
		return;
	}
}

void CMFC_FTPDlg::Connect()
{
	if(m_bConnect == FALSE)
	{
		GetDlgItemText(IDC_EDIT_IP, m_strIP);
		GetDlgItemText(IDC_EDIT_ID, m_strID);
		GetDlgItemText(IDC_EDIT_PASS, m_strPass);
		m_nPort = GetDlgItemInt(IDC_EDIT_PORT);

		m_pConnection = m_Session.GetFtpConnection(m_strIP, m_strID, m_strPass, m_nPort, FALSE);

		if(!m_pConnection)
		{
			MessageBox(_T("Disconnected"));
			m_pConnection = NULL;
			m_pConnection->Close();
			return;
		}

		m_BtnConnectStat.SetWindowText(_T("Disconnect"));
		m_bConnect = TRUE;
		MessageBox(_T("Connected"));
		GetDlgItem(IDC_BUTTON_UPLOAD)->ShowWindow(SW_SHOWNORMAL);

		m_pConnection->SetCurrentDirectory(_T("/"));
		m_pConnection->GetCurrentDirectory(m_strPath);
		SetDlgItemText(IDC_STATIC_PATH, m_strPath);

		ShowList();
		return;
	}
	else
	{
		m_BtnConnectStat.SetWindowText(_T("Connect"));
		MessageBox(_T("Disconnected"));
		m_pConnection = NULL;
		m_pConnection->Close();
	}
}

void CMFC_FTPDlg::RemoveFile(CString strPath)
{
	BOOL bRemove;
	CString strRemoveFile = strPath;
	bRemove =  m_pConnection->Remove(strPath);
	if(bRemove)
	{
		MessageBox(_T("Remove Success!!"), NULL, MB_OK);
		ShowList();
		return;
	}
	else
	{
		MessageBox(_T("Remove Fail!!"), NULL, MB_OK);
		return;
	}
}

void CMFC_FTPDlg::RemoveDir(CString strPath /*CString strFileName*/)
{
	CFtpFileFind finder = CFtpFileFind(m_pConnection);
	BOOL bWorking = TRUE;
	
	m_pConnection->SetCurrentDirectory(strPath);
	CString strDirFile;
	strDirFile.Format(_T("%s/*.*"), strPath);
	/*MessageBox(_T("strDirFile"));
	MessageBox(strDirFile);*/
	bWorking = finder.FindFile(strDirFile);
	while(bWorking)
	{
		bWorking = finder.FindNextFile();
		if(finder.IsNormal())
		{
			/*MessageBox(_T("finder.GetFilePathFile()"));
			MessageBox(finder.GetFilePath());*/
			RemoveFile(finder.GetFilePath());
		}
		if(finder.IsDirectory())
		{
			CString strRmDir;
			/*MessageBox(_T("finder.GetFilePathDIR()"));
			MessageBox(finder.GetFilePath());*/
			strRmDir.Format(finder.GetFilePath());
			/*if(strRmDir.Right(1) != "/")
			{
				strRmDir.Format(strRmDir + "/");
			}*/
			RemoveDir(strRmDir);
		}
	}
	finder.Close();
	m_pConnection->RemoveDirectory(strPath);
}

void CMFC_FTPDlg::Remove()
{	
	int nResult = MessageBox(_T("������ �����Ͻðڽ��ϱ�?"), NULL, MB_YESNO);
	int nIndex = -1;
	nIndex = m_List.GetCurSel();

	if(nIndex == -1)
	{
		MessageBox(_T("������ �׸��� �������ּ���"));
		return;
	}

	m_List.GetText(nIndex, m_strRemoveTitle);

	if(m_strPath.Right(1) != "/")
	{
		m_strPath += "/";
	}
	if(nResult == IDYES)
	{
		CString strTemp;
		if(m_strRemoveTitle.Left(3) == "[F]")
		{
			m_strRemoveTitle.Delete(0,3);
			strTemp.Format(m_strPath);
			if(strTemp.Right(1) != "/")
			{
				strTemp.Format(strTemp + "/");
			}
			strTemp.Format(strTemp + m_strRemoveTitle);
			RemoveFile(strTemp);
			m_pConnection->SetCurrentDirectory(m_strPath);
			SetDlgItemText(IDC_STATIC_PATH,m_strPath);
			ShowList();
		}
		else if(m_strRemoveTitle.Left(3) == "[D]")
		{
			m_strRemoveTitle.Delete(0,3);
			strTemp.Format(m_strPath);
			if(strTemp.Right(1) != _T("/"))
			{
				strTemp.Format(strTemp + _T("/"));
			}
			strTemp.Format(strTemp + m_strRemoveTitle);
			RemoveDir(strTemp);
			m_pConnection->SetCurrentDirectory(m_strPath);
			SetDlgItemText(IDC_STATIC_PATH, m_strPath);
			ShowList();
		}
	}
	else if(nResult == IDNO)
	{
		MessageBox(_T("Cancel!!"), NULL, MB_OK);
	}
}

void CMFC_FTPDlg::CreateDir()
{
	CreateDirDlg CreateDirdlg;
	CreateDirdlg.DoModal();

	//m_pConnection->GetCurrentDirectory(m_strPath);

	CString strDirName;

	strDirName = CreateDirdlg.m_strDirName;
	CString strDirTemp;
	if(m_strAllPath.Right(1) != "/")
	{
		m_strAllPath.Format(m_strAllPath + "/");
	}
	strDirTemp.Format(m_strAllPath + strDirName);

	BOOL bCreateDir = m_pConnection->CreateDirectory(strDirTemp);

	if(bCreateDir)
	{
		MessageBox(_T("Create Dir Success"), NULL, MB_OK);
	}
	else
	{
		MessageBox(_T("Create Dir Fail"), NULL, MB_OK);
	}
	ShowList();
}
//============================================
//Thread
//============================================
UINT ThreadDownLoad(LPVOID pParam)
{
	CMFC_FTPDlg* pDlg = (CMFC_FTPDlg*)pParam;
	CFileFind find;
	CString strFile = _T("*.*");
	BOOL bResult = find.FindFile(_T("C:\\test") + strFile);
	
	if(!bResult)
	{
		BOOL bDir = CreateDirectory(_T("C:\\test"), NULL);
		if(bDir)
		{
			TRACE(_T("Create Dir Success"));
			TRACE(_T("C:\test"));
		}
		else
		{
			TRACE(_T("Create Dir Fail"));
			return 0;
		}
	}
	
	pDlg->DownLoad();
	return 0;
}

UINT ThreadUpLoad(LPVOID pParam)
{
	CMFC_FTPDlg* pDlg = (CMFC_FTPDlg*)pParam;

	pDlg->UpLoad();
	
	return 0;
}

UINT ThreadRemove(LPVOID pParam)
{
	CMFC_FTPDlg* pDlg = (CMFC_FTPDlg*)pParam;

	pDlg->Remove();

	return 0;
}

UINT ThreadCreateDir(LPVOID pParam)
{
	CMFC_FTPDlg* pDlg = (CMFC_FTPDlg*)pParam;

	pDlg->CreateDir();
	
	return 0;
}

UINT ThreadConnect(LPVOID pParam)
{
	CMFC_FTPDlg* pDlg = (CMFC_FTPDlg*)pParam;

	pDlg->Connect();
	
	return 0;
}

