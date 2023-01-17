// OkDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OkDlg.h"
#include "resource.h"
#include "afxdialogex.h"


// COkDlg dialog

IMPLEMENT_DYNAMIC(COkDlg, CDialogEx)

COkDlg::COkDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_OK, pParent)
{

}

COkDlg::~COkDlg()
{
}

void COkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(COkDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// COkDlg message handlers


BOOL COkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	//����ͼƬ
	CBitmap bmpBackground;
	bmpBackground.LoadBitmap(IDB_BITMAP1); //IDB_BITMAP�����Լ���ͼ��Ӧ��ID
	
	BITMAP bitmap;
	bmpBackground.GetBitmap(&bitmap);

	//�ı�����СΪͼƬ��С
	SetWindowPos(NULL, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SWP_NOZORDER | SWP_NOMOVE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void COkDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CDialogEx::OnPaint() for painting messages
	//��ý����С
	CRect   rectDlg;
	GetClientRect(&rectDlg);
	
	//��������
	CDC   dcMem;
	dcMem.CreateCompatibleDC(&dc);

	//����ͼƬ
	CBitmap   bmpBackground;
	bmpBackground.LoadBitmap(IDB_BITMAP1);   //IDB_BITMAP1�Ǳ���λͼ��Ӧ��ID 

	BITMAP   bitmap;
	bmpBackground.GetBitmap(&bitmap);

	CBitmap   *pbmpOld = dcMem.SelectObject(&bmpBackground);
	
	//ͼƬ�����Ի�����
	dc.StretchBlt(0, 0, rectDlg.Width(), rectDlg.Height(), &dcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
}
