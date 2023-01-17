// CfirstDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KeXueJiSuanQI.h"
#include "CfirstDlg.h"
#include "afxdialogex.h"


// CfirstDlg dialog

IMPLEMENT_DYNAMIC(CfirstDlg, CPropertyPage)

CfirstDlg::CfirstDlg()
	: CPropertyPage(IDD_DIALOG1)
{

}

CfirstDlg::~CfirstDlg()
{
}

void CfirstDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CfirstDlg, CPropertyPage)
END_MESSAGE_MAP()


// CfirstDlg message handlers


BOOL CfirstDlg::OnSetActive()
{
	// TODO: Add your specialized code here and/or call the base class
	CPropertySheet* psheet = (CPropertySheet*)GetParent();
	// 设置属性表只有“下一步”按钮   
	psheet->SetWizardButtons(PSWIZB_NEXT);
	return CPropertyPage::OnSetActive();
}
