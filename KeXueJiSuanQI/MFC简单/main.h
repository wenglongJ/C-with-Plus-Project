#pragma once
#ifndef _QTNINSIDE_H_
#define _QTNINSIDE_H_

class CMFCApp :public CWinApp
{
public:
	virtual BOOL InitInstance();
};

class CMFCFrmWnd :public CFrameWnd
{
public:
	CMFCFrmWnd();
	int m_nTextX;
	int m_nTextY;
	CFont m_newFont;
	CFont *m_pOldFont;
protected:
	afx_msg void OnLButtonDblClk(UINT uFlag, CPoint pt);
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
};
#endif // !_QTNINSIDE_H_
