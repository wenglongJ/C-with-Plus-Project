// C++练习3.cpp : Defines the entry point for the console application.
//

#include <string>
#include <iostream>
#include <assert.h>
#include "stdafx.h"
#include "SplitBuffer.h"

using namespace std;

int main()
{
	TestSplitString();

	getchar();
	return 0;
}

void SplitBufferByZero(LPCTSTR lpBuf, int nBufLen, CStringArray &szaDst)
{
	if (lpBuf == NULL || nBufLen <= 0)
	{
		return;
	}

	CString szBuf;
	int nPos = 0;

	while (nPos < nBufLen)
	{
		if (lpBuf[nPos] == '\0')
		{
			if (!szBuf.IsEmpty())
			{
				szaDst.push_back(szBuf);
				szBuf.Empty();
			}
			nPos++;
		}
		else
		{
			szBuf += lpBuf[nPos++];
		}
	}
}

void PrintCString(const CStringArray &szaDst)
{
	for (auto itrVS = szaDst.begin(); itrVS < szaDst.end(); itrVS++)
	{
		cout << *itrVS << " ";
	}
	cout << endl;
}

void TestSplitString()
{
	CStringArray szaDst;

	//头部有\0
	SplitBufferByZero("\0hello\0world\0I\0love", sizeof("\0hello\0world\0I\0love"), szaDst);
	assert(szaDst.size() == 4);
	PrintCString(szaDst);
	szaDst.clear();

	//存在多个\0分割字符
	SplitBufferByZero("hello\0\0world", sizeof("hello\0\0world"), szaDst);
	assert(szaDst.size() == 2);
	PrintCString(szaDst);
	szaDst.clear();

	//全为\0
	SplitBufferByZero("\0\0\0\0\0", sizeof("\0\0\0\0\0"), szaDst);
	assert(szaDst.size() == 0);
	szaDst.clear();

	//头尾存在大量\0
	SplitBufferByZero("\0\0hello\0\0world\0\0\0", sizeof("\0\0hello\0\0world\0\0\0"), szaDst);
	assert(szaDst.size() == 2);
	PrintCString(szaDst);
	szaDst.clear();

	//以单个\0分割字符
	SplitBufferByZero("hello\0world", sizeof("hello\0world"), szaDst);
	assert(szaDst.size() == 2);
	PrintCString(szaDst);
	szaDst.clear();

	//空字符串
	char pszStr[10] = { 0 };
	SplitBufferByZero(pszStr, sizeof(pszStr), szaDst);
	assert(szaDst.size() == 0);
	szaDst.clear();

	//空指针
	char *pszStrNull = NULL; //空指针指向为空，但其存在地址
	//cout<<&pszStrNull;
	SplitBufferByZero(pszStrNull, 0, szaDst); //sizeof(*pszStrNull)为类型长度1，sizeof(pszStrNull)是指针长度8
	assert(szaDst.size() == 0);
	szaDst.clear();
}

