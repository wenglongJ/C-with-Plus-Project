#pragma once


// CKexueDlg dialog

class CKexueDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CKexueDlg)

public:
	CKexueDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CKexueDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KEXUE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
