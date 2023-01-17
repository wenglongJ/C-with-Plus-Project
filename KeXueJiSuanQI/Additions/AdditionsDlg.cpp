
// AdditionsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Additions.h"
#include "AdditionsDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CAdditionsDlg 对话框



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


// CAdditionsDlg 消息处理程序

BOOL CAdditionsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	//列表控件初始化
	// TODO: 在此添加额外的初始化代码
	m_list.AddString(_T("清华大学"));
	m_list.AddString(_T("北京大学"));
	m_list.AddString(_T("上海交通大学"));
	m_list.AddString(_T("西安交通大学"));
	m_list.AddString(_T("西南交通大学"));
	m_list.AddString(_T("北京交通大学"));


	m_combox.AddString(_T("上海交通大学"));
	m_combox.AddString(_T("西安交通大学"));
	m_combox.AddString(_T("西南交通大学"));
	m_combox.AddString(_T("北京交通大学"));

	//滚动条初始化
	CScrollBar *ptr = new CScrollBar;
	ptr->Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,
		CRect(10, 10, 100, 100), this, 1);

	m_horiScrollbars.SetScrollRange(1, 100);
	// 设置水平滚动条的初始位置为20   
	m_horiScrollbars.SetScrollPos(20);
	// 在编辑框中显示20   
	SetDlgItemInt(IDC_HSCROLL_EDIT, 20);

	m_set.SetRange(1, 100);
	m_set.SetPos(20);
	SetTimer(6, 100, 0);
	//表格控件初始化
	CRect rect;
	m_jiaodaList.GetClientRect(&rect);

	m_jiaodaList.SetExtendedStyle(m_jiaodaList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_jiaodaList.InsertColumn(0, _T("大学名称"), LVCFMT_CENTER, rect.Width() / 2, 0);
	m_jiaodaList.InsertColumn(2, _T("所在地"), LVCFMT_CENTER, rect.Width() / 2, 1);
	m_jiaodaList.InsertItem(0, _T("上海交通大学"));
	m_jiaodaList.SetItemText(0, 1, _T("上海"));
	m_jiaodaList.InsertItem(1, _T("西安交通大学"));
	m_jiaodaList.SetItemText(1, 1, _T("西安"));
	m_jiaodaList.InsertItem(2, _T("西南交通大学"));
	m_jiaodaList.SetItemText(2, 1, _T("成都"));
	m_jiaodaList.InsertItem(3, _T("北京交通大学"));
	m_jiaodaList.SetItemText(3, 1, _T("北京"));
	m_jiaodaList.InsertItem(4, _T("新竹交通大学"));
	m_jiaodaList.SetItemText(4, 1, _T("台湾"));

	//树型初始化
	HICON hIcon[3];      // 图标句柄数组   
	HTREEITEM hRoot;     // 树的根节点的句柄   
	HTREEITEM hCataItem; // 可表示任一分类节点的句柄   
	HTREEITEM hArtItem;  // 可表示任一文章节点的句柄   

						 // 加载三个图标，并将它们的句柄保存到数组   
	hIcon[0] = theApp.LoadIcon(IDI_ICON1);
	hIcon[1] = theApp.LoadIcon(IDI_ICON2);
	hIcon[2] = theApp.LoadIcon(IDI_ICON3);

	// 创建图像序列CImageList对象   
	m_imageList.Create(32, 32, ILC_COLOR32, 3, 3);
	// 将三个图标添加到图像序列   
	for (int i = 0; i<3; i++)
	{
		m_imageList.Add(hIcon[i]);
	}

	// 为树形控件设置图像序列   
	m_tree.SetImageList(&m_imageList, TVSIL_NORMAL);

	// 插入根节点   
	hRoot = m_tree.InsertItem(_T("互联网大牛"), 0, 0);
	// 在根节点下插入子节点   
	hCataItem = m_tree.InsertItem(_T("百度"), 1, 1, hRoot, TVI_LAST);
	// 为“百度”节点添加附加的编号数据，在鼠标划过该节点时显示   
	m_tree.SetItemData(hCataItem, 1);
	// 在“百度”节点下插入子节点   
	hArtItem = m_tree.InsertItem(_T("手机百度"), 2, 2, hCataItem, TVI_LAST);
	// 为“手机百度”节点添加附加的编号数据，在鼠标划过该节点时显示   
	m_tree.SetItemData(hArtItem, 2);
	// 在“百度”节点下插入另一子节点   
	hArtItem = m_tree.InsertItem(_T("百度地图"), 2, 2, hCataItem, TVI_LAST);
	// 为“百度地图”节点添加附加的编号数据，在鼠标划过该节点时显示   
	m_tree.SetItemData(hArtItem, 3);
	// 在根节点下插入第二个子节点   
	hCataItem = m_tree.InsertItem(_T("腾讯"), 1, 1, hRoot, TVI_LAST);
	// 为“腾讯”节点添加附加的编号数据，在鼠标划过该节点时显示   
	m_tree.SetItemData(hCataItem, 4);
	// 在“腾讯”节点下插入子节点   
	hArtItem = m_tree.InsertItem(_T("QQ"), 2, 2, hCataItem, TVI_LAST);
	// 为“QQ”节点添加附加的编号数据，在鼠标划过该节点时显示   
	m_tree.SetItemData(hArtItem, 5);
	// 在“腾讯”节点下插入另一子节点   
	hArtItem = m_tree.InsertItem(_T("微信"), 2, 2, hCataItem, TVI_LAST);
	// 为“微信”节点添加附加的编号数据，在鼠标划过该节点时显示   
	m_tree.SetItemData(hArtItem, 6);
	// 在根节点下插入第三个子节点   
	hCataItem = m_tree.InsertItem(_T("阿里巴巴"), 1, 1, hRoot, TVI_LAST);
	// 为“阿里巴巴”节点添加附加的编号数据，在鼠标划过该节点时显示   
	m_tree.SetItemData(hCataItem, 7);
	// 在“阿里巴巴”节点下插入子节点   
	hArtItem = m_tree.InsertItem(_T("淘宝"), 2, 2, hCataItem, TVI_LAST);
	// 为“淘宝”节点添加附加的编号数据，在鼠标划过该节点时显示   
	m_tree.SetItemData(hArtItem, 8);
	// 在“阿里巴巴”节点下插入另一子节点   
	hArtItem = m_tree.InsertItem(_T("天猫"), 2, 2, hCataItem, TVI_LAST);
	// 为“天猫”节点添加附加的编号数据，在鼠标划过该节点时显示   
	m_tree.SetItemData(hArtItem, 9);
	// 在根节点下插入第四个子节点   
	hCataItem = m_tree.InsertItem(_T("蚂蚁金融"), 1, 1, hRoot, TVI_LAST);
	// 为“蚂蚁金融”节点添加附加的编号数据，在鼠标划过该节点时显示   
	m_tree.SetItemData(hCataItem, 10);
	// 在“蚂蚁金融”节点下插入子节点   
	hArtItem = m_tree.InsertItem(_T("余额宝"), 2, 2, hCataItem, TVI_LAST);
	// 为“余额宝”节点添加附加的编号数据，在鼠标划过该节点时显示   
	m_tree.SetItemData(hArtItem, 11);
	// 在“蚂蚁金融”节点下插入另一子节点   
	hArtItem = m_tree.InsertItem(_T("支付宝"), 2, 2, hCataItem, TVI_LAST);
	// 为“支付宝”节点添加附加的编号数据，在鼠标划过该节点时显示   
	m_tree.SetItemData(hArtItem, 12);

	//tab控件初始化
	CRect tabRect;   // 标签控件客户区的位置和大小   
	m_tab.InsertItem(0, _T("安徽大学"));         // 插入第一个标签“西南交通大学”  
	m_tab.InsertItem(1, _T("中国科学技术大学"));  // 插入第二个标签“西南交通大学”   
	anhuitu.Create(IDD_ANHUI_DIALOG, &m_tab);    // 创建第一个标签页   
	kexuetu.Create(IDD_KEXUE_DIALOG, &m_tab); // 创建第二个标签页   

	m_tab.GetClientRect(&tabRect);    // 获取标签控件客户区Rect   
									  // 调整tabRect，使其覆盖范围适合放置标签页   
	tabRect.left ;
	tabRect.right;
	tabRect.top += 25;
	tabRect.bottom ;
	// 根据调整好的tabRect放置swjtu子对话框，并设置为显示   
	anhuitu.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
	// 根据调整好的tabRect放置xajtu子对话框，并设置为隐藏   
	kexuetu.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);

	//初始化字体
	m_newFont.CreatePointFont(180, _T("隶书"));

	SetTimer(3, 200, NULL);

	//画波形图
	srand((unsigned)time(NULL));
	SetTimer(4, 200, NULL);

	//初始化计算器符号选择
	m_somboy.AddString(_T("+"));
	m_somboy.AddString(_T("-"));
	m_somboy.AddString(_T("*"));
	m_somboy.AddString(_T("/"));
	m_somboy.SetCurSel(0);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAdditionsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);

		dc.FillSolidRect(rect, RGB(217, 226, 241));   //设置为浅蓝色背景
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		CRect rect;
		GetClientRect(&rect);

		dc.FillSolidRect(rect, RGB(217, 226, 241));   //设置为浅蓝色背景
		m_pOldFont = (CFont*)dc.SelectObject(&m_newFont);
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(RGB(255, 255, 0));
		dc.TextOutW(m_nTextX, 10, _T("欢迎来到鸡啄米！"));
		dc.SetTextColor(RGB(0, 255, 0));
		dc.TextOutW(10, m_nTextY, _T("欢迎来到鸡啄米！"));
		dc.SelectObject(m_pOldFont);
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAdditionsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#include "AddSheet.h"
#include "Addsheet.h"

