
// AdditionsDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Additions.h"
#include "AdditionsDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAdditionsDlg �Ի���



CAdditionsDlg::CAdditionsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ADDITIONS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nData1 = 0;
	m_nData2 = 0;
	m_nData3 = 0;

	m_nTextX = 260;
	m_nTextY = 10;
	m_pOldFont = NULL;

	memset(m_nzValues, 0, sizeof(int)*POINT_COUNT);
}

void CAdditionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RJ_CHECK, m_com);
	DDX_Control(pDX, IDC_WL_CHECK, m_sofware);
	DDX_Control(pDX, IDC_EY_CHECK, m_english);
	DDX_Control(pDX, IDC_RY_CHECK, m_japanese);
	DDX_Control(pDX, IDC_TM_CHECK, m_civil);
	DDX_Control(pDX, IDC_ZJ_CHECK, m_cost);
	DDX_Control(pDX, IDC_WEB_LIST, m_list);
	DDX_Control(pDX, IDC_WEB_COMBO, m_combox);
	DDX_Control(pDX, IDC_HSCROLL_EDIT, m_horiScrollbar);
	DDX_Control(pDX, IDC_HORI_SCROLLBAR, m_horiScrollbars);
	DDX_Control(pDX, IDC_JIAODA_LIST, m_jiaodaList);
	DDX_Control(pDX, IDC_WEB_TREE, m_tree);
	DDX_Control(pDX, IDC_TAB_SEE, m_tab);
	DDX_Control(pDX, IDC_WAVE_DRAW, m_picDraw);
	DDX_Control(pDX, IDC_COLOR_SHOW_STATIC, m_picColor);
	DDX_Control(pDX, IDC_COMBO_SOMBOY, m_somboy);
	DDX_Text(pDX, IDC_EDIT_FIRST, m_datafirst);
	DDX_Text(pDX, IDC_EDIT_SECOND, m_datasecond);
	DDX_Text(pDX, IDC_EDIT_RESULT, m_dataresult);
	DDX_Control(pDX, IDC_PROGRESS_SET, m_set);
}

BEGIN_MESSAGE_MAP(CAdditionsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_INSTRUCT_BUTTON, &CAdditionsDlg::OnBnClickedInstructButton)
	ON_BN_CLICKED(IDC_OPEN_BUTTON, &CAdditionsDlg::OnBnClickedOpenButton)
	ON_BN_CLICKED(IDC_SAVE_BUTTON, &CAdditionsDlg::OnBnClickedSaveButton)
	ON_BN_CLICKED(IDC_FONT_BUTTON, &CAdditionsDlg::OnBnClickedFontButton)
	ON_BN_CLICKED(IDC_COLOR_BUTTON, &CAdditionsDlg::OnBnClickedColorButton)
	ON_BN_CLICKED(IDC_COM_RADIO, &CAdditionsDlg::OnBnClickedComRadio)
	ON_BN_CLICKED(IDC_BUI_RADIO, &CAdditionsDlg::OnBnClickedBuiRadio)
	ON_BN_CLICKED(IDC_LAN_RADIO, &CAdditionsDlg::OnBnClickedLanRadio)
	ON_BN_CLICKED(IDC_SURE_BUTTON, &CAdditionsDlg::OnBnClickedSureButton)
	ON_LBN_SELCHANGE(IDC_WEB_LIST, &CAdditionsDlg::OnLbnSelchangeWebList)
	ON_CBN_SELCHANGE(IDC_WEB_COMBO, &CAdditionsDlg::OnCbnSelchangeWebCombo)
	ON_WM_HSCROLL()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_JIAODA_LIST, &CAdditionsDlg::OnLvnItemchangedJiaodaList)
	ON_NOTIFY(TVN_SELCHANGED, IDC_WEB_TREE, &CAdditionsDlg::OnTvnSelchangedWebTree)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_SEE, &CAdditionsDlg::OnTcnSelchangeTabSee)
	ON_BN_CLICKED(IDC_BUTTON_TABSURE, &CAdditionsDlg::OnBnClickedButtonTabsure)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_COUNT, &CAdditionsDlg::OnBnClickedButtonCount)
	ON_BN_CLICKED(IDC_BUTTON_NEW, &CAdditionsDlg::OnBnClickedButtonNew)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CAdditionsDlg ��Ϣ�������

