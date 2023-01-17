
// ClipboardDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Clipboard.h"
#include "ClipboardDlg.h"
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


// CClipboardDlg dialog



CClipboardDlg::CClipboardDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CLIPBOARD_DIALOG, pParent)
	, m_str(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	hRead = NULL;
	hWrite = NULL;
}

CClipboardDlg::~CClipboardDlg()
{
	if (hRead) {
		CloseHandle(hRead);
	}
	if (hWrite) {
		CloseHandle(hWrite);
	}
}


void CClipboardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RECV, m_str);
}

BEGIN_MESSAGE_MAP(CClipboardDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CClipboardDlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_RECV, &CClipboardDlg::OnBnClickedButtonRecv)
	ON_BN_CLICKED(IDC_PIPE_WRITE, &CClipboardDlg::OnBnClickedPipeWrite)
	ON_BN_CLICKED(IDC_PIPE_READ, &CClipboardDlg::OnBnClickedPipeRead)
END_MESSAGE_MAP()


// CClipboardDlg message handlers

BOOL CClipboardDlg::OnInitDialog()
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
	hRead = GetStdHandle(STD_INPUT_HANDLE);
	hWrite = GetStdHandle(STD_OUTPUT_HANDLE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CClipboardDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CClipboardDlg::OnPaint()
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
HCURSOR CClipboardDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CClipboardDlg::OnBnClickedButtonSend()
{
	// TODO: Add your control notification handler code here
	if (OpenClipboard()) {
		CString str;
		HANDLE hClip;
		char *pData;
		char *pBuf;
		EmptyClipboard();

		GetDlgItemText(IDC_EDIT_SEND, str);

		USES_CONVERSION;
		pData = T2A(str);

		hClip = GlobalAlloc(GMEM_MOVEABLE, strlen(pData) + 1);
		pBuf = (char*)GlobalLock(hClip);
		strcpy_s(pBuf, strlen(pData) + 1, pData);
		GlobalUnlock(hClip);
		SetClipboardData(CF_TEXT, hClip);
		CloseClipboard();
	}
}


void CClipboardDlg::OnBnClickedButtonRecv()
{
	// TODO: Add your control notification handler code here
	if (OpenClipboard()) {
		if (IsClipboardFormatAvailable(CF_TEXT)) {
			HANDLE hClip;
			char *pBuf;
			hClip = GetClipboardData(CF_TEXT);
			pBuf = (char *)GlobalLock(hClip);
			GlobalUnlock(hClip);
			USES_CONVERSION;
			
			m_str = pBuf;
		}
		CloseClipboard();
	}
	UpdateData(false);
}


void CClipboardDlg::OnBnClickedPipeWrite()
{
	// TODO: Add your control notification handler code here
	char buf[] = "匿名管道测试程序！";
	DWORD dwWrite;
	if (!WriteFile(hWrite, buf, strlen(buf) + 1, &dwWrite, NULL)) {
		MessageBox(_T("写入数据失败！"));
		return;
	}
}


void CClipboardDlg::OnBnClickedPipeRead()
{
	// TODO: Add your control notification handler code here
	char buf[100];
	DWORD dwRead;
	if (!ReadFile(hRead, buf, 100, &dwRead, NULL)) {
		MessageBox(_T("读取数据失败！"));
		return;
	}
	USES_CONVERSION;
	MessageBox(A2T(buf));
}