void CAdditionsDlg::OnBnClickedInstructButton()
{
	// TODO: Add your control notification handler code here   

	// 创建属性表对象   
	CAddsheet sheet(_T("使用说明"));
	// 设置属性对话框为向导对话框
	//sheet.SetWizardMode();
	// 打开模态向导对话框   
	sheet.DoModal();
}



void CAdditionsDlg::OnBnClickedOpenButton()
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here   
	// 设置过滤器   
	TCHAR szFilter[] = _T("文本文件(*.txt)|*.txt|所有文件(*.*)|*.*||");
	// 构造打开文件对话框   
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
	CString strFilePath;

	// 显示打开文件对话框   
	if (IDOK == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里  
		strFilePath = fileDlg.GetPathName();
		SetDlgItemText(IDC_OPEN_EDIT, strFilePath);
		char writeBuffer[500];     // 要写入的数据的缓存   
		char readBuffer[500];      // 存放读取数据的缓存   
		LONGLONG lOff = 0;         // 文件指针的偏移量，也是读取到的数据的总字节数  
								   // 构造CFile对象，同时以创建和读写的方式打开文件E:\1.txt   
		CFile file(strFilePath, CFile::modeCreate | CFile::modeReadWrite);

		// 将写入数据的缓存中每个字节都赋值为字符c   
		memset(writeBuffer, 'b', sizeof(writeBuffer));
		// 将数据写入到文件中   
		file.Write(writeBuffer, sizeof(writeBuffer));

		while (true)
		{
			// 以文件开头为基准，移动文件指针到lOff的位置   
			file.Seek(lOff, CFile::begin);
			// 读取100个字节的数据到存放读取数据的缓存的readBuffer + lOff位置处   
			int nRet = file.Read(readBuffer + lOff, 100);
			// 根据实际读取的字节数，增加文件指针的移动量   
			lOff += nRet;
			// 如果读取数据时返回值小于指定的100，说明已到文件尾，跳出循环   
			if (nRet < 100)
				break;
		}

		// 关闭文件   
		file.Close();
	}

}