BOOL CAdditionsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	//�б�ؼ���ʼ��
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_list.AddString(_T("�廪��ѧ"));
	m_list.AddString(_T("������ѧ"));
	m_list.AddString(_T("�Ϻ���ͨ��ѧ"));
	m_list.AddString(_T("������ͨ��ѧ"));
	m_list.AddString(_T("���Ͻ�ͨ��ѧ"));
	m_list.AddString(_T("������ͨ��ѧ"));


	m_combox.AddString(_T("�Ϻ���ͨ��ѧ"));
	m_combox.AddString(_T("������ͨ��ѧ"));
	m_combox.AddString(_T("���Ͻ�ͨ��ѧ"));
	m_combox.AddString(_T("������ͨ��ѧ"));

	//��������ʼ��
	CScrollBar *ptr = new CScrollBar;
	ptr->Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,
		CRect(10, 10, 100, 100), this, 1);

	m_horiScrollbars.SetScrollRange(1, 100);
	// ����ˮƽ�������ĳ�ʼλ��Ϊ20   
	m_horiScrollbars.SetScrollPos(20);
	// �ڱ༭������ʾ20   
	SetDlgItemInt(IDC_HSCROLL_EDIT, 20);

	m_set.SetRange(1, 100);
	m_set.SetPos(20);
	SetTimer(6, 100, 0);
	//���ؼ���ʼ��
	CRect rect;
	m_jiaodaList.GetClientRect(&rect);

	m_jiaodaList.SetExtendedStyle(m_jiaodaList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_jiaodaList.InsertColumn(0, _T("��ѧ����"), LVCFMT_CENTER, rect.Width() / 2, 0);
	m_jiaodaList.InsertColumn(2, _T("���ڵ�"), LVCFMT_CENTER, rect.Width() / 2, 1);
	m_jiaodaList.InsertItem(0, _T("�Ϻ���ͨ��ѧ"));
	m_jiaodaList.SetItemText(0, 1, _T("�Ϻ�"));
	m_jiaodaList.InsertItem(1, _T("������ͨ��ѧ"));
	m_jiaodaList.SetItemText(1, 1, _T("����"));
	m_jiaodaList.InsertItem(2, _T("���Ͻ�ͨ��ѧ"));
	m_jiaodaList.SetItemText(2, 1, _T("�ɶ�"));
	m_jiaodaList.InsertItem(3, _T("������ͨ��ѧ"));
	m_jiaodaList.SetItemText(3, 1, _T("����"));
	m_jiaodaList.InsertItem(4, _T("����ͨ��ѧ"));
	m_jiaodaList.SetItemText(4, 1, _T("̨��"));

	//���ͳ�ʼ��
	HICON hIcon[3];      // ͼ��������   
	HTREEITEM hRoot;     // ���ĸ��ڵ�ľ��   
	HTREEITEM hCataItem; // �ɱ�ʾ��һ����ڵ�ľ��   
	HTREEITEM hArtItem;  // �ɱ�ʾ��һ���½ڵ�ľ��   

						 // ��������ͼ�꣬�������ǵľ�����浽����   
	hIcon[0] = theApp.LoadIcon(IDI_ICON1);
	hIcon[1] = theApp.LoadIcon(IDI_ICON2);
	hIcon[2] = theApp.LoadIcon(IDI_ICON3);

	// ����ͼ������CImageList����   
	m_imageList.Create(32, 32, ILC_COLOR32, 3, 3);
	// ������ͼ����ӵ�ͼ������   
	for (int i = 0; i<3; i++)
	{
		m_imageList.Add(hIcon[i]);
	}

	// Ϊ���οؼ�����ͼ������   
	m_tree.SetImageList(&m_imageList, TVSIL_NORMAL);

	// ������ڵ�   
	hRoot = m_tree.InsertItem(_T("��������ţ"), 0, 0);
	// �ڸ��ڵ��²����ӽڵ�   
	hCataItem = m_tree.InsertItem(_T("�ٶ�"), 1, 1, hRoot, TVI_LAST);
	// Ϊ���ٶȡ��ڵ���Ӹ��ӵı�����ݣ�����껮���ýڵ�ʱ��ʾ   
	m_tree.SetItemData(hCataItem, 1);
	// �ڡ��ٶȡ��ڵ��²����ӽڵ�   
	hArtItem = m_tree.InsertItem(_T("�ֻ��ٶ�"), 2, 2, hCataItem, TVI_LAST);
	// Ϊ���ֻ��ٶȡ��ڵ���Ӹ��ӵı�����ݣ�����껮���ýڵ�ʱ��ʾ   
	m_tree.SetItemData(hArtItem, 2);
	// �ڡ��ٶȡ��ڵ��²�����һ�ӽڵ�   
	hArtItem = m_tree.InsertItem(_T("�ٶȵ�ͼ"), 2, 2, hCataItem, TVI_LAST);
	// Ϊ���ٶȵ�ͼ���ڵ���Ӹ��ӵı�����ݣ�����껮���ýڵ�ʱ��ʾ   
	m_tree.SetItemData(hArtItem, 3);
	// �ڸ��ڵ��²���ڶ����ӽڵ�   
	hCataItem = m_tree.InsertItem(_T("��Ѷ"), 1, 1, hRoot, TVI_LAST);
	// Ϊ����Ѷ���ڵ���Ӹ��ӵı�����ݣ�����껮���ýڵ�ʱ��ʾ   
	m_tree.SetItemData(hCataItem, 4);
	// �ڡ���Ѷ���ڵ��²����ӽڵ�   
	hArtItem = m_tree.InsertItem(_T("QQ"), 2, 2, hCataItem, TVI_LAST);
	// Ϊ��QQ���ڵ���Ӹ��ӵı�����ݣ�����껮���ýڵ�ʱ��ʾ   
	m_tree.SetItemData(hArtItem, 5);
	// �ڡ���Ѷ���ڵ��²�����һ�ӽڵ�   
	hArtItem = m_tree.InsertItem(_T("΢��"), 2, 2, hCataItem, TVI_LAST);
	// Ϊ��΢�š��ڵ���Ӹ��ӵı�����ݣ�����껮���ýڵ�ʱ��ʾ   
	m_tree.SetItemData(hArtItem, 6);
	// �ڸ��ڵ��²���������ӽڵ�   
	hCataItem = m_tree.InsertItem(_T("����Ͱ�"), 1, 1, hRoot, TVI_LAST);
	// Ϊ������Ͱ͡��ڵ���Ӹ��ӵı�����ݣ�����껮���ýڵ�ʱ��ʾ   
	m_tree.SetItemData(hCataItem, 7);
	// �ڡ�����Ͱ͡��ڵ��²����ӽڵ�   
	hArtItem = m_tree.InsertItem(_T("�Ա�"), 2, 2, hCataItem, TVI_LAST);
	// Ϊ���Ա����ڵ���Ӹ��ӵı�����ݣ�����껮���ýڵ�ʱ��ʾ   
	m_tree.SetItemData(hArtItem, 8);
	// �ڡ�����Ͱ͡��ڵ��²�����һ�ӽڵ�   
	hArtItem = m_tree.InsertItem(_T("��è"), 2, 2, hCataItem, TVI_LAST);
	// Ϊ����è���ڵ���Ӹ��ӵı�����ݣ�����껮���ýڵ�ʱ��ʾ   
	m_tree.SetItemData(hArtItem, 9);
	// �ڸ��ڵ��²�����ĸ��ӽڵ�   
	hCataItem = m_tree.InsertItem(_T("���Ͻ���"), 1, 1, hRoot, TVI_LAST);
	// Ϊ�����Ͻ��ڡ��ڵ���Ӹ��ӵı�����ݣ�����껮���ýڵ�ʱ��ʾ   
	m_tree.SetItemData(hCataItem, 10);
	// �ڡ����Ͻ��ڡ��ڵ��²����ӽڵ�   
	hArtItem = m_tree.InsertItem(_T("��"), 2, 2, hCataItem, TVI_LAST);
	// Ϊ�������ڵ���Ӹ��ӵı�����ݣ�����껮���ýڵ�ʱ��ʾ   
	m_tree.SetItemData(hArtItem, 11);
	// �ڡ����Ͻ��ڡ��ڵ��²�����һ�ӽڵ�   
	hArtItem = m_tree.InsertItem(_T("֧����"), 2, 2, hCataItem, TVI_LAST);
	// Ϊ��֧�������ڵ���Ӹ��ӵı�����ݣ�����껮���ýڵ�ʱ��ʾ   
	m_tree.SetItemData(hArtItem, 12);

	//tab�ؼ���ʼ��
	CRect tabRect;   // ��ǩ�ؼ��ͻ�����λ�úʹ�С   
	m_tab.InsertItem(0, _T("���մ�ѧ"));         // �����һ����ǩ�����Ͻ�ͨ��ѧ��  
	m_tab.InsertItem(1, _T("�й���ѧ������ѧ"));  // ����ڶ�����ǩ�����Ͻ�ͨ��ѧ��   
	anhuitu.Create(IDD_ANHUI_DIALOG, &m_tab);    // ������һ����ǩҳ   
	kexuetu.Create(IDD_KEXUE_DIALOG, &m_tab); // �����ڶ�����ǩҳ   

	m_tab.GetClientRect(&tabRect);    // ��ȡ��ǩ�ؼ��ͻ���Rect   
									  // ����tabRect��ʹ�串�Ƿ�Χ�ʺϷ��ñ�ǩҳ   
	tabRect.left ;
	tabRect.right;
	tabRect.top += 25;
	tabRect.bottom ;
	// ���ݵ����õ�tabRect����swjtu�ӶԻ��򣬲�����Ϊ��ʾ   
	anhuitu.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
	// ���ݵ����õ�tabRect����xajtu�ӶԻ��򣬲�����Ϊ����   
	kexuetu.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);

	//��ʼ������
	m_newFont.CreatePointFont(180, _T("����"));

	SetTimer(3, 200, NULL);

	//������ͼ
	srand((unsigned)time(NULL));
	SetTimer(4, 200, NULL);

	//��ʼ������������ѡ��
	m_somboy.AddString(_T("+"));
	m_somboy.AddString(_T("-"));
	m_somboy.AddString(_T("*"));
	m_somboy.AddString(_T("/"));
	m_somboy.SetCurSel(0);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CAdditionsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CAdditionsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);

		dc.FillSolidRect(rect, RGB(217, 226, 241));   //����Ϊǳ��ɫ����
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		CRect rect;
		GetClientRect(&rect);

		dc.FillSolidRect(rect, RGB(217, 226, 241));   //����Ϊǳ��ɫ����
		m_pOldFont = (CFont*)dc.SelectObject(&m_newFont);
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(RGB(255, 255, 0));
		dc.TextOutW(m_nTextX, 10, _T("��ӭ���������ף�"));
		dc.SetTextColor(RGB(0, 255, 0));
		dc.TextOutW(10, m_nTextY, _T("��ӭ���������ף�"));
		dc.SelectObject(m_pOldFont);
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CAdditionsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#include "AddSheet.h"
#include "Addsheet.h"

