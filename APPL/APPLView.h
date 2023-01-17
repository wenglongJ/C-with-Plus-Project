
// APPLView.h : interface of the CAPPLView class
//

#pragma once

class CAPPLView : public CView
{
protected: // create from serialization only
	CAPPLView();
	DECLARE_DYNCREATE(CAPPLView)

// Attributes
public:
	CAPPLDoc* GetDocument() const;

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
	virtual ~CAPPLView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

private:

public:
	afx_msg void OnFileWrite();
	afx_msg void OnFileRead();

public:
	HANDLE hPipe;
	afx_msg void OnNamepipeConnectpipe();
	afx_msg void OnNamepipeReadpipe();
	afx_msg void OnNamepipeWritepipe();
};

#ifndef _DEBUG  // debug version in APPLView.cpp
inline CAPPLDoc* CAPPLView::GetDocument() const
   { return reinterpret_cast<CAPPLDoc*>(m_pDocument); }
#endif