void CAdditionsDlg::OnBnClickedSaveButton()
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here   
	// 设置过滤器   
	TCHAR szFilter[] = _T("文本文件(*.txt)|*.txt|Word文件(*.doc)|*.doc|所有文件(*.*)|*.*||");
	// 构造保存文件对话框   
	CFileDialog fileDlg(FALSE, _T("doc"), _T("my"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	CString strFilePath;

	// 显示保存文件对话框   
	if (IDOK == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“保存”按钮，则将选择的文件路径显示到编辑框里  
		strFilePath = fileDlg.GetPathName();
		SetDlgItemText(IDC_SAVE_EDIT, strFilePath);
	}
}

//字体对话框
void CAdditionsDlg::OnBnClickedFontButton()
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here   
	CString strFontName;    // 字体名称   
	LOGFONT lf;             // LOGFONT变量   

							// 将lf所有字节清零   
	memset(&lf, 0, sizeof(LOGFONT));

	// 将lf中的元素字体名设为“宋体”   
	_tcscpy_s(lf.lfFaceName, LF_FACESIZE, _T("宋体"));

	// 构造字体对话框，初始选择字体名为“宋体”   
	CFontDialog fontDlg(&lf);

	if (IDOK == fontDlg.DoModal())     // 显示字体对话框   
	{
		// 如果m_font已经关联了一个字体资源对象，则释放它   
		if (m_font.m_hObject)
		{
			m_font.DeleteObject();
		}
		// 使用选定字体的LOGFONT创建新的字体   
		m_font.CreateFontIndirect(fontDlg.m_cf.lpLogFont);
		// 获取编辑框IDC_FONT_EDIT的CWnd指针，并设置其字体   
		GetDlgItem(IDC_FONT_EDIT)->SetFont(&m_font);

		// 如果用户选择了字体对话框的OK按钮，则获取被选择字体的名称并显示到编辑框里   
		strFontName = fontDlg.m_cf.lpLogFont->lfFaceName;
		SetDlgItemText(IDC_FONT_EDIT, strFontName);
	}
}

