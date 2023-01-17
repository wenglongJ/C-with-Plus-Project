
// ParentView.cpp : implementation of the CParentView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Parent.h"
#endif

#include "ParentDoc.h"
#include "ParentView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CParentView

IMPLEMENT_DYNCREATE(CParentView, CView)

BEGIN_MESSAGE_MAP(CParentView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(IDM_PIPE_CREATE, &CParentView::OnPipeCreate)
	ON_COMMAND(IDM_PIPE_READ, &CParentView::OnPipeRead)
	ON_COMMAND(IDM_PIPE_WRITE, &CParentView::OnPipeWrite)
	ON_COMMAND(IDM_NAMEPIPE_CREATE, &CParentView::OnNamepipeCreate)
	ON_COMMAND(IDM_NAMEPIPE_READ, &CParentView::OnNamepipeRead)
	ON_COMMAND(IDM_NAMEPIPE_WRITE, &CParentView::OnNamepipeWrite)
END_MESSAGE_MAP()

// CParentView construction/destruction

CParentView::CParentView()
{
	// TODO: add construction code here
	hRead = NULL;
	hWrite = NULL;

	hPipe = NULL;
}

CParentView::~CParentView()
{
	if (hRead) {
		CloseHandle(hRead);
	}
	if (hWrite) {
		CloseHandle(hWrite);
	}
	if (hPipe) {
		CloseHandle(hPipe);
	}
}

BOOL CParentView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CParentView drawing

void CParentView::OnDraw(CDC* /*pDC*/)
{
	CParentDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CParentView printing

BOOL CParentView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CParentView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CParentView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CParentView diagnostics

#ifdef _DEBUG
void CParentView::AssertValid() const
{
	CView::AssertValid();
}

void CParentView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CParentDoc* CParentView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CParentDoc)));
	return (CParentDoc*)m_pDocument;
}
#endif //_DEBUG


// CParentView message handlers


void CParentView::OnPipeCreate()
{
	// TODO: Add your command handler code here
	SECURITY_ATTRIBUTES sa;
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = NULL;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	if (!CreatePipe(&hRead, &hWrite, &sa, 0)) {
		MessageBox(_T("创建匿名管道失败！"));
		return;
	}
	STARTUPINFO sui;
	PROCESS_INFORMATION pi;
	ZeroMemory(&sui, sizeof(STARTUPINFO));
	sui.cb = sizeof(STARTUPINFO);
	sui.dwFlags = STARTF_USESTDHANDLES;
	sui.hStdInput = hRead;
	sui.hStdOutput = hWrite;
	sui.hStdError = GetStdHandle(STD_ERROR_HANDLE);

	if (!CreateProcess(_T("..\\Debug\\Clipboard.exe"), NULL, NULL, NULL, TRUE, 0, NULL, NULL, &sui, &pi)) {
		CloseHandle(hRead);
		CloseHandle(hWrite);
		hRead = NULL;
		hWrite = NULL;
		MessageBox(_T("创建子进程失败!"));
		return;
	}
	else {
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
}


void CParentView::OnPipeRead()
{
	// TODO: Add your command handler code here
	char buf[100];
	DWORD dwRead;
	if (!ReadFile(hRead, buf, 100, &dwRead, NULL)) {
		MessageBox(_T("读取数据失败！"));
		return;
	}
	USES_CONVERSION;
	MessageBox(A2T(buf));
}


void CParentView::OnPipeWrite()
{
	// TODO: Add your command handler code here
	char buf[100] = "hasduhasduiasiduauidauis";
	DWORD dwWrite;
	if (!WriteFile(hWrite, buf, strlen(buf) + 1, &dwWrite, NULL)) {
		MessageBox(_T("写入数据失败！"));
		return;
	}
}


void CParentView::OnNamepipeCreate()
{
	// TODO: Add your command handler code here
	hPipe = CreateNamedPipe(_T("\\\\.\\pipe\\MyPipe"), PIPE_ACCESS_DUPLEX|FILE_FLAG_OVERLAPPED,
		0,2,1024,1024,0,NULL);
	if (INVALID_HANDLE_VALUE == hPipe) {
		MessageBox(_T("创建命名管道失败!"));
		hPipe = NULL;
		return;
	}

	HANDLE hEvent;
	hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (!hEvent) {
		MessageBox(_T("创建事件对象失败！"));
		CloseHandle(hPipe);
		hPipe = NULL;
		return;
	}
	OVERLAPPED ovlap;
	ZeroMemory(&ovlap, sizeof(OVERLAPPED));
	ovlap.hEvent = hEvent;

	if (ConnectNamedPipe(hPipe, &ovlap)==FALSE) {
		if (ERROR_IO_PENDING != GetLastError()) {
			MessageBox(_T("等待客户端连接失败！"));
			CloseHandle(hPipe);
			CloseHandle(hEvent);
			hPipe = NULL;
			return;
		}
	}
	if (WAIT_FAILED == MsgWaitForMultipleObjects(1,&hEvent,FALSE,INFINITE, QS_ALLINPUT)) {
		MessageBox(_T("等待对象失败！"));
		CloseHandle(hPipe);
		CloseHandle(hEvent);
		hPipe = NULL;
		return;
	}
	CloseHandle(hEvent);

}


void CParentView::OnNamepipeRead()
{
	// TODO: Add your command handler code here
	char buf[100] = {0};
	DWORD dwRead;
	if (!ReadFile(hPipe, buf, 100, &dwRead, NULL)) {
		MessageBox(_T("读取数据失败！"));
		return;
	}
	buf[dwRead] = 0;
	USES_CONVERSION;
	MessageBox(A2T(buf));
}


void CParentView::OnNamepipeWrite()
{
	// TODO: Add your command handler code here
	char bufs[100] = "dasfdsafdsfds";
	DWORD dwWrite;

	if (!WriteFile(hPipe, bufs, strlen(bufs), &dwWrite, NULL)) {
		MessageBox(_T("写入数据失败！"));
		return;
	}
}

