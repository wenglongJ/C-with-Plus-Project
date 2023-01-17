
// SINGLEView.cpp : implementation of the CSINGLEView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "SINGLE.h"
#endif

#include "SINGLEDoc.h"
#include "SINGLEView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSINGLEView

IMPLEMENT_DYNCREATE(CSINGLEView, CView)

BEGIN_MESSAGE_MAP(CSINGLEView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSINGLEView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CSINGLEView construction/destruction

CSINGLEView::CSINGLEView()
{
	// TODO: add construction code here

}

CSINGLEView::~CSINGLEView()
{
}

BOOL CSINGLEView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CSINGLEView drawing

void CSINGLEView::OnDraw(CDC* /*pDC*/)
{
	CSINGLEDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CSINGLEView printing


void CSINGLEView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSINGLEView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSINGLEView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSINGLEView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

//void CSINGLEView::OnRButtonUp(UINT /* nFlags */, CPoint point)
//{
//	ClientToScreen(&point);
//	OnContextMenu(this, point);
//}

void CSINGLEView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSINGLEView diagnostics

#ifdef _DEBUG
void CSINGLEView::AssertValid() const
{
	CView::AssertValid();
}

void CSINGLEView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSINGLEDoc* CSINGLEView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSINGLEDoc)));
	return (CSINGLEDoc*)m_pDocument;
}
#endif //_DEBUG


// CSINGLEView message handlers


void CSINGLEView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CMenu menu;       // 菜单（包含主菜单栏和子菜单）   
	CMenu *pSubMenu;  // 右键菜单   

					  // 加载菜单资源到menu对象   
	menu.LoadMenu(IDR_POPUP_EDIT);
	// 因为右键菜单是弹出式菜单，不包含主菜单栏，所以取子菜单   
	pSubMenu = menu.GetSubMenu(0);
	// 将坐标值由客户坐标转换为屏幕坐标   
	ClientToScreen(&point);
	// 弹出右键菜单，菜单左侧与point.x坐标值对齐   
	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);

	CView::OnRButtonDown(nFlags, point);
}
