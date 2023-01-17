#pragma once


// CfirstDlg dialog

class CfirstDlg : public CPropertyPage
{
	DECLARE_DYNAMIC(CfirstDlg)

public:
	CfirstDlg();
	virtual ~CfirstDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
};
