// AnhuiDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Additions.h"
#include "AnhuiDlg.h"
#include "afxdialogex.h"


// CAnhuiDlg dialog

IMPLEMENT_DYNAMIC(CAnhuiDlg, CDialogEx)

CAnhuiDlg::CAnhuiDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ANHUI_DIALOG, pParent)
{

}

CAnhuiDlg::~CAnhuiDlg()
{
}

void CAnhuiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_ANHUI, m_ctrPic);
}


BEGIN_MESSAGE_MAP(CAnhuiDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAnhuiDlg::OnBnClickedOk)
	ON_STN_CLICKED(IDC_STATIC_ANHUI, &CAnhuiDlg::OnStnClickedStaticAnhui)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CAnhuiDlg message handlers


void CAnhuiDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


BOOL CAnhuiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	// TODO: 在此添加额外的初始化代码

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CAnhuiDlg::OnStnClickedStaticAnhui()
{
	// TODO: Add your control notification handler code here
}


void CAnhuiDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CDialogEx::OnPaint() for painting message
		CBitmap bitmap;
		//加载指定位图资源 Bmp图片ID  
		bitmap.LoadBitmap(IDB_BITMAP1);
		//获取对话框上的句柄 图片控件ID  
		CStatic *p = (CStatic *)GetDlgItem(IDC_STATIC_ANHUI);
		//设置静态控件窗口风格为位图居中显示   
		p->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
		//将图片设置到Picture控件上  
		p->SetBitmap(bitmap);

		BITMAP bmpInfo;
		bitmap.GetBitmap(&bmpInfo);
		CDC dcMemory;
		CDC* pDC = GetDlgItem(IDC_STATIC_ANHUI)->GetDC();
		dcMemory.CreateCompatibleDC(pDC);
		CBitmap* pOldBitmap = dcMemory.SelectObject(&bitmap);
		CRect rect;
		m_ctrPic.GetClientRect(&rect);
		int nX = rect.left + (rect.Width() - bmpInfo.bmWidth) / 2;
		int nY = rect.top + (rect.Height() - bmpInfo.bmHeight) / 2;
		//pDC->BitBlt(0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, &dcMemory, 0, 0, SRCCOPY);  
		pDC->SetStretchBltMode(COLORONCOLOR);
		pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMemory, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);
		dcMemory.SelectObject(pOldBitmap);
		ReleaseDC(pDC);
}