void CAdditionsDlg::OnBnClickedInstructButton()
{
	// TODO: Add your control notification handler code here   

	// �������Ա����   
	CAddsheet sheet(_T("ʹ��˵��"));
	// �������ԶԻ���Ϊ�򵼶Ի���
	//sheet.SetWizardMode();
	// ��ģ̬�򵼶Ի���   
	sheet.DoModal();
}



void CAdditionsDlg::OnBnClickedOpenButton()
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here   
	// ���ù�����   
	TCHAR szFilter[] = _T("�ı��ļ�(*.txt)|*.txt|�����ļ�(*.*)|*.*||");
	// ������ļ��Ի���   
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
	CString strFilePath;

	// ��ʾ���ļ��Ի���   
	if (IDOK == fileDlg.DoModal())
	{
		// ���������ļ��Ի����ϵġ��򿪡���ť����ѡ����ļ�·����ʾ���༭����  
		strFilePath = fileDlg.GetPathName();
		SetDlgItemText(IDC_OPEN_EDIT, strFilePath);
		char writeBuffer[500];     // Ҫд������ݵĻ���   
		char readBuffer[500];      // ��Ŷ�ȡ���ݵĻ���   
		LONGLONG lOff = 0;         // �ļ�ָ���ƫ������Ҳ�Ƕ�ȡ�������ݵ����ֽ���  
								   // ����CFile����ͬʱ�Դ����Ͷ�д�ķ�ʽ���ļ�E:\1.txt   
		CFile file(strFilePath, CFile::modeCreate | CFile::modeReadWrite);

		// ��д�����ݵĻ�����ÿ���ֽڶ���ֵΪ�ַ�c   
		memset(writeBuffer, 'b', sizeof(writeBuffer));
		// ������д�뵽�ļ���   
		file.Write(writeBuffer, sizeof(writeBuffer));

		while (true)
		{
			// ���ļ���ͷΪ��׼���ƶ��ļ�ָ�뵽lOff��λ��   
			file.Seek(lOff, CFile::begin);
			// ��ȡ100���ֽڵ����ݵ���Ŷ�ȡ���ݵĻ����readBuffer + lOffλ�ô�   
			int nRet = file.Read(readBuffer + lOff, 100);
			// ����ʵ�ʶ�ȡ���ֽ����������ļ�ָ����ƶ���   
			lOff += nRet;
			// �����ȡ����ʱ����ֵС��ָ����100��˵���ѵ��ļ�β������ѭ��   
			if (nRet < 100)
				break;
		}

		// �ر��ļ�   
		file.Close();
	}

}


