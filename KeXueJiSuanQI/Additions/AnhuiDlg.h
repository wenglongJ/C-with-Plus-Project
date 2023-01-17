#pragma once
#include "afxwin.h"


// CAnhuiDlg dialog

class CAnhuiDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAnhuiDlg)

public:
	CAnhuiDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAnhuiDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ANHUI_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnStnClickedStaticAnhui();
	CStatic m_ctrPic;
	afx_msg void OnPaint();
};
