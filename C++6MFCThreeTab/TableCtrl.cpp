#include "stdafx.h"
#include "TableCtrl.h"

//Ĭ���Ǹ�3����3����������������
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

	//��һ�γ�ʼ������m_pDcMem
	if (m_dcMem.m_hDC == NULL)
	{
		m_dcMem.CreateCompatibleDC(&dc);
	}

	//����ˢ��������ػ�,��ֹ�ٴλ�ͼ���𿨶�
	if (!m_bRedraw)
	{
		dc.BitBlt(0, 0, rect.Width(), rect.Height(), &m_dcMem, 0, 0, SRCCOPY);
		return;
	}

	//˫����
	//CDC dcMem;
	//dcMem.CreateCompatibleDC(&dc);

	//���ٴδ������ʱ���ͷ�ǰһ�ε���Դ
	if (m_pPenOld != NULL)
	{
		m_dcMem.SelectObject(m_pPenOld);
	}

	if (m_pBmpOld != NULL)
	{
		m_dcMem.SelectObject(m_pBmpOld);
	}

	//������ͼ����
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());

	m_pBmpOld = m_dcMem.SelectObject(&bmpMem);

	//�ѱ�����Ϊ��ɫ
	m_dcMem.FillSolidRect(0, 0, rect.Width(), rect.Height(), RGB(255, 255, 255));

	//��ñ��ؼ��Ŀ�͸�
	int nWidth = rect.left - rect.right;
	int nHigh = rect.bottom - rect.top;

	//����������ɫ
	CPen penNew(PS_SOLID, 1, RGB(79, 129, 189));
	m_pPenOld = m_dcMem.SelectObject(&penNew);

	m_dcMem.SetBkMode(TRANSPARENT);	//�������屳��Ϊ͸������������ɫ
	m_dcMem.SetTextColor(RGB(79, 129, 189));

	for (int i = 0; i < m_nColumns + 1; i++)
	{
		//������
		//�����Ե���ڲ����ڵ�Ԫ��֮�䣬ֻ��1�Ŀ�϶����Ҫ��������
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

		//������
		for (int j = 0; j < m_nRows + 1; j++)
		{
			//�����߿�ȵ�Ԫ���1������ȥ��
			if (i != 0)
			{
				//�����Ե���ڲ����ڵ�Ԫ��֮�䣬ֻ��1�Ŀ�϶����Ҫ��������
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

				//�����߿�ȵ�Ԫ���1������ȥ��
				if (j != 0)
				{
					//ȷ��ÿ����Ԫ��������Ա߽絥Ԫ������ͬ����
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

					//Ϊ��������ɫ�������У�ż������䲻ͬ��ɫ
					if (i % 2 != 0)    //������1��3��5....
					{
						m_dcMem.FillSolidRect(rectFill, RGB(235, 241, 221));
					}
					else if (i % 2 == 0)//ż����2, 4, 6.....
					{
						m_dcMem.FillSolidRect(rectFill, RGB(219, 238, 243));
					}
					else
					{
						;
					}

					//Ϊÿ����Ԫ����
					char pszNum[10] = { 0 };
					sprintf_s(pszNum, "%d", j + (i - 1)*m_nRows);

					m_dcMem.DrawText(pszNum, rectFill, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
			}
		}//j��forѭ������
	}//i��forѭ������

	//����������֮���ػ�ֻ�Ǵ���ˢ��������ػ�
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

	//������������ֵ�ػ�,������ʲô������ػ�
	m_bRedraw = TRUE;  

	m_nColumns = m;
	m_nRows = n;

	//����һ���ػ棬������ͼʹ����Ч������WM_PAINT��Ϣ������
	Invalidate();	  
	//UpdateWindow();
}