void CAdditionsDlg::OnBnClickedSaveButton()
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here   
	// ���ù�����   
	TCHAR szFilter[] = _T("�ı��ļ�(*.txt)|*.txt|Word�ļ�(*.doc)|*.doc|�����ļ�(*.*)|*.*||");
	// ���챣���ļ��Ի���   
	CFileDialog fileDlg(FALSE, _T("doc"), _T("my"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	CString strFilePath;

	// ��ʾ�����ļ��Ի���   
	if (IDOK == fileDlg.DoModal())
	{
		// ���������ļ��Ի����ϵġ����桱��ť����ѡ����ļ�·����ʾ���༭����  
		strFilePath = fileDlg.GetPathName();
		SetDlgItemText(IDC_SAVE_EDIT, strFilePath);
	}
}

//����Ի���
void CAdditionsDlg::OnBnClickedFontButton()
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here   
	CString strFontName;    // ��������   
	LOGFONT lf;             // LOGFONT����   

							// ��lf�����ֽ�����   
	memset(&lf, 0, sizeof(LOGFONT));

	// ��lf�е�Ԫ����������Ϊ�����塱   
	_tcscpy_s(lf.lfFaceName, LF_FACESIZE, _T("����"));

	// ��������Ի��򣬳�ʼѡ��������Ϊ�����塱   
	CFontDialog fontDlg(&lf);

	if (IDOK == fontDlg.DoModal())     // ��ʾ����Ի���   
	{
		// ���m_font�Ѿ�������һ��������Դ�������ͷ���   
		if (m_font.m_hObject)
		{
			m_font.DeleteObject();
		}
		// ʹ��ѡ�������LOGFONT�����µ�����   
		m_font.CreateFontIndirect(fontDlg.m_cf.lpLogFont);
		// ��ȡ�༭��IDC_FONT_EDIT��CWndָ�룬������������   
		GetDlgItem(IDC_FONT_EDIT)->SetFont(&m_font);

		// ����û�ѡ��������Ի����OK��ť�����ȡ��ѡ����������Ʋ���ʾ���༭����   
		strFontName = fontDlg.m_cf.lpLogFont->lfFaceName;
		SetDlgItemText(IDC_FONT_EDIT, strFontName);
	}
}

