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
	// TODO: �ڴ���Ӷ���ĳ�ʼ������

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
		//����ָ��λͼ��Դ BmpͼƬID  
		bitmap.LoadBitmap(IDB_BITMAP1);
		//��ȡ�Ի����ϵľ�� ͼƬ�ؼ�ID  
		CStatic *p = (CStatic *)GetDlgItem(IDC_STATIC_ANHUI);
		//���þ�̬�ؼ����ڷ��Ϊλͼ������ʾ   
		p->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
		//��ͼƬ���õ�Picture�ؼ���  
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
