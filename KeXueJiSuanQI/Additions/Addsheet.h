#pragma once

#include "SummandPage.h"
#include "AddendPage.h"
#include "AddPage.h"

// CAddsheet

class CAddsheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CAddsheet)

public:
	CAddsheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CAddsheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CAddsheet();

protected:
	DECLARE_MESSAGE_MAP()
private:
	CSummandPage    m_summandPage;
	CAddendPage     m_addendPage;
	CAddPage        m_addPage;
};


