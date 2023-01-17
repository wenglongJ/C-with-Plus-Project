// CancelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CancelDlg.h"
#include "resource.h"
#include "afxdialogex.h"


// CCancelDlg dialog

IMPLEMENT_DYNAMIC(CCancelDlg, CDialogEx)

CCancelDlg::CCancelDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_CANCEL, pParent)
{

}

CCancelDlg::~CCancelDlg()
{

}

void CCancelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCancelDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CCancelDlg message handlers

BOOL CCancelDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CCancelDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CDialogEx::OnPaint() for painting messages
	//��ÿؼ���С
	CRect   rectDlg;
	GetClientRect(&rectDlg);

	//��������
	CDC   dcMem;
	dcMem.CreateCompatibleDC(&dc);

	//����ͼƬ
	CBitmap   bmpBackground;
	bmpBackground.LoadBitmap(IDB_BITMAP2);   //IDB_BITMAP2�Ǳ���λͼ��Ӧ��ID 

	BITMAP   bitmap;
	bmpBackground.GetBitmap(&bitmap);

	CBitmap  *pbmpOld = dcMem.SelectObject(&bmpBackground);

	//Ϊdialog���ͼƬ
	dc.StretchBlt(0, 0, rectDlg.Width(), rectDlg.Height(), &dcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
}





