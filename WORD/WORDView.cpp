
// WORDView.cpp : implementation of the CWORDView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "WORD.h"
#endif

#include "WORDDoc.h"
#include "WORDView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWORDView

IMPLEMENT_DYNCREATE(CWORDView, CView)

BEGIN_MESSAGE_MAP(CWORDView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_CHAR()
END_MESSAGE_MAP()

// CWORDView construction/destruction

CWORDView::CWORDView()
{
	// TODO: add construction code here
	m_strLine = "";
	m_nIndex = -1;
}

CWORDView::~CWORDView()
{
}

BOOL CWORDView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW, LoadCursor(NULL, IDC_CROSS),
		(HBRUSH)GetStockObject(BLACK_BRUSH), 0);
	//cs.lpszClass = L"sunxin";
	return CView::PreCreateWindow(cs);
}

// CWORDView drawing

void CWORDView::OnDraw(CDC* pDC)
{
	CWORDDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CString str(_T("VC++深入编程"));
	pDC->TextOut(50, 50, str);
	


	CSize sz = pDC->GetTextExtent(str);

	str.LoadString(ID_FILE_NEW);
	pDC->TextOut(50, 150, str);

	pDC->BeginPath();
	pDC->Rectangle(50, 50, 50 + sz.cx, 50 + sz.cy);
	pDC->EndPath();
	pDC->SelectClipPath(RGN_AND);
	for (int i = 0; i < 300; i += 10) {
		pDC->MoveTo(0, i);
		pDC->LineTo(300, i);
		pDC->MoveTo(i, 0);
		pDC->LineTo(i, 300);
	}
	
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CWORDView printing

BOOL CWORDView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CWORDView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CWORDView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CWORDView diagnostics

#ifdef _DEBUG
void CWORDView::AssertValid() const
{
	CView::AssertValid();
}

void CWORDView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWORDDoc* CWORDView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWORDDoc)));
	return (CWORDDoc*)m_pDocument;
}
#endif //_DEBUG


// CWORDView message handlers

#include "resource.h"
int CWORDView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	CClientDC dc(this);
	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);
	CreateSolidCaret(tm.tmAveCharWidth/8,tm.tmHeight*2);
	ShowCaret();


	SetClassLong(m_hWnd, GCL_HBRBACKGROUND,(LONG)GetStockObject(WHITE_BRUSH));
	SetClassLong(m_hWnd, GCL_HCURSOR, (LONG)LoadCursor(NULL,IDC_CROSS));
	//bitmap.LoadBitmap(IDB_BITMAP1);
	//CreateCaret(&bitmap);
	//ShowCaret();
	return 0;
}


void CWORDView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	SetCaretPos(point);
	m_strLine.Empty();
	m_ptOrigin = point;
	CView::OnLButtonDown(nFlags, point);
}


void CWORDView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
	 //TODO: Add your message handler code here and/or call default
	CClientDC dc(this);
	CFont font;
	font.CreatePointFont(300, _T("宋体"), NULL);
	CFont *pOldFont = dc.SelectObject(&font);
	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);
	if (0x0d == nChar) {     //回车
		//m_ptOrigin.y += tm.tmHeight;
		if (0 == ++m_nIndex) {
			m_menu.CreatePopupMenu();
			GetParent()->GetMenu()->AppendMenuW(MF_POPUP, (UINT)m_menu.m_hMenu, L"PhoneBook");
			GetParent()->DrawMenuBar();
		}
		m_menu.AppendMenuW(MF_STRING, 111, m_strLine.Left(m_strLine.Find(' ')));
		m_strArray.Add(m_strLine);
		m_strLine.Empty();
		Invalidate();
	}
	else if (0x08 == nChar) {  //退格
		COLORREF clr = dc.SetTextColor(dc.GetBkColor());
		dc.TextOutW(m_ptOrigin.x, m_ptOrigin.y, m_strLine);
		m_strLine = m_strLine.Left(m_strLine.GetLength() - 1);
		HideCaret();
		dc.SetTextColor(clr);

	}
	else {
		m_strLine += (TCHAR)nChar;
	}
	CSize sz = dc.GetTextExtent(m_strLine);
	CPoint pt;
	pt.x = m_ptOrigin.x + sz.cx;
	pt.y = m_ptOrigin.y;
	SetCaretPos(pt);
	dc.TextOutW(m_ptOrigin.x, m_ptOrigin.y, m_strLine);
	

	CView::OnChar(nChar, nRepCnt, nFlags);
}
