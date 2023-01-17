
// Doc-ViewView.cpp : implementation of the CDocViewView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Doc-View.h"
#endif

#include "Doc-ViewDoc.h"
#include "Doc-ViewView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDocViewView

IMPLEMENT_DYNCREATE(CDocViewView, CView)

BEGIN_MESSAGE_MAP(CDocViewView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CDocViewView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CDocViewView construction/destruction

CDocViewView::CDocViewView()
{
	// TODO: add construction code here

}

CDocViewView::~CDocViewView()
{
}

BOOL CDocViewView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CDocViewView drawing

void CDocViewView::OnDraw(CDC* /*pDC*/)
{
	CDocViewDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CDocViewView printing


void CDocViewView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CDocViewView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDocViewView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDocViewView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CDocViewView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CDocViewView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CDocViewView diagnostics

#ifdef _DEBUG
void CDocViewView::AssertValid() const
{
	CView::AssertValid();
}

void CDocViewView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDocViewDoc* CDocViewView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDocViewDoc)));
	return (CDocViewDoc*)m_pDocument;
}
#endif //_DEBUG


// CDocViewView message handlers