//��ɫ�Ի���
void CAdditionsDlg::OnBnClickedColorButton()
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here   
	COLORREF color = RGB(255, 0, 0);      // ��ɫ�Ի���ĳ�ʼ��ɫΪ��ɫ  
	CColorDialog colorDlg(color);         // ������ɫ�Ի��򣬴����ʼ��ɫֵ   

	CRect rectPicture;       // ͼƬ�ؼ��ľ�����������   
	CBrush newBrush;         // �������»�ˢ   
	CBrush *pOldBrush;       // �ɻ�ˢ��ָ��   
	CClientDC clientDC(this); // ����ͻ������豸�����Ķ��� 

	if (IDOK == colorDlg.DoModal())       // ��ʾ��ɫ�Ի��򣬲��ж��Ƿ����ˡ�ȷ����   
	{
		color = colorDlg.GetColor();      // ��ȡ��ɫ�Ի�����ѡ�����ɫֵ  
		SetDlgItemInt(IDC_COLOR_EDIT, color);         // ��Color�༭������ʾ��ѡ��ɫֵ   
		SetDlgItemInt(IDC_R_EDIT, GetRValue(color));  // ��R�༭������ʾ��ѡ��ɫ��R����ֵ   
		SetDlgItemInt(IDC_G_EDIT, GetGValue(color));  // ��G�༭������ʾ��ѡ��ɫ��G����ֵ   
		SetDlgItemInt(IDC_B_EDIT, GetBValue(color));  // ��B�༭������ʾ��ѡ��ɫ��B����ֵ  

		m_picColor.GetClientRect(&rectPicture);
		newBrush.CreateSolidBrush(color);
		CDC* pDC = (CDC*)m_picColor.GetDC();
		pOldBrush = pDC->SelectObject(&newBrush);
		pDC->Rectangle(rectPicture);
		// ��ȡͼƬ�ؼ������������Ļ����   
		//m_picColor.GetWindowRect(&rectPicture);
		// ��ͼƬ�ؼ������������Ļ����ת��Ϊ�丸���ڼ��Ի���Ŀͻ�������   
		//ScreenToClient(&rectPicture);

		//// ѡ���»�ˢ��������ɻ�ˢ��ָ�뵽pOldBrush   
		//pOldBrush = clientDC.SelectObject(&newBrush);
		//// ���»�ˢΪͼƬ�ؼ������ɫ   
		//clientDC.Rectangle(rectPicture);

		// �ָ��ɻ�ˢ   
		pDC->SelectObject(pOldBrush);
		// ɾ���»�ˢ   
		newBrush.DeleteObject();
	}
}


void CAdditionsDlg::AllCheck()
{
	m_com.SetCheck(0);
	m_sofware.SetCheck(0);
	m_english.SetCheck(0);
	m_japanese.SetCheck(0);
	m_civil.SetCheck(0);
	m_cost.SetCheck(0);
}

void CAdditionsDlg::OnBnClickedComRadio()
{
	// TODO: Add your control notification handler code here
	AllCheck();
	choose = 1;
	m_com.SetCheck(1);
	m_sofware.SetCheck(1);
	m_english.EnableWindow(FALSE);
	m_japanese.EnableWindow(FALSE);
	m_civil.EnableWindow(FALSE);
	m_cost.EnableWindow(FALSE);
}


void CAdditionsDlg::OnBnClickedBuiRadio()
{
	// TODO: Add your control notification handler code here
	choose = 2;
	AllCheck();
	m_com.EnableWindow(FALSE);
	m_sofware.EnableWindow(FALSE);
	m_english.SetCheck(1);
	m_japanese.SetCheck(1);
	m_civil.EnableWindow(FALSE);
	m_cost.EnableWindow(FALSE);
}


