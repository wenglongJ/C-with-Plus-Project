#pragma once


// CCancelDlg dialog

class CCancelDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCancelDlg)

public:
	CCancelDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCancelDlg();
	

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CANCEL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
};
