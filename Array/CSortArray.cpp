#include "stdafx.h"
#include "CSortArray.h"
#include <iostream>

using namespace std;

CSortArray::CSortArray(int nLen) : CMyArray(nLen)
{
	;
}

void CSortArray::Sort()
{
	if (m_pBuf == NULL)
	{
		return;
	}

	for (int i = 0; i < m_nLength - 1; i++)
	{
		for (int j = i + 1; j < m_nLength; j++)
		{
			if (m_pBuf[i] < m_pBuf[j])
			{
				int nTemp = m_pBuf[i];
				m_pBuf[i] = m_pBuf[j];
				m_pBuf[j] = nTemp;
			}
		}
	}
}