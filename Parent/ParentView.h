
// ParentView.h : interface of the CParentView class
//

#pragma once


class CParentView : public CView
{
protected: // create from serialization only
	CParentView();
	DECLARE_DYNCREATE(CParentView)

// Attributes
public:
	CParentDoc* GetDocument() const;

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
	virtual ~CParentView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPipeCreate();
	afx_msg void OnPipeRead();
	afx_msg void OnPipeWrite();
private:
	HANDLE hWrite;
	HANDLE hRead;

	HANDLE hPipe;
	DWORD WriteNum;
	DWORD ReadNum;
public:
	afx_msg void OnNamepipeCreate();
	afx_msg void OnNamepipeRead();
	afx_msg void OnNamepipeWrite();
};

#ifndef _DEBUG  // debug version in ParentView.cpp
inline CParentDoc* CParentView::GetDocument() const
   { return reinterpret_cast<CParentDoc*>(m_pDocument); }
#endif

