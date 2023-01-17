
// CthreeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CThree.h"
#include "CThreeDlg.h"
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


// CthreeDlg dialog

CThreeDlg::CThreeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CMFCTHREE_DIALOG, pParent), m_nRows(3), m_nColumns(3)
{
	m_pTabList = NULL;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CThreeDlg::~CThreeDlg()
{
	if (m_pTabList != NULL)
	{
		m_pTabList->DestroyWindow();
		delete m_pTabList;
	}
}

void CThreeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ROWS, m_nRows);
	DDX_Text(pDX, IDC_EDIT_COLUMNS, m_nColumns);
}

BEGIN_MESSAGE_MAP(CThreeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_CREATETABLE, &CThreeDlg::OnBnClickedBtnCreateTable)
END_MESSAGE_MAP()


// CthreeDlg message handlers

BOOL CThreeDlg::OnInitDialog()
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CThreeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CThreeDlg::OnPaint()
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
HCURSOR CThreeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CThreeDlg::OnBnClickedBtnCreateTable()
{
	//输入为空，更新数据失败，返回
	if (!UpdateData())
	{
		return;
	}

	//对于极大值或者小于等于0的表格画不出来
	//禁止用户创建0行或者0列的表格,对错误参数负数不做响应
	if (m_nColumns <= 0 || m_nColumns > 100 )
	{
		MessageBox("请输入一个合法有效的值!", "错误", MB_OK);
		GetDlgItem(IDC_EDIT_COLUMNS)->SetFocus();
		return;
	}
	else if (m_nRows <= 0 || m_nRows > 100)
	{
		MessageBox("请输入一个合法有效的值!", "错误", MB_OK);
		GetDlgItem(IDC_EDIT_ROWS)->SetFocus();
		return;
	}
	else
	{
		;
	}

	CRect rect;
	GetClientRect(rect);

	//表格控件位置
	CRect rectTab;
	rectTab.left = rect.left + rect.Width() / 10;
	rectTab.right = rect.right - rect.Width() / 10;
	rectTab.top = rect.top + rect.Height() / 4;
	rectTab.bottom = rect.bottom - rect.Height() / 10;

	//第一次创建，之后调用resetTable方法重设行列值
	if (m_pTabList == NULL)
	{
		m_pTabList = new CTableCtrl(m_nRows, m_nColumns);
		m_pTabList->Create("", WS_CHILD | WS_VISIBLE , rectTab, this, 12345);
	}
	else
	{
		m_pTabList->ResetTable(m_nRows, m_nColumns);
	}
}

void CThreeDlg::OnOK()
{
	;
}
