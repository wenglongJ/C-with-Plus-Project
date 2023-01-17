#pragma once


// CSecondDlg dialog

class CSecondDlg : public CPropertyPage
{
	DECLARE_DYNAMIC(CSecondDlg)

public:
	CSecondDlg();
	virtual ~CSecondDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Little };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
