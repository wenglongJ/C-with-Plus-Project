#include<iostream>
#include<assert.h>
#include"SplitString.h"

using namespace std;

void SplitString(LPCTSTR lpszSrc, StringArray &szaDst, char c)
{
	//以\0分割
	if (lpszSrc == NULL || c == '\0')
	{
		return;
	}

	string strStr;

	//检验头部出现c
	LPCTSTR lpszPStr = lpszSrc;

	while (*lpszPStr != '\0')
	{
		if (*lpszPStr == c)
		{
			if (!strStr.empty())
			{
				szaDst.push_back(strStr);
				strStr.clear();
			}
			lpszPStr ++;
		}
		else
		{
			strStr += *lpszPStr++;
		}
	}

	//尾部多个*时产生空字符串,校验之后插入
	if (!strStr.empty())
	{
		szaDst.push_back(strStr);
	}
}

void PrintString(const StringArray &vctString)
{
	for (auto itrVS = vctString.begin(); itrVS < vctString.end(); itrVS++)
	{
		cout << itrVS->c_str() << endl;
	}
}

void TestSplitString()
{
	StringArray vctStr;

	//输入一个字符串以*号分割
	SplitString("aduas*bhasdf*asbd*asdasd", vctStr, '*');
	assert(vctStr.size() == 4);
	PrintString(vctStr);
	vctStr.clear();

	//输入一个字符串以*号分割，但错误把分割符号设置成立,号
	SplitString("aduas*bhasdf*asbd*asdasd", vctStr, ',');
	assert(vctStr.size() == 1);

	PrintString(vctStr);
	vctStr.clear();

	//输入一个字符串以*号分割，头部或尾部存在多个*
	SplitString("****aduas*bhasdf*asbd*asdasd****", vctStr, '*');
	assert(vctStr.size() == 4);
	PrintString(vctStr);
	vctStr.clear();

	//以多个***分割
	SplitString("*aduas***bhasdf**asbd**asdasd", vctStr, '*');
	assert(vctStr.size() == 4);
	PrintString(vctStr);
	vctStr.clear();

	//错误的以'\0'做为分割符
	SplitString("hello\0world", vctStr, '\0');
	assert(vctStr.size() == 0);
	vctStr.clear();

	//全部为*
	SplitString("********", vctStr, '*');
	assert(vctStr.size() == 0);
	vctStr.clear();

	//空字符串
	char pszStr[10] = { 0 };
	SplitString(pszStr, vctStr, '*');
	assert(vctStr.size() == 0);
	vctStr.clear();

	//空指针
	char *pszStrNull = NULL;
	SplitString(pszStr, vctStr, '*');
	assert(vctStr.size() == 0);
	vctStr.clear();
}

//第二种实现
/*void SplitString(LPCTSTR lpszSrc, StringArray &szaDst, char c)
{
	//以\0分割
	if (lpszSrc == NULL || c == '\0')
	{
		return;
	}

	string strStr;

	//检验头部出现c
	LPCTSTR lpszHead = lpszSrc;

	while (*lpszHead != '\0')
	{
		if (*lpszHead == c)
		{
			//头部一个c
			if (lpszSrc == lpszHead)
			{
				//头部存在多个c
				while (*lpszHead == c)
				{
					lpszHead++;
				}
				continue;
			}

			szaDst.push_back(strStr);
			strStr.clear();

			//以多个c符号分割，取出所有c
			while (*lpszHead == c)
			{
				lpszHead++;
			}
		}

		//当尾部存在c字符时，内部while已经取出c到达\0,防止重复++越界
		if (*lpszHead != '\0')
		{
			strStr += *lpszHead++;
		}
	}

	//尾部多个*时产生空字符串,校验之后插入
	if (!strStr.empty())
	{
		szaDst.push_back(strStr);
	}
}
*/
