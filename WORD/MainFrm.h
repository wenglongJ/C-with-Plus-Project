
// MainFrm.h : interface of the CMainFrame class
//

#pragma once
#include "afxext.h"
#include "afxcmn.h"
#define UM_PROGRESS WM_USER+1
class CMainFrame : public CFrameWnd
{

protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

	// Attributes
public:

	// Operations
public:

	// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	// Implementation
public:
	CBitmap m_bitmap;
	HICON m_hIcons[2];
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnProgress(WPARAM xParam, LPARAM lparam);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnUpdateEditCut(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFileNew(CCmdUI *pCmdUI);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnTest();
	CToolBar m_newToolBar;
	afx_msg void OnViewbarNewtool();
	afx_msg void OnUpdateViewbarNewtool(CCmdUI *pCmdUI);
	CProgressCtrl m_progress;
};


