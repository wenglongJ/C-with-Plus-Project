#include "stdafx.h"
#include "CMyArray.h"
#include <windows.h>
#include <iostream>

using namespace std;

CMyArray::CMyArray(int nLen)
{
	if (nLen <= 0)
	{
		m_pBuf = NULL;
		m_nLength = 0;
		return;
	}

	m_pBuf = new int[nLen];
	m_nLength = nLen;
}

CMyArray::~CMyArray()
{
	if (m_pBuf != NULL)
	{
		delete[] m_pBuf;
	}
}
void CMyArray::Input()
{
	cout << "请依次输入" << m_nLength << "个整数：" << endl;

	int nGetCin;
	int nPos = 0;

	while (nPos < m_nLength)
	{
		cin >> nGetCin;
		if (cin.fail())
		{
			cin.clear();
			cin.get();
		}
		else
		{
			m_pBuf[nPos] = nGetCin;
			nPos++;
		}
	}
}
void CMyArray::Display()
{
	cout << "数组中元素为：";
	for (int i = 0; i < m_nLength; i++)
	{
		cout << m_pBuf[i] << " ";
	}
	cout << endl;
}