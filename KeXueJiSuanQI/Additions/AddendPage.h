#pragma once


// CAddendPage dialog

class CAddendPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CAddendPage)

public:
	CAddendPage();
	virtual ~CAddendPage();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADDEND_PAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnWizardFinish();
};
