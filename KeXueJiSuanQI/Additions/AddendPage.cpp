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
	// ��ø����ڣ������Ա�CPropertySheet��   
	CPropertySheet* psheet = (CPropertySheet*)GetParent();
	//�������Ա�ֻ�С���ɡ���ť   
	psheet->SetFinishText(_T("���"));
	return CPropertyPage::OnSetActive();
}


BOOL CAddendPage::OnWizardFinish()
{
	// TODO: Add your specialized code here and/or call the base class
	
		// TODO: Add your specialized code here and/or call the base class
		MessageBox(_T("ʹ��˵�������Ķ��꣡"));

		return CPropertyPage::OnWizardFinish();

	return CPropertyPage::OnWizardFinish();
}