//颜色对话框
void CAdditionsDlg::OnBnClickedColorButton()
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here   
	COLORREF color = RGB(255, 0, 0);      // 颜色对话框的初始颜色为红色  
	CColorDialog colorDlg(color);         // 构造颜色对话框，传入初始颜色值   

	CRect rectPicture;       // 图片控件的矩形区域坐标   
	CBrush newBrush;         // 创建的新画刷   
	CBrush *pOldBrush;       // 旧画刷的指针   
	CClientDC clientDC(this); // 构造客户区的设备上下文对象 

	if (IDOK == colorDlg.DoModal())       // 显示颜色对话框，并判断是否点击了“确定”   
	{
		color = colorDlg.GetColor();      // 获取颜色对话框中选择的颜色值  
		SetDlgItemInt(IDC_COLOR_EDIT, color);         // 在Color编辑框中显示所选颜色值   
		SetDlgItemInt(IDC_R_EDIT, GetRValue(color));  // 在R编辑框中显示所选颜色的R分量值   
		SetDlgItemInt(IDC_G_EDIT, GetGValue(color));  // 在G编辑框中显示所选颜色的G分量值   
		SetDlgItemInt(IDC_B_EDIT, GetBValue(color));  // 在B编辑框中显示所选颜色的B分量值  

		m_picColor.GetClientRect(&rectPicture);
		newBrush.CreateSolidBrush(color);
		CDC* pDC = (CDC*)m_picColor.GetDC();
		pOldBrush = pDC->SelectObject(&newBrush);
		pDC->Rectangle(rectPicture);
		// 获取图片控件矩形区域的屏幕坐标   
		//m_picColor.GetWindowRect(&rectPicture);
		// 将图片控件矩形区域的屏幕坐标转换为其父窗口即对话框的客户区坐标   
		//ScreenToClient(&rectPicture);

		//// 选择新画刷，并保存旧画刷的指针到pOldBrush   
		//pOldBrush = clientDC.SelectObject(&newBrush);
		//// 以新画刷为图片控件填充颜色   
		//clientDC.Rectangle(rectPicture);

		// 恢复旧画刷   
		pDC->SelectObject(pOldBrush);
		// 删除新画刷   
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
		string += _T(" 软件工程");
	if (m_sofware.GetCheck() == 1)
		string += _T(" 网络工程");
	if (m_english.GetCheck() == 1)
		string += _T(" 英语");
	if (m_japanese.GetCheck() == 1)
		string += _T(" 日语");
	if (m_civil.GetCheck() == 1)
		string += _T(" 土木工程");
	if (m_cost.GetCheck() == 1)
		string += _T(" 造价工程");
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
	// 获取组合框控件的列表框中选中项的索引   
	nSel = m_combox.GetCurSel();
	// 根据选中项索引获取该项字符串   
	m_combox.GetLBText(nSel, strbox);
	// 将组合框中选中的字符串显示到IDC_SEL_WEB_EDIT编辑框中   
	SetDlgItemText(IDC_SET_WEB_EDIT, strbox);
}


void CAdditionsDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	int pos = m_horiScrollbars.GetScrollPos();  // 获取水平滚动条当前位置  

	switch (nSBCode)
	{
		// 如果向左滚动一列，则pos减1  
	case SB_LINELEFT:
		pos -= 1;
		break;
		// 如果向右滚动一列，则pos加1  
	case SB_LINERIGHT:
		pos += 1;
		break;
		// 如果向左滚动一页，则pos减10  
	case SB_PAGELEFT:
		pos -= 10;
		break;
		// 如果向右滚动一页，则pos加10  
	case SB_PAGERIGHT:
		pos += 10;
		break;
		// 如果滚动到最左端，则pos为1  
	case SB_LEFT:
		pos = 1;
		break;
		// 如果滚动到最右端，则pos为100  
	case SB_RIGHT:
		pos = 100;
		break;
		// 如果拖动滚动块滚动到指定位置，则pos赋值为nPos的值  
	case SB_THUMBPOSITION:
		pos = nPos;
		break;
		// 下面的m_horiScrollbar.SetScrollPos(pos);执行时会第二次进入此函数，最终确定滚动块位置，并且会直接到default分支，所以在此处设置编辑框中显示数值  
	default:
		SetDlgItemInt(IDC_HSCROLL_EDIT, pos);
		return;
	}

	// 设置滚动块位置  
	m_horiScrollbars.SetScrollPos(pos);
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CAdditionsDlg::OnLvnItemchangedJiaodaList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	CString strLangName;    // 选择语言的名称字符串   
	NMLISTVIEW *pNMListView = (NMLISTVIEW*)pNMHDR;

	if (-1 != pNMListView->iItem)        // 如果iItem不是-1，就说明有列表项被选择   
	{
		// 获取被选择列表项第一个子项的文本   
		strLangName = m_jiaodaList.GetItemText(pNMListView->iItem, 0);
		// 将选择的语言显示与编辑框中   
		SetDlgItemText(IDC_SET_WEB_EDIT, strLangName);
	}
	*pResult = 0;
}


void CAdditionsDlg::OnTvnSelchangedWebTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	CString strText; // 树节点的标签文本字符串   

					 // 获取当前选中节点的句柄   
	HTREEITEM hItem = m_tree.GetSelectedItem();
	// 获取选中节点的标签文本字符串   
	strText = m_tree.GetItemText(hItem);
	// 将字符串显示到编辑框中   
	SetDlgItemText(IDC_ITEM_SET_EDIT, strText);
	*pResult = 0;
}


