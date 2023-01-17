
// CMFConeDlg.h : header file
//

#pragma once
#include "CancelDlg.h"

// CMFConeDlg dialog
class CMFConeDlg : public CDialogEx
{
// Construction
public:
	CMFConeDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CMFConeDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CMFCONE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnOK();
	virtual void OnCancel();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedBtnOk();
	afx_msg void OnBnClickedBtnCancel();
	afx_msg HCURSOR OnQueryDragIcon();

private:
	CCancelDlg *m_pDlgCancel;
};
