#pragma once
#include <windows.h>

class CString
{
public:
	CString(const char *pszString = NULL);
	CString(const CString &szOther);
	~CString();
	CString & operator=(const CString &szOther);

private:
	char* m_pData;
};