void CAdditionsDlg::OnTcnSelchangeTabSee(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	CRect tabRect;    // 标签控件客户区的Rect   

	// 获取标签控件客户区Rect，并对其调整，以适合放置标签页   
	m_tab.GetClientRect(&tabRect);
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;

	switch (m_tab.GetCurSel())
	{
		// 如果标签控件当前选择标签为“西南交通大学”，则显示swjtu对话框，隐藏xajtu对话框   
	case 0:
		anhuitu.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		kexuetu.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		break;
		// 如果标签控件当前选择标签为“西安交通大学”，则隐藏swjtu对话框，显示xajtu对话框   
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
	// 启动ID为2的定时器，定时时间为2秒   
	SetTimer(2, 2000, NULL);
}


void CAdditionsDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	switch (nIDEvent)
	{
	case 1:
		// 如果m_nData1已经达到10，则销毁ID为1的定时器   
		if (100 == m_nData1)
		{
			KillTimer(1);
			break;
		}
		// 刷新编辑框IDC_EDIT1的显示   
		SetDlgItemInt(IDC_EDIT_TIME1, ++m_nData1);
		break;
	case 2:
		// 如果m_nData2已经达到5，则销毁ID为2的定时器   
		if (50 == m_nData2)
		{
			KillTimer(2);
			break;
		}
		// 刷新编辑框IDC_EDIT2的显示   
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
	//移动字体部分
	LOGFONT logFont;
	m_newFont.GetLogFont(&logFont);

	m_nTextX -= 5;
	if (m_nTextX < 10)
		m_nTextX = 260;
	m_nTextY += abs(logFont.lfHeight);
	if (m_nTextY > 260)
		m_nTextY = 10;

	//Invalidate();

	//绘制波形图部分
	CRect rectPicture;

	// 将数组中的所有元素前移一个单位，第一个元素丢弃   
	for (int i = 0; i<POINT_COUNT - 1; i++)
	{
		m_nzValues[i] = m_nzValues[i + 1];
	}
	// 为最后一个元素赋一个80以内的随机数值（整型）   
	m_nzValues[POINT_COUNT - 1] = rand() % 80;

	// 获取绘图控件的客户区坐标   
	// （客户区坐标以窗口的左上角为原点，这区别于以屏幕左上角为原点的屏幕坐标）   
	m_picDraw.GetClientRect(&rectPicture);

	// 绘制波形图   
	DrawWave(m_picDraw.GetDC(), rectPicture);
	CDialogEx::OnTimer(nIDEvent);
}

void CAdditionsDlg::DrawWave(CDC *pDC, CRect &rectPicture) {
	float fDeltaX;     // x轴相邻两个绘图点的坐标距离   
	float fDeltaY;     // y轴每个逻辑单位对应的坐标值   
	int nX;      // 在连线时用于存储绘图点的横坐标   
	int nY;      // 在连线时用于存储绘图点的纵坐标   
	CPen newPen;       // 用于创建新画笔   
	CPen *pOldPen;     // 用于存放旧画笔   
	CBrush newBrush;   // 用于创建新画刷   
	CBrush *pOldBrush; // 用于存放旧画刷   

					   // 计算fDeltaX和fDeltaY   
	fDeltaX = (float)rectPicture.Width() / (POINT_COUNT - 1);
	fDeltaY = (float)rectPicture.Height() / 80;

	// 创建黑色新画刷   
	newBrush.CreateSolidBrush(RGB(0, 0, 0));
	// 选择新画刷，并将旧画刷的指针保存到pOldBrush   
	pOldBrush = pDC->SelectObject(&newBrush);
	// 以黑色画刷为绘图控件填充黑色，形成黑色背景   
	pDC->Rectangle(rectPicture);
	// 恢复旧画刷   
	pDC->SelectObject(pOldBrush);
	// 删除新画刷   
	newBrush.DeleteObject();

	// 创建实心画笔，粗度为1，颜色为绿色   
	newPen.CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	// 选择新画笔，并将旧画笔的指针保存到pOldPen   
	pOldPen = pDC->SelectObject(&newPen);

	// 将当前点移动到绘图控件窗口的左下角，以此为波形的起始点   
	pDC->MoveTo(rectPicture.left, rectPicture.bottom);
	// 计算m_nzValues数组中每个点对应的坐标位置，并依次连接，最终形成曲线   
	for (int i = 0; i < POINT_COUNT; i++)
	{
		nX = rectPicture.left + (int)(i * fDeltaX);
		nY = rectPicture.bottom - (int)(m_nzValues[i] * fDeltaY);
		pDC->LineTo(nX, nY);
	}

	// 恢复旧画笔   
	pDC->SelectObject(pOldPen);
	// 删除新画笔   
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
		MessageBox(_T("请输入有效数据！"));
		break;
	}
		m_dataresult = m_datafirst / m_datasecond;
		break;
	}
	UpdateData(false);
}
//使用多线程创建一个窗口，线程结束窗口自动回收
//#include<thread>
//using namespace std;
//void about() {
//	CAboutDlg *pdlg;
//	pdlg = new CAboutDlg();
//	pdlg->Create(IDD_ABOUTBOX); // 新创建对话框
//	pdlg->ShowWindow(SW_SHOW);
//	
//}
void CAdditionsDlg::OnBnClickedButtonNew()
{
	// TODO: Add your control notification handler code here
	//thread pthread(about);
	//pthread.join();
	//this->PostMessage(WM_CLOSE); // 触发本对话框关闭
	//this->ShowWindow(SW_HIDE);
	//CAboutDlg *pdlg;
	//pdlg = new CAboutDlg();
	//pdlg->Create(IDD_ABOUTBOX); // 新创建对话框
	//pdlg->ShowWindow(SW_SHOW);
	//this->ShowWindow(SW_HIDE);
}




HBRUSH CAdditionsDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	if (nCtlColor == CTLCOLOR_BTN)          //更改按钮颜色
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
	else if (nCtlColor == CTLCOLOR_EDIT)   //更改编辑框
	{
		//pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SetBkColor(RGB(246, 246, 246));
		HBRUSH b = CreateSolidBrush(RGB(246, 246, 246));
		return b;
	}
	else if (nCtlColor == CTLCOLOR_STATIC)  //更改静态文本
	{
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SetBkColor(RGB(217, 226, 241));
		HBRUSH b = CreateSolidBrush(RGB(217, 226, 241));
		return b;
	}
	else if (nCtlColor == CTLCOLOR_DLG)   //更改对话框背景色
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