void CAdditionsDlg::OnBnClickedLanRadio()
{
	// TODO: Add your control notification handler code here
	AllCheck();
	choose = 3;
	m_com.EnableWindow(FALSE);
	m_sofware.EnableWindow(FALSE);
	m_english.EnableWindow(FALSE);
	m_japanese.EnableWindow(FALSE);
	m_civil.SetCheck(1);
	m_cost.SetCheck(1);
}


void CAdditionsDlg::OnBnClickedSureButton()
{
	// TODO: Add your control notification handler code here
	CString major;
	if(choose==1)
		GetDlgItemText(IDC_COM_RADIO, major);
	else if(choose == 2)
		GetDlgItemText(IDC_BUI_RADIO, major);
	else if(choose == 3)
		GetDlgItemText(IDC_LAN_RADIO, major);
	CString string = major;
	if (m_com.GetCheck() == 1)
		string += _T(" �������");
	if (m_sofware.GetCheck() == 1)
		string += _T(" ���繤��");
	if (m_english.GetCheck() == 1)
		string += _T(" Ӣ��");
	if (m_japanese.GetCheck() == 1)
		string += _T(" ����");
	if (m_civil.GetCheck() == 1)
		string += _T(" ��ľ����");
	if (m_cost.GetCheck() == 1)
		string += _T(" ��۹���");
	SetDlgItemText(IDC_CHOOSE_EDIT, string);
}


void CAdditionsDlg::OnLbnSelchangeWebList()
{
	// TODO: Add your control notification handler code here
	CString strText;
	int nCurSel;
	nCurSel = m_list.GetCurSel();
	m_list.GetText(nCurSel, strText);
	SetDlgItemText(IDC_SET_WEB_EDIT, strText);

}


void CAdditionsDlg::OnCbnSelchangeWebCombo()
{
	// TODO: Add your control notification handler code here
	CString strbox;
	int nSel;
	// ��ȡ��Ͽ�ؼ����б����ѡ���������   
	nSel = m_combox.GetCurSel();
	// ����ѡ����������ȡ�����ַ���   
	m_combox.GetLBText(nSel, strbox);
	// ����Ͽ���ѡ�е��ַ�����ʾ��IDC_SEL_WEB_EDIT�༭����   
	SetDlgItemText(IDC_SET_WEB_EDIT, strbox);
}


void CAdditionsDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	int pos = m_horiScrollbars.GetScrollPos();  // ��ȡˮƽ��������ǰλ��  

	switch (nSBCode)
	{
		// ����������һ�У���pos��1  
	case SB_LINELEFT:
		pos -= 1;
		break;
		// ������ҹ���һ�У���pos��1  
	case SB_LINERIGHT:
		pos += 1;
		break;
		// ����������һҳ����pos��10  
	case SB_PAGELEFT:
		pos -= 10;
		break;
		// ������ҹ���һҳ����pos��10  
	case SB_PAGERIGHT:
		pos += 10;
		break;
		// �������������ˣ���posΪ1  
	case SB_LEFT:
		pos = 1;
		break;
		// ������������Ҷˣ���posΪ100  
	case SB_RIGHT:
		pos = 100;
		break;
		// ����϶������������ָ��λ�ã���pos��ֵΪnPos��ֵ  
	case SB_THUMBPOSITION:
		pos = nPos;
		break;
		// �����m_horiScrollbar.SetScrollPos(pos);ִ��ʱ��ڶ��ν���˺���������ȷ��������λ�ã����һ�ֱ�ӵ�default��֧�������ڴ˴����ñ༭������ʾ��ֵ  
	default:
		SetDlgItemInt(IDC_HSCROLL_EDIT, pos);
		return;
	}

	// ���ù�����λ��  
	m_horiScrollbars.SetScrollPos(pos);
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CAdditionsDlg::OnLvnItemchangedJiaodaList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	CString strLangName;    // ѡ�����Ե������ַ���   
	NMLISTVIEW *pNMListView = (NMLISTVIEW*)pNMHDR;

	if (-1 != pNMListView->iItem)        // ���iItem����-1����˵�����б��ѡ��   
	{
		// ��ȡ��ѡ���б����һ��������ı�   
		strLangName = m_jiaodaList.GetItemText(pNMListView->iItem, 0);
		// ��ѡ���������ʾ��༭����   
		SetDlgItemText(IDC_SET_WEB_EDIT, strLangName);
	}
	*pResult = 0;
}


void CAdditionsDlg::OnTvnSelchangedWebTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	CString strText; // ���ڵ�ı�ǩ�ı��ַ���   

					 // ��ȡ��ǰѡ�нڵ�ľ��   
	HTREEITEM hItem = m_tree.GetSelectedItem();
	// ��ȡѡ�нڵ�ı�ǩ�ı��ַ���   
	strText = m_tree.GetItemText(hItem);
	// ���ַ�����ʾ���༭����   
	SetDlgItemText(IDC_ITEM_SET_EDIT, strText);
	*pResult = 0;
}


