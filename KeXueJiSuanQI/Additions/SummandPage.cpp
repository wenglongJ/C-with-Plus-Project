// SummandPage.cpp : implementation file
//

#include "stdafx.h"
#include "Additions.h"
#include "SummandPage.h"
#include "afxdialogex.h"


// CSummandPage dialog

IMPLEMENT_DYNAMIC(CSummandPage, CPropertyPage)

CSummandPage::CSummandPage()               //����һ��DIADLG����
	: CPropertyPage(IDD_SUMMAND_PAGE)
{

}

CSummandPage::~CSummandPage()
{
}

void CSummandPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSummandPage, CPropertyPage)
END_MESSAGE_MAP()


// CSummandPage message handlers


BOOL CSummandPage::OnSetActive()
{
	// TODO: Add your specialized code here and/or call the base class
	CPropertySheet* psheet = (CPropertySheet*)GetParent();
	// �������Ա�ֻ�С���һ������ť   
	psheet->SetWizardButtons(PSWIZB_NEXT);
	return CPropertyPage::OnSetActive();
}
