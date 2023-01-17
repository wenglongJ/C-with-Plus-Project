#include "stdafx.h"
#include "TableCtrl.h"

//默认是高3，宽3，输入行数和列数
CTableCtrl::CTableCtrl(int m, int n) : CStatic(), m_nColumns(m), m_nRows(n)
{
	m_bRedraw = TRUE;
	m_pPenOld = NULL;
	m_pBmpOld = NULL;
}

CTableCtrl::~CTableCtrl()
{
	if (m_dcMem.m_hDC != NULL)
	{
		m_dcMem.DeleteDC();
	}
}

BEGIN_MESSAGE_MAP(CTableCtrl, CStatic)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

void CTableCtrl::OnPaint()
{
	CPaintDC dc(this);

	CRect rect;
	GetClientRect(rect);

	//第一次初始化创建m_pDcMem
	if (m_dcMem.m_hDC == NULL)
	{
		m_dcMem.CreateCompatibleDC(&dc);
	}

	//窗口刷新引起的重绘,防止再次绘图引起卡顿
	if (!m_bRedraw)
	{
		dc.BitBlt(0, 0, rect.Width(), rect.Height(), &m_dcMem, 0, 0, SRCCOPY);
		return;
	}

	//双缓冲
	//CDC dcMem;
	//dcMem.CreateCompatibleDC(&dc);

	//当再次创建表格时，释放前一次的资源
	if (m_pPenOld != NULL)
	{
		m_dcMem.SelectObject(m_pPenOld);
	}

	if (m_pBmpOld != NULL)
	{
		m_dcMem.SelectObject(m_pBmpOld);
	}

	//建立画图区域
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());

	m_pBmpOld = m_dcMem.SelectObject(&bmpMem);

	//把背景设为白色
	m_dcMem.FillSolidRect(0, 0, rect.Width(), rect.Height(), RGB(255, 255, 255));

	//获得表格控件的宽和高
	int nWidth = rect.left - rect.right;
	int nHigh = rect.bottom - rect.top;

	//定义线条颜色
	CPen penNew(PS_SOLID, 1, RGB(79, 129, 189));
	m_pPenOld = m_dcMem.SelectObject(&penNew);

	m_dcMem.SetBkMode(TRANSPARENT);	//设置字体背景为透明！，字体颜色
	m_dcMem.SetTextColor(RGB(79, 129, 189));

	for (int i = 0; i < m_nColumns + 1; i++)
	{
		//画横线
		//区域边缘由于不处于单元格之间，只有1的空隙，需要单独处理
		if (i != m_nColumns)
		{
			m_dcMem.MoveTo(rect.left, rect.top + i*nHigh / m_nColumns);
			m_dcMem.LineTo(rect.right, rect.top + i*nHigh / m_nColumns);
		}
		else
		{
			m_dcMem.MoveTo(rect.left, rect.top + i*nHigh / m_nColumns - 1);
			m_dcMem.LineTo(rect.right, rect.top + i*nHigh / m_nColumns - 1);
		}

		//画竖线
		for (int j = 0; j < m_nRows + 1; j++)
		{
			//线条边框比单元格多1，进行去除
			if (i != 0)
			{
				//区域边缘由于不处于单元格之间，只有1的空隙，需要单独处理
				if (j != m_nRows)
				{
					m_dcMem.MoveTo(rect.left - j*nWidth / m_nRows
						, rect.top + (i - 1)*nHigh / m_nColumns);
					m_dcMem.LineTo(rect.left - j*nWidth / m_nRows
						, rect.top + i * nHigh / m_nColumns);
				}
				else
				{
					m_dcMem.MoveTo(rect.left - j*nWidth / m_nRows - 1
						, rect.top + (i - 1)*nHigh / m_nColumns);
					m_dcMem.LineTo(rect.left - j*nWidth / m_nRows - 1
						, rect.top + i * nHigh / m_nColumns);
				}

				//线条边框比单元格多1，进行去除
				if (j != 0)
				{
					//确定每个单元格区域。针对边界单元格做不同处理
					CRect rectFill;

					if (i < m_nColumns && j < m_nRows)
					{
						rectFill.left = rect.left - (j - 1)*nWidth / m_nRows + 1;
						rectFill.right = rect.left - j*nWidth / m_nRows;

						rectFill.top = rect.top + (i - 1)*nHigh / m_nColumns + 1;
						rectFill.bottom = rect.top + i*nHigh / m_nColumns;
					}
					else if (i == m_nColumns && j != m_nRows)
					{
						rectFill.left = rect.left - (j - 1)*nWidth / m_nRows + 1;
						rectFill.right = rect.left - j*nWidth / m_nRows;

						rectFill.top = rect.top + (i - 1)*nHigh / m_nColumns + 1;
						rectFill.bottom = rect.top + i*nHigh / m_nColumns - 1;
					}
					else if (j == m_nRows && i != m_nColumns)
					{
						rectFill.left = rect.left - (j - 1)*nWidth / m_nRows + 1;
						rectFill.right = rect.left - j*nWidth / m_nRows - 1;

						rectFill.top = rect.top + (i - 1)*nHigh / m_nColumns + 1;
						rectFill.bottom = rect.top + i*nHigh / m_nColumns;
					}
					else if (i == m_nColumns && j == m_nRows)
					{
						rectFill.left = rect.left - (j - 1)*nWidth / m_nRows + 1;
						rectFill.right = rect.left - j*nWidth / m_nRows - 1;

						rectFill.top = rect.top + (i - 1)*nHigh / m_nColumns + 1;
						rectFill.bottom = rect.top + i*nHigh / m_nColumns - 1;
					}
					else
					{
						;
					}

					//为表格填充颜色，奇数行，偶数行填充不同颜色
					if (i % 2 != 0)    //奇数行1，3，5....
					{
						m_dcMem.FillSolidRect(rectFill, RGB(235, 241, 221));
					}
					else if (i % 2 == 0)//偶数行2, 4, 6.....
					{
						m_dcMem.FillSolidRect(rectFill, RGB(219, 238, 243));
					}
					else
					{
						;
					}

					//为每个单元格标号
					char pszNum[10] = { 0 };
					sprintf_s(pszNum, "%d", j + (i - 1)*m_nRows);

					m_dcMem.DrawText(pszNum, rectFill, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
			}
		}//j的for循环结束
	}//i的for循环结束

	//创建结束，之后重绘只是窗口刷新引起的重绘
	m_bRedraw = FALSE;  

	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &m_dcMem, 0, 0, SRCCOPY);

	//m_pDcMem.SelectObject(pPenOld);
	//m_pDcMem.SelectObject(pBmpOld);

	bmpMem.DeleteObject();
	//dcMem.DeleteDC();
}

BOOL CTableCtrl::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void  CTableCtrl::ResetTable(int m, int n)
{
	if (m <= 0 || n <= 0 || m > 100 || n > 100)
	{
		return;
	}

	//主动重设行列值重绘,检验是什么引起的重绘
	m_bRedraw = TRUE;  

	m_nColumns = m;
	m_nRows = n;

	//进行一次重绘，擦除绘图使其无效并发送WM_PAINT消息给程序
	Invalidate();	  
	//UpdateWindow();
}
