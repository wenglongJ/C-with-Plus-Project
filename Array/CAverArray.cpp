#include "stdafx.h"
#include "CAverArray.h"

CAverArray::CAverArray(int nLen) : CMyArray(nLen)
{
	;
}

double CAverArray::Average()
{
	if (m_pBuf == NULL)
	{
		return 0;
	}

	double nSum = 0;
	
	for (int i = 0; i < m_nLength; i++)
	{
		nSum += m_pBuf[i];
	}

	return nSum / m_nLength;
}