void CAdditionsDlg::OnTcnSelchangeTabSee(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	CRect tabRect;    // ��ǩ�ؼ��ͻ�����Rect   

	// ��ȡ��ǩ�ؼ��ͻ���Rect����������������ʺϷ��ñ�ǩҳ   
	m_tab.GetClientRect(&tabRect);
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;

	switch (m_tab.GetCurSel())
	{
		// �����ǩ�ؼ���ǰѡ���ǩΪ�����Ͻ�ͨ��ѧ��������ʾswjtu�Ի�������xajtu�Ի���   
	case 0:
		anhuitu.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		kexuetu.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		break;
		// �����ǩ�ؼ���ǰѡ���ǩΪ��������ͨ��ѧ����������swjtu�Ի�����ʾxajtu�Ի���   
	case 1:
		anhuitu.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		kexuetu.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		break;
	default:
		break;
	}
	*pResult = 0;
}



void CAdditionsDlg::OnBnClickedButtonTabsure()
{
	MessageBox(_T("1,2"));
	// TODO: Add your control notification handler code here
	SetTimer(1, 1000, NULL);
	// ����IDΪ2�Ķ�ʱ������ʱʱ��Ϊ2��   
	SetTimer(2, 2000, NULL);
}


void CAdditionsDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	switch (nIDEvent)
	{
	case 1:
		// ���m_nData1�Ѿ��ﵽ10��������IDΪ1�Ķ�ʱ��   
		if (100 == m_nData1)
		{
			KillTimer(1);
			break;
		}
		// ˢ�±༭��IDC_EDIT1����ʾ   
		SetDlgItemInt(IDC_EDIT_TIME1, ++m_nData1);
		break;
	case 2:
		// ���m_nData2�Ѿ��ﵽ5��������IDΪ2�Ķ�ʱ��   
		if (50 == m_nData2)
		{
			KillTimer(2);
			break;
		}
		// ˢ�±༭��IDC_EDIT2����ʾ   
		SetDlgItemInt(IDC_EDIT_TIME2, ++m_nData2);
		break;
	case 6:
		if (100 == m_nData3)
		{
			KillTimer(6);
			break;
		}
		m_set.SetPos(++m_nData3);
	default:
		break;
	}
	//�ƶ����岿��
	LOGFONT logFont;
	m_newFont.GetLogFont(&logFont);

	m_nTextX -= 5;
	if (m_nTextX < 10)
		m_nTextX = 260;
	m_nTextY += abs(logFont.lfHeight);
	if (m_nTextY > 260)
		m_nTextY = 10;

	//Invalidate();

	//���Ʋ���ͼ����
	CRect rectPicture;

	// �������е�����Ԫ��ǰ��һ����λ����һ��Ԫ�ض���   
	for (int i = 0; i<POINT_COUNT - 1; i++)
	{
		m_nzValues[i] = m_nzValues[i + 1];
	}
	// Ϊ���һ��Ԫ�ظ�һ��80���ڵ������ֵ�����ͣ�   
	m_nzValues[POINT_COUNT - 1] = rand() % 80;

	// ��ȡ��ͼ�ؼ��Ŀͻ�������   
	// ���ͻ��������Դ��ڵ����Ͻ�Ϊԭ�㣬������������Ļ���Ͻ�Ϊԭ�����Ļ���꣩   
	m_picDraw.GetClientRect(&rectPicture);

	// ���Ʋ���ͼ   
	DrawWave(m_picDraw.GetDC(), rectPicture);
	CDialogEx::OnTimer(nIDEvent);
}

void CAdditionsDlg::DrawWave(CDC *pDC, CRect &rectPicture) {
	float fDeltaX;     // x������������ͼ����������   
	float fDeltaY;     // y��ÿ���߼���λ��Ӧ������ֵ   
	int nX;      // ������ʱ���ڴ洢��ͼ��ĺ�����   
	int nY;      // ������ʱ���ڴ洢��ͼ���������   
	CPen newPen;       // ���ڴ����»���   
	CPen *pOldPen;     // ���ڴ�žɻ���   
	CBrush newBrush;   // ���ڴ����»�ˢ   
	CBrush *pOldBrush; // ���ڴ�žɻ�ˢ   

					   // ����fDeltaX��fDeltaY   
	fDeltaX = (float)rectPicture.Width() / (POINT_COUNT - 1);
	fDeltaY = (float)rectPicture.Height() / 80;

	// ������ɫ�»�ˢ   
	newBrush.CreateSolidBrush(RGB(0, 0, 0));
	// ѡ���»�ˢ�������ɻ�ˢ��ָ�뱣�浽pOldBrush   
	pOldBrush = pDC->SelectObject(&newBrush);
	// �Ժ�ɫ��ˢΪ��ͼ�ؼ�����ɫ���γɺ�ɫ����   
	pDC->Rectangle(rectPicture);
	// �ָ��ɻ�ˢ   
	pDC->SelectObject(pOldBrush);
	// ɾ���»�ˢ   
	newBrush.DeleteObject();

	// ����ʵ�Ļ��ʣ��ֶ�Ϊ1����ɫΪ��ɫ   
	newPen.CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	// ѡ���»��ʣ������ɻ��ʵ�ָ�뱣�浽pOldPen   
	pOldPen = pDC->SelectObject(&newPen);

	// ����ǰ���ƶ�����ͼ�ؼ����ڵ����½ǣ��Դ�Ϊ���ε���ʼ��   
	pDC->MoveTo(rectPicture.left, rectPicture.bottom);
	// ����m_nzValues������ÿ�����Ӧ������λ�ã����������ӣ������γ�����   
	for (int i = 0; i < POINT_COUNT; i++)
	{
		nX = rectPicture.left + (int)(i * fDeltaX);
		nY = rectPicture.bottom - (int)(m_nzValues[i] * fDeltaY);
		pDC->LineTo(nX, nY);
	}

	// �ָ��ɻ���   
	pDC->SelectObject(pOldPen);
	// ɾ���»���   
	newPen.DeleteObject();
}

