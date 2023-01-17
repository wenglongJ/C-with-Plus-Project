#pragma once


// COkDlg dialog

class COkDlg : public CDialogEx
{
	DECLARE_DYNAMIC(COkDlg)

public:
	COkDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~COkDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_OK };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
};
