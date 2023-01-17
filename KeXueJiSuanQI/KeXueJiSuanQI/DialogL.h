#pragma once


// CDialogL dialog

class CDialogL : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogL)

public:
	CDialogL(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogL();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Little };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
