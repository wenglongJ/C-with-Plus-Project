#pragma once
#include "afxwin.h"

class CTableCtrl : public CStatic
{
public:
	CTableCtrl(int m = 3, int n = 3);
	~CTableCtrl();

	void ResetTable(int m, int n);

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

private:
	int m_nRows;
	int m_nColumns;
	BOOL m_bRedraw;
	CDC m_dcMem;
	CPen *m_pPenOld;
	CBitmap *m_pBmpOld;
};

