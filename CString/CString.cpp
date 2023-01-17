#include <stdio.h>
#include <iostream>
#include "CString.h"

#pragma warning(disable : 4996)
using namespace std;

CString::CString(const char *pszString)
{
	if (pszString == NULL)
	{
		m_pData = new char[1];
		*m_pData = '\0';
	}
	else
	{
		int nLength = strlen(pszString);
		m_pData = new char[nLength + 1];
		if (m_pData == NULL)
		{
			return;
		}

		strcpy(m_pData, pszString);
	}
}

CString::CString(const CString &szOther)
{
	int nLength = strlen(szOther.m_pData);
	m_pData = new char[nLength + 1];
	if (m_pData == NULL)
	{
		return;
	}

	strcpy(m_pData, szOther.m_pData);
}

CString::~CString()
{
	if (m_pData != NULL)
	{
		delete[] m_pData;
	}
}

CString & CString::operator=(const CString &szOther)
{
	if (this == &szOther) //¼ì²â×ÔÎÒ¸´Öµ
	{
		return *this;
	}

	delete[] m_pData;

	int nLength = strlen(szOther.m_pData);
	m_pData = new char[nLength + 1];
	if (m_pData == NULL)
	{
		return *this;
	}

	strcpy(m_pData, szOther.m_pData);
	return *this;
}