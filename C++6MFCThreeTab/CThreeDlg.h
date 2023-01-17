
// CthreeDlg.h : header file
//

#pragma once
#include"TableCtrl.h"

// CthreeDlg dialog
class CThreeDlg : public CDialogEx
{
// Construction
public:
	CThreeDlg(CWnd* pParent = NULL);	// standard constructor
	~CThreeDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CMFCTHREE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedBtnCreateTable();
	
private:
	CTableCtrl *m_pTabList;
	int m_nRows;
	int m_nColumns;
};
