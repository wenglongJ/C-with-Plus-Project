
// KeXueJiSuanQIDlg.h : header file
//

#pragma once
#include"CfirstDlg.h"
#include "SecondDlg.h"
#include "afxwin.h"

// CKeXueJiSuanQIDlg dialog
class CKeXueJiSuanQIDlg : public CDialogEx
{
// Construction
public:
	CKeXueJiSuanQIDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KEXUEJISUANQI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void On32771();
	afx_msg void OnBnClickedButton1();
	CfirstDlg m_page1;
	CSecondDlg m_page2;
	CPropertySheet m_Sheet;
	CStatic m_pc;
};
