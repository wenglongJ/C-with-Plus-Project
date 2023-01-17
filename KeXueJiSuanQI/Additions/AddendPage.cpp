// AddendPage.cpp : implementation file
//

#include "stdafx.h"
#include "Additions.h"
#include "AddendPage.h"
#include "afxdialogex.h"


// CAddendPage dialog

IMPLEMENT_DYNAMIC(CAddendPage, CPropertyPage)

CAddendPage::CAddendPage()
	: CPropertyPage(IDD_ADDEND_PAGE)
{

}

CAddendPage::~CAddendPage()
{
}

void CAddendPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAddendPage, CPropertyPage)
END_MESSAGE_MAP()


// CAddendPage message handlers


BOOL CAddendPage::OnSetActive()
{
	// TODO: Add your specialized code here and/or call the base class
	// 获得父窗口，即属性表CPropertySheet类   
	CPropertySheet* psheet = (CPropertySheet*)GetParent();
	//设置属性表只有“完成”按钮   
	psheet->SetFinishText(_T("完成"));
	return CPropertyPage::OnSetActive();
}


BOOL CAddendPage::OnWizardFinish()
{
	// TODO: Add your specialized code here and/or call the base class
	
		// TODO: Add your specialized code here and/or call the base class
		MessageBox(_T("使用说明向导已阅读完！"));

		return CPropertyPage::OnWizardFinish();

	return CPropertyPage::OnWizardFinish();
}
