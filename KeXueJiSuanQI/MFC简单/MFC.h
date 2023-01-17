#pragma once
#include <iostream.h>
using namespace std;
 class CObject
 {
  public:
       CObject::CObject() { cout << "CObject Constructor \n"; }
	      CObject::~CObject() { cout << "CObject Destructor \n"; }
	  };
 class CCmdTarget : public CObject
  {
  public:
  CCmdTarget::CCmdTarget() { cout << "CCmdTarget Constructor \n"; }
  CCmdTarget::~CCmdTarget() { cout << "CCmdTarget Destructor\n"; }
 };
 class CWinThread : public CCmdTarget
{
 public:
	 CWinThread::CWinThread() { cout << "CWinThread Constructor\n"; }
	   CWinThread::~CWinThread() { cout << "CWinThread Destructor\n"; }
		 };
class CWinApp : public CWinThread
 {
 public:
	      CWinApp* m_pCurrentWinApp;
	  public:
	      CWinApp::CWinApp() {
				m_pCurrentWinApp = this;
				cout << "CWinApp Constructor \n";
			}
      CWinApp::~CWinApp() { cout << "CWinApp Destructor \n"; }
  };
 class CDocument : public CCmdTarget
 {
  public:
    CDocument::CDocument() { cout << "CDocument Constructor \n"; }
       CDocument::~CDocument() { cout << "CDocument Destructor \n"; }
	 };
class CWnd : public CCmdTarget
 {
  public:
		       CWnd::CWnd() { cout << "CWnd Constructor \n"; }
		       CWnd::~CWnd() { cout << "CWnd Destructor \n"; }
		 };
 class CFrameWnd : public CWnd
 {
 public:
	      CFrameWnd::CFrameWnd() { cout << "CFrameWnd Constructor \n"; }
    CFrameWnd::~CFrameWnd() { cout << "CFrameWnd Destructor \n"; }
	 };
  class CView : public CWnd
  {
  public:
    CView::CView() { cout << "CView Constructor \n"; }
      CView::~CView() { cout << "CView Destructor \n"; }
 };
 // global function
  CWinApp* AfxGetApp();