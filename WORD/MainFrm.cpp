
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "WORD.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, &CMainFrame::OnUpdateEditCut)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW, &CMainFrame::OnUpdateFileNew)
	ON_WM_TIMER()
	ON_COMMAND(IDM_TEST, &CMainFrame::OnTest)
	ON_COMMAND(ID_VIEWBAR_NEWTOOL, &CMainFrame::OnViewbarNewtool)
	ON_UPDATE_COMMAND_UI(ID_VIEWBAR_NEWTOOL, &CMainFrame::OnUpdateViewbarNewtool)
	ON_MESSAGE(UM_PROGRESS, OnProgress)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
	IDS_TIMER,
	IDS_PROGRESS,
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_bAutoMenuEnable = FALSE;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));

	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	/*
	GetMenu()->GetSubMenu(0)->CheckMenuItem(ID_FILE_NEW, MF_BYPOSITION | MF_CHECKED);
	GetMenu()->GetSubMenu(0)->SetDefaultItem(2, TRUE);

	CString str;
	str.Format(L"x=%d,y=%d", GetSystemMetrics(SM_CXMENUCHECK), GetSystemMetrics(SM_CYMENUCHECK));
	MessageBox(str);
	m_bitmap.LoadBitmap(IDB_BITMAP1);
	GetMenu()->GetSubMenu(0)->SetMenuItemBitmaps(0, MF_BYPOSITION, &m_bitmap, &m_bitmap);*/
	SetWindowLong(m_hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);


	GetMenu()->GetSubMenu(0)->EnableMenuItem(1, MF_BYPOSITION | MF_DISABLED | MF_GRAYED);
	SetMenu(NULL);

	CMenu menu;
	menu.LoadMenu(IDR_MAINFRAME);
	SetMenu(&menu);
	menu.Detach();


	menu.CreatePopupMenu();
	//GetMenu()->AppendMenuW(MF_POPUP, (UINT)menu.m_hMenu, L"Test");
	GetMenu()->InsertMenuW(2, MF_POPUP | MF_BYPOSITION, (UINT)menu.m_hMenu, L"Test");
	menu.AppendMenuW(MF_STRING, 111, L"Hello");
	menu.AppendMenuW(MF_STRING, 112, L"Bye");
	menu.AppendMenuW(MF_STRING, 113, L"Mybole");
	GetMenu()->GetSubMenu(0)->InsertMenuW(ID_FILE_OPEN, MF_STRING | MF_BYPOSITION, 115, L"VC±à³Ì");
	GetMenu()->GetSubMenu(0)->AppendMenuW(MF_STRING, 114, L"Welcome");
	menu.Detach();

	m_hIcons[0] = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_WORDTYPE));
	m_hIcons[1] = LoadIcon(theApp.m_hInstance, MAKEINTRESOURCE(IDR_MAINFRAME));
	SetClassLong(m_hWnd, GCL_HICON, (LONG)m_hIcons[0]);
	SetTimer(1, 1000, NULL);
	//SetClassLong(m_hWnd, GCL_HICON, (LONG)LoadIcon(NULL, IDI_ERROR));
	
	if (!m_newToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_RIGHT | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_newToolBar.LoadToolBar(IDR_TOOLBAR1))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	//m_newToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBar(&m_newToolBar);
	GetMenu()->GetSubMenu(3)->CheckMenuItem(ID_VIEW_NEWTOOL, MF_BYPOSITION | MF_CHECKED);
	
	CTime t = CTime::GetCurrentTime();
	CString str = t.Format("%H:%M:%S");
	CClientDC dc(this);
	CSize sz = dc.GetTextExtent(str);
	int index = 0;
	index = m_wndStatusBar.CommandToIndex(IDS_TIMER);

	m_wndStatusBar.SetPaneInfo(index, IDS_TIMER, SBPS_NORMAL, sz.cx);
	m_wndStatusBar.SetPaneText(index, str);

	m_progress.Create(WS_CHILD | WS_VISIBLE, CRect(100, 100, 200, 120), this, 123);
	m_progress.SetPos(50);

	PostMessage(UM_PROGRESS);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	//cs.cx = 600;
	//cs.cy = 400;

	WNDCLASS wndcls;
	wndcls.cbClsExtra = 0;
	wndcls.cbWndExtra = 0;
	wndcls.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndcls.hCursor = LoadCursor(NULL, IDC_HELP);
	wndcls.hIcon = LoadIcon(NULL, IDI_ERROR);
	wndcls.hInstance = AfxGetInstanceHandle();
	wndcls.lpfnWndProc = ::DefWindowProc;
	wndcls.lpszClassName = L"sunxin";
	wndcls.lpszMenuName = NULL;
	wndcls.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wndcls);
	
	//cs.lpszName = L"½¨Éè";
	//cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW, 0, 0, LoadIcon(NULL, IDI_WARNING));
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW, LoadCursor(NULL, IDC_CROSS),
		(HBRUSH)GetStockObject(BLACK_BRUSH), 0);//L"sunxin";
	//cs.style &= ~FWS_ADDTOTITLE;
	//cs.style = WS_OVERLAPPEDWINDOW;
	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers



void CMainFrame::OnUpdateEditCut(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}


void CMainFrame::OnUpdateFileNew(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	//pCmdUI->Enable(FALSE);
	if (ID_FILE_NEW == pCmdUI->m_nID)
		pCmdUI->Enable(FALSE);
}


void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	static int index = 0;
	SetClassLong(m_hWnd, GCL_HICON, (LONG)m_hIcons[index]);
	index = ++index % 3;
	CFrameWnd::OnTimer(nIDEvent);
}


void CMainFrame::OnTest()
{
	// TODO: Add your command handler code here
	MessageBox(L"Test");
}


void CMainFrame::OnViewbarNewtool()
{
	
	//if (m_newToolBar.IsWindowVisible()) {
	//	m_newToolBar.ShowWindow(SW_HIDE);
	//}
	//else {
	//	m_newToolBar.ShowWindow(SW_SHOW);
	//}
	//RecalcLayout();
	//DockControlBar(&m_newToolBar);
	ShowControlBar(&m_newToolBar, !m_newToolBar.IsWindowVisible(), FALSE);
	// TODO: Add your command handler code here
}


void CMainFrame::OnUpdateViewbarNewtool(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_newToolBar.IsWindowVisible());
}

LRESULT CMainFrame::OnProgress(WPARAM wParam, LPARAM lParam) {
	CRect rect;
	m_wndStatusBar.GetItemRect(1, &rect);
	m_progress.Create(WS_CHILD | WS_VISIBLE, rect, &m_wndStatusBar, 123);
	m_progress.SetPos(50);
	return 0;
}
