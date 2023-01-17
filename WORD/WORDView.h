
// WORDView.h : interface of the CWORDView class
//

#pragma once
#include "afxcoll.h"


class CWORDView : public CView
{
protected: // create from serialization only
	CWORDView();
	DECLARE_DYNCREATE(CWORDView)

// Attributes
public:
	CWORDDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CWORDView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CBitmap bitmap;
	CString m_strLine;
	CPoint m_ptOrigin;
	int m_nIndex;
	CMenu m_menu;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	CStringArray m_strArray;
};

#ifndef _DEBUG  // debug version in WORDView.cpp
inline CWORDDoc* CWORDView::GetDocument() const
   { return reinterpret_cast<CWORDDoc*>(m_pDocument); }
#endif

