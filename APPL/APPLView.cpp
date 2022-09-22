
// APPLView.cpp : implementation of the CAPPLView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "APPL.h"
#endif

#include "APPLDoc.h"
#include "APPLView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAPPLView

IMPLEMENT_DYNCREATE(CAPPLView, CView)

BEGIN_MESSAGE_MAP(CAPPLView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(IDM_FILE_WRITE, &CAPPLView::OnFileWrite)
	ON_COMMAND(IDM_FILE_READ, &CAPPLView::OnFileRead)
	ON_COMMAND(ID_NAMEPIPE_CONNECTPIPE, &CAPPLView::OnNamepipeConnectpipe)
	ON_COMMAND(ID_NAMEPIPE_READPIPE, &CAPPLView::OnNamepipeReadpipe)
	ON_COMMAND(ID_NAMEPIPE_WRITEPIPE, &CAPPLView::OnNamepipeWritepipe)
END_MESSAGE_MAP()

// CAPPLView construction/destruction

CAPPLView::CAPPLView()
{
	// TODO: add construction code here
	hPipe = NULL;
}

CAPPLView::~CAPPLView()
{
	if (hPipe) {
		CloseHandle(hPipe);
	}
}

BOOL CAPPLView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CAPPLView drawing

void CAPPLView::OnDraw(CDC* /*pDC*/)
{
	CAPPLDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CAPPLView printing

BOOL CAPPLView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CAPPLView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CAPPLView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CAPPLView diagnostics

#ifdef _DEBUG
void CAPPLView::AssertValid() const
{
	CView::AssertValid();
}

void CAPPLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAPPLDoc* CAPPLView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAPPLDoc)));
	return (CAPPLDoc*)m_pDocument;
}
#endif //_DEBUG


// CAPPLView message handlers


void CAPPLView::OnFileWrite()
{
	// TODO: Add your command handler code here
	CFile file(L"1.txt", CFile::modeCreate | CFile::modeWrite);
	CArchive ar(&file, CArchive::store);
	int i = 4;
	char ch = 'a';
	float f = 1.3f;
	CString str("http://www.phei.com.cn");

	ar << i << ch << f << str;
}


void CAPPLView::OnFileRead()
{
	// TODO: Add your command handler code here
	CFile file(L"1.txt", CFile::modeRead);
	CArchive ar(&file, CArchive::load);
	int i ;
	char ch;
	float f;
	CString str;
	CString strResult;

	ar >> i >> ch >> f >> str;
	strResult.Format(L"%d,%c,%f,%s", i, ch, f, str);
	MessageBox(strResult);
}




void CAPPLView::OnNamepipeConnectpipe()
{
	// TODO: Add your command handler code here
	if (!WaitNamedPipe(_T("\\\\.\\pipe\\MyPipe"), NMPWAIT_WAIT_FOREVER)) {
		MessageBox(_T("当前没有可用的命名管道实例！"));
		return;
	}
	hPipe = CreateFile(_T("\\\\.\\pipe\\MyPipe"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hPipe) {
		MessageBox(_T("打开命名管道失败！"));
		hPipe = NULL;
		return;
	}
}


void CAPPLView::OnNamepipeReadpipe()
{
	// TODO: Add your command handler code here
	char buf[100] = { 0 };
	DWORD dwRead;
	//HANDLE readFinishEvent = CreateEvent(
	//	NULL,   // default security attributes
	//	TRUE,   // manual-reset event
	//	FALSE,  // initial state is nonsignaled
	//	NULL    // unnamed
	//);
	//OVERLAPPED ovl;
	//ZeroMemory(&ovl, sizeof(ovl));
	//ovl.hEvent = readFinishEvent;
	if (!ReadFile(hPipe, buf, 100, &dwRead, NULL)) {
		MessageBox(_T("读取数据失败！"));
		return;
	}
	USES_CONVERSION;
	MessageBox(A2T(buf));
}


void CAPPLView::OnNamepipeWritepipe()
{
	// TODO: Add your command handler code here
	char bufs[100] = "命名管道测试！";
	DWORD dwWrite;
	if (!WriteFile(hPipe, bufs, strlen(bufs) + 1, &dwWrite, NULL)) {
		MessageBox(_T("写入数据失败！"));
		return;
	}
}
