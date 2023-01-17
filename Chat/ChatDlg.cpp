
// ChatDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Chat.h"
#include "ChatDlg.h"
#include "afxdialogex.h"
#include "ClientSocket.h"

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


// CChatDlg dialog



CChatDlg::CChatDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CHAT_DIALOG, pParent)
	, m_uPort(5000)
	, m_sShowString(_T(""))
	, m_sInputText(_T(""))
	, m_sName(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PORT, m_uPort);
	DDX_Text(pDX, IDC_SHOWTEXT, m_sShowString);
	DDX_Text(pDX, IDC_INPUTTEXT, m_sInputText);
	DDX_Text(pDX, IDC_NAME, m_sName);
	DDV_MinMaxUInt(pDX, m_uPort, 1024, 100000);
}

BEGIN_MESSAGE_MAP(CChatDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT, &CChatDlg::OnBnClickedConnect)
	ON_BN_CLICKED(IDC_SETSERVER, &CChatDlg::OnBnClickedSetserver)
	ON_BN_CLICKED(IDC_SEND, &CChatDlg::OnBnClickedSend)
	ON_EN_CHANGE(IDC_INPUTTEXT, &CChatDlg::OnEnChangeInputtext)
END_MESSAGE_MAP()


// CChatDlg message handlers

BOOL CChatDlg::OnInitDialog()
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
	if (AfxSocketInit(NULL) == 0) {
		AfxMessageBox(_T("CSocket Inital Error"));
	}
	BYTE f0, f1, f2, f3;
	CString name;
	CClientSocket::GetLocalHostName(name);
	CClientSocket::GetIpAddress(name, f0, f1, f2, f3);
	((CIPAddressCtrl*)(GetDlgItem(IDC_SERVERIP)))->SetAddress(f0, f1, f2, f3);

	m_bInit = false;
	m_bClient = false;
	m_clientsocket = new CClientSocket;
	m_pListenSocket = new CServerSocket;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CChatDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CChatDlg::OnPaint()
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
HCURSOR CChatDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CChatDlg::OnBnClickedConnect()
{
	// TODO: Add your control notification handler code here
	if (!m_bInit) {
		BYTE f0, f1, f2, f3;
		CString name;
		((CIPAddressCtrl *)(GetDlgItem(IDC_SERVERIP)))->GetAddress(f0, f1, f2, f3);
		CString ip;
		ip.Format(_T("%d.%d.%d.%d"), f0, f1, f2, f3);
		m_bClient = true;
		m_clientsocket->Create();
		if (m_clientsocket->Connect(ip, GetDlgItemInt(IDC_PORT))) {
			m_clientsocket->Init(this);
			SetDlgItemText(IDC_SHOWTEXT,_T("Client Connection Succend"));
			m_bInit = true;
		}
		else {
			m_clientsocket->Close();
			AfxMessageBox(_T("Client Connection failed"));
			m_bInit = false;
		}
	}
}


void CChatDlg::OnBnClickedSetserver()
{
	// TODO: Add your control notification handler code here
	if (!m_bInit) {
		m_bClient = false;
		m_bInit = true;
		if (m_pListenSocket->Init(GetDlgItemInt(IDC_PORT), this) == FALSE) {
			m_bInit = false;
			return;
		}
	}
}


void CChatDlg::OnBnClickedSend()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (!m_bInit) {
		AfxMessageBox(_T("Not Connection to the Server"));
		return;
	}
	CString in;
	CString str_name;
	CMessg msg;
	GetDlgItemText(IDC_INPUTTEXT, in);
	GetDlgItemText(IDC_NAME, str_name);
	if (in.GetLength() == 0) {
		return;
	}
	if (m_sName=="") {
		AfxMessageBox(_T("Please input your Name"));
		return;
	}
	in.TrimRight(_T(" "));                  //消除从左侧起的空格，防止发送空白
	SetDlgItemText(IDC_INPUTTEXT, in);
	if (in.GetLength()) {
		m_sMsgList += str_name + _T("说:");
		m_sMsgList += in + _T("\r\n");

		SetDlgItemText(IDC_SHOWTEXT, m_sMsgList);
		int m_iLineCurrentPos = ((CEdit *)(GetDlgItem(IDC_SHOWTEXT)))->GetLineCount();
		((CEdit *)(GetDlgItem(IDC_SHOWTEXT)))->LineScroll(m_iLineCurrentPos);        //当Edit遇到最后一行，自动向上滚动
		msg.m_strText = str_name + "说：" + in;
		if (!m_bClient) {
			POSITION pos;
			for (pos = m_connectionList.GetHeadPosition(); pos != NULL;) {
				CClientSocket *t = (CClientSocket *)m_connectionList.GetNext(pos);
				t->SendMessage(&msg);
			}
		}
		else {
			m_clientsocket->SendMessage(&msg);
		}
		SetDlgItemText(IDC_INPUTTEXT, _T(""));
	}
}

void CChatDlg::ProcessPendingAccept() {
	CClientSocket *pSocket = new CClientSocket();
	if (m_pListenSocket->Accept(*pSocket)) {
		CMessg msg;
		msg.m_strText = "一个游客进入了聊天室了";
		m_sShowString += "一个游客进入聊天室了\n";
		POSITION pos;
		for (pos = m_connectionList.GetHeadPosition(); pos != NULL;) {
			CClientSocket *t = (CClientSocket *)m_connectionList.GetNext(pos);
			t->SendMessage(&msg);
		}
		pSocket->Init(this);
		m_connectionList.AddTail(pSocket);
	}
	else {
		delete pSocket;
	}
}
void CChatDlg::CloseSessionSocket() {
	if (!m_bClient) {
		for (POSITION pos = m_connectionList.GetHeadPosition(); pos != NULL;) {
			POSITION t_pos = pos;
			CClientSocket *t = (CClientSocket *)m_connectionList.GetNext(pos);
			if (t->m_bClose == true) {
				m_connectionList.RemoveAt(t_pos);
			}
		}
	}
}
void CChatDlg::ClearContent() {
	if (!m_bClient) {
		m_clientsocket->Close();
	}
	else {
		m_pListenSocket->Close();
		m_connectionList.RemoveAll();
	}
	m_bInit = false;
	m_sMsgList = "";
	SetDlgItemText(IDC_INPUTTEXT, _T(""));
	SetDlgItemText(IDC_SHOWTEXT, _T(""));
}

void CChatDlg::OnClearconnection() {
	ClearContent();
}


void CChatDlg::OnEnChangeInputtext()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
