// C++��ϰ3.cpp : Defines the entry point for the console application.
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

	//ͷ����\0
	SplitBufferByZero("\0hello\0world\0I\0love", sizeof("\0hello\0world\0I\0love"), szaDst);
	assert(szaDst.size() == 4);
	PrintCString(szaDst);
	szaDst.clear();

	//���ڶ��\0�ָ��ַ�
	SplitBufferByZero("hello\0\0world", sizeof("hello\0\0world"), szaDst);
	assert(szaDst.size() == 2);
	PrintCString(szaDst);
	szaDst.clear();

	//ȫΪ\0
	SplitBufferByZero("\0\0\0\0\0", sizeof("\0\0\0\0\0"), szaDst);
	assert(szaDst.size() == 0);
	szaDst.clear();

	//ͷβ���ڴ���\0
	SplitBufferByZero("\0\0hello\0\0world\0\0\0", sizeof("\0\0hello\0\0world\0\0\0"), szaDst);
	assert(szaDst.size() == 2);
	PrintCString(szaDst);
	szaDst.clear();

	//�Ե���\0�ָ��ַ�
	SplitBufferByZero("hello\0world", sizeof("hello\0world"), szaDst);
	assert(szaDst.size() == 2);
	PrintCString(szaDst);
	szaDst.clear();

	//���ַ���
	char pszStr[10] = { 0 };
	SplitBufferByZero(pszStr, sizeof(pszStr), szaDst);
	assert(szaDst.size() == 0);
	szaDst.clear();

	//��ָ��
	char *pszStrNull = NULL; //��ָ��ָ��Ϊ�գ�������ڵ�ַ
	//cout<<&pszStrNull;
	SplitBufferByZero(pszStrNull, 0, szaDst); //sizeof(*pszStrNull)Ϊ���ͳ���1��sizeof(pszStrNull)��ָ�볤��8
	assert(szaDst.size() == 0);
	szaDst.clear();
}

