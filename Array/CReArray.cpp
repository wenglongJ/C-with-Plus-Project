#include "stdafx.h"
#include "CReArray.h"
#include <iostream>

using namespace std;

CReArray::CReArray(int nLen) : CMyArray(nLen)
{
	;
}

void CReArray::Reserve()
{
	if (m_pBuf == NULL)
	{
		return;
	}

	int nLeft = 0;
	int nRight = m_nLength - 1;

	while (nLeft < nRight)
	{
		int nTemp = m_pBuf[nLeft];
		m_pBuf[nLeft] = m_pBuf[nRight];
		m_pBuf[nRight] = nTemp;

		nLeft++;
		nRight--;
	}
}