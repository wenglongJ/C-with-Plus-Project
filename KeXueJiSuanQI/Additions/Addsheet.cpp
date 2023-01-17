// Addsheet.cpp : implementation file
//

#include "stdafx.h"
#include "Additions.h"
#include "Addsheet.h"


// CAddsheet

IMPLEMENT_DYNAMIC(CAddsheet, CPropertySheet)

CAddsheet::CAddsheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	// 添加三个属性页到属性表  
	AddPage(&m_addPage);
	AddPage(&m_summandPage);
	
	AddPage(&m_addendPage);
}

CAddsheet::CAddsheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	// 添加三个属性页到属性表  
	AddPage(&m_addPage);
	AddPage(&m_summandPage);
	
	AddPage(&m_addendPage);
	Create(this, WS_CHILD | WS_VISIBLE, 0);

}

CAddsheet::~CAddsheet()
{
}


BEGIN_MESSAGE_MAP(CAddsheet, CPropertySheet)
END_MESSAGE_MAP()


// CAddsheet message handlers
