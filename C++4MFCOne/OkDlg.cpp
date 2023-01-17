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

	//加载图片
	CBitmap bmpBackground;
	bmpBackground.LoadBitmap(IDB_BITMAP1); //IDB_BITMAP是你自己的图对应的ID
	
	BITMAP bitmap;
	bmpBackground.GetBitmap(&bitmap);

	//改变界面大小为图片大小
	SetWindowPos(NULL, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SWP_NOZORDER | SWP_NOMOVE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void COkDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CDialogEx::OnPaint() for painting messages
	//获得界面大小
	CRect   rectDlg;
	GetClientRect(&rectDlg);
	
	//创建画笔
	CDC   dcMem;
	dcMem.CreateCompatibleDC(&dc);

	//加载图片
	CBitmap   bmpBackground;
	bmpBackground.LoadBitmap(IDB_BITMAP1);   //IDB_BITMAP1是背景位图对应的ID 

	BITMAP   bitmap;
	bmpBackground.GetBitmap(&bitmap);

	CBitmap   *pbmpOld = dcMem.SelectObject(&bmpBackground);
	
	//图片填充入对话框中
	dc.StretchBlt(0, 0, rectDlg.Width(), rectDlg.Height(), &dcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
}
