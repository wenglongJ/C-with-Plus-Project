#pragma once


// CSummandPage dialog

class CSummandPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CSummandPage)

public:
	CSummandPage();
	virtual ~CSummandPage();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SUMMAND_PAGE};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
};
