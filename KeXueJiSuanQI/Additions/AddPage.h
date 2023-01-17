#pragma once


// AddPage dialog

class CAddPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CAddPage)

public:
	CAddPage();
	virtual ~CAddPage();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_PAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
};