void CAdditionsDlg::OnDestroy()
{
	CDialogEx::OnDestroy();


	// TODO: Add your message handler code here
	KillTimer(3);
	KillTimer(4);
}


void CAdditionsDlg::OnBnClickedButtonCount()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	int choose=m_somboy.GetCurSel();
	switch (choose) {
	case 0: m_dataresult = m_datafirst + m_datasecond;
		break;
	case 1:m_dataresult = m_datafirst - m_datasecond;
		break;
	case 2:m_dataresult = m_datafirst * m_datasecond;
		break;
	case 3:if (m_datasecond == 0) {
		MessageBox(_T("��������Ч���ݣ�"));
		break;
	}
		m_dataresult = m_datafirst / m_datasecond;
		break;
	}
	UpdateData(false);
}
//ʹ�ö��̴߳���һ�����ڣ��߳̽��������Զ�����
//#include<thread>
//using namespace std;
//void about() {
//	CAboutDlg *pdlg;
//	pdlg = new CAboutDlg();
//	pdlg->Create(IDD_ABOUTBOX); // �´����Ի���
//	pdlg->ShowWindow(SW_SHOW);
//	
//}
void CAdditionsDlg::OnBnClickedButtonNew()
{
	// TODO: Add your control notification handler code here
	//thread pthread(about);
	//pthread.join();
	//this->PostMessage(WM_CLOSE); // �������Ի���ر�
	//this->ShowWindow(SW_HIDE);
	//CAboutDlg *pdlg;
	//pdlg = new CAboutDlg();
	//pdlg->Create(IDD_ABOUTBOX); // �´����Ի���
	//pdlg->ShowWindow(SW_SHOW);
	//this->ShowWindow(SW_HIDE);
}




HBRUSH CAdditionsDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	if (nCtlColor == CTLCOLOR_BTN)          //���İ�ť��ɫ
	{
		//pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 255, 0));
		pDC->SetBkColor(RGB(1, 121, 255));
		pDC->SetDCBrushColor(RGB(1, 121, 255));
		HBRUSH b = CreateSolidBrush(RGB(121, 121, 255));
		return b;
	}
	else if (nCtlColor == CTLCOLOR_SCROLLBAR)  //
	{
		//pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SetBkColor(RGB(233, 233, 220));
		HBRUSH b = CreateSolidBrush(RGB(121, 121, 255));
		return b;
	}
	else if (nCtlColor == CTLCOLOR_EDIT)   //���ı༭��
	{
		//pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SetBkColor(RGB(246, 246, 246));
		HBRUSH b = CreateSolidBrush(RGB(246, 246, 246));
		return b;
	}
	else if (nCtlColor == CTLCOLOR_STATIC)  //���ľ�̬�ı�
	{
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SetBkColor(RGB(217, 226, 241));
		HBRUSH b = CreateSolidBrush(RGB(217, 226, 241));
		return b;
	}
	else if (nCtlColor == CTLCOLOR_DLG)   //���ĶԻ��򱳾�ɫ
	{
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SetBkColor(RGB(166, 254, 1));
		HBRUSH b = CreateSolidBrush(RGB(213, 226, 240));
		return b;
	}
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

void CAboutDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//auto x = AfxGetApp()->m_pMainWnd;
	//x->ShowWindow(SW_SHOW);
	this->ShowWindow(SW_HIDE);
	//auto x = AfxGetApp()->m_pMainWnd;
	//x->ShowWindow(SW_SHOW);
	CAdditionsDlg dlg;
	dlg.DoModal();

	this->SendMessage(WM_CLOSE);
	CDialogEx::OnOK();
}


void CAdditionsDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	CDialogEx::OnOK();
}


