
// KeXueJiSuanQIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KeXueJiSuanQI.h"
#include "KeXueJiSuanQIDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CKeXueJiSuanQIDlg dialog



CKeXueJiSuanQIDlg::CKeXueJiSuanQIDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_KEXUEJISUANQI_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKeXueJiSuanQIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_PC, m_pc);
}

BEGIN_MESSAGE_MAP(CKeXueJiSuanQIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_32771, &CKeXueJiSuanQIDlg::On32771)
	ON_BN_CLICKED(IDC_BUTTON1, &CKeXueJiSuanQIDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CKeXueJiSuanQIDlg message handlers

BOOL CKeXueJiSuanQIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_Sheet.AddPage(&m_page2);
	m_Sheet.AddPage(&m_page1);
	

	m_Sheet.Create(this, WS_CHILD | WS_VISIBLE, 0);
	m_Sheet.ModifyStyleEx(0, WS_EX_CONTROLPARENT);
	m_Sheet.ModifyStyle(0, WS_TABSTOP);
	m_Sheet.SetWindowPos(NULL, 0, 100, 100, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CKeXueJiSuanQIDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CKeXueJiSuanQIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CKeXueJiSuanQIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#include"DialogL.h"

void CKeXueJiSuanQIDlg::On32771()
{
	// TODO: Add your command handler code here
	CDialogL dlg;
	INT_PTR nResponse = dlg.DoModal();
	DestroyWindow();
	if (nResponse == IDOK)               // 判断返回值是否为OK按钮（其ID为IDOK，已经将它删除）   
	{
		// TODO: Place code here to handle when the dialog is   
		//  dismissed with OK   
	}
	else if (nResponse == IDCANCEL)      // 判断返回值是否为Cancel按钮（其ID为IDCANCEL，将它的Caption改为了“退出”）   
	{
		// TODO: Place code here to handle when the dialog is   
		//  dismissed with Cancel   
	}
}

#include"CfirstDlg.h"

void CKeXueJiSuanQIDlg::OnBnClickedButton1()
{

	// TODO: Add your control notification handler code here
	CfirstDlg *m_page = new CfirstDlg;// CPage 是子窗体所关联的类名。
	m_page->Create(IDD_DIALOG1, this); // 通过create方法来创建一个子窗体。其中IDD_XXX是子窗体的ID号。
	//CRect re;
	//ScreenToClient(re); // 将屏幕坐标移到客户区坐标。可以尝试着注释一下，仔细观察一下子窗体位置的区别
	//m_page->MoveWindow(re);// 将子窗体移动到PictureCtrl控件的位置。
	//m_page->ShowWindow(SW_SHOW);//  显示子窗体。
	m_page->SetWindowPos(NULL, 0, 10, 100,0, SWP_SHOWWINDOW);

}
