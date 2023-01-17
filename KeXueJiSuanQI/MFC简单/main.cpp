#include"stdafx.h"
#include"main.h"
BEGIN_MESSAGE_MAP(CMFCFrmWnd, CFrameWnd)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_PAINT()
END_MESSAGE_MAP()
BOOL CMFCApp::InitInstance()
{
	m_pMainWnd = new CMFCFrmWnd();
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return true;
}
CMFCFrmWnd::CMFCFrmWnd()
{
	m_nTextX = 260;
	m_nTextY = 40;
	m_pOldFont = NULL;
	Create(NULL, _T("InsideMFC"));
}
void CMFCFrmWnd::OnLButtonDblClk(UINT uFlag, CPoint pt)
{
	MessageBox(_T("HELLO WORLD!"), NULL, MB_OK|MB_YESNOCANCEL);
}
void CMFCFrmWnd::OnPaint()
{
	CPaintDC dc(this);

	dc.TextOut(0, 0, _T("HELLO WORLD!"));
	m_newFont.CreatePointFont(180, _T("隶书"));
	m_pOldFont = (CFont*)dc.SelectObject(&m_newFont);
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(255, 255, 0));
	dc.TextOutW(m_nTextX, 40, _T("欢迎来到鸡啄米1！"));
	dc.SetTextColor(RGB(0, 255, 0));
	dc.TextOutW(40, m_nTextY, _T("欢迎来到鸡啄米2！"));
	dc.SelectObject(m_pOldFont);

}
CMFCApp theApp;