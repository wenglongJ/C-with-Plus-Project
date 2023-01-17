#include<iostream>
#include<assert.h>
#include"SplitString.h"

using namespace std;

void SplitString(LPCTSTR lpszSrc, StringArray &szaDst, char c)
{
	//��\0�ָ�
	if (lpszSrc == NULL || c == '\0')
	{
		return;
	}

	string strStr;

	//����ͷ������c
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

	//β�����*ʱ�������ַ���,У��֮�����
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

	//����һ���ַ�����*�ŷָ�
	SplitString("aduas*bhasdf*asbd*asdasd", vctStr, '*');
	assert(vctStr.size() == 4);
	PrintString(vctStr);
	vctStr.clear();

	//����һ���ַ�����*�ŷָ������ѷָ�������ó���,��
	SplitString("aduas*bhasdf*asbd*asdasd", vctStr, ',');
	assert(vctStr.size() == 1);

	PrintString(vctStr);
	vctStr.clear();

	//����һ���ַ�����*�ŷָͷ����β�����ڶ��*
	SplitString("****aduas*bhasdf*asbd*asdasd****", vctStr, '*');
	assert(vctStr.size() == 4);
	PrintString(vctStr);
	vctStr.clear();

	//�Զ��***�ָ�
	SplitString("*aduas***bhasdf**asbd**asdasd", vctStr, '*');
	assert(vctStr.size() == 4);
	PrintString(vctStr);
	vctStr.clear();

	//�������'\0'��Ϊ�ָ��
	SplitString("hello\0world", vctStr, '\0');
	assert(vctStr.size() == 0);
	vctStr.clear();

	//ȫ��Ϊ*
	SplitString("********", vctStr, '*');
	assert(vctStr.size() == 0);
	vctStr.clear();

	//���ַ���
	char pszStr[10] = { 0 };
	SplitString(pszStr, vctStr, '*');
	assert(vctStr.size() == 0);
	vctStr.clear();

	//��ָ��
	char *pszStrNull = NULL;
	SplitString(pszStr, vctStr, '*');
	assert(vctStr.size() == 0);
	vctStr.clear();
}

//�ڶ���ʵ��
/*void SplitString(LPCTSTR lpszSrc, StringArray &szaDst, char c)
{
	//��\0�ָ�
	if (lpszSrc == NULL || c == '\0')
	{
		return;
	}

	string strStr;

	//����ͷ������c
	LPCTSTR lpszHead = lpszSrc;

	while (*lpszHead != '\0')
	{
		if (*lpszHead == c)
		{
			//ͷ��һ��c
			if (lpszSrc == lpszHead)
			{
				//ͷ�����ڶ��c
				while (*lpszHead == c)
				{
					lpszHead++;
				}
				continue;
			}

			szaDst.push_back(strStr);
			strStr.clear();

			//�Զ��c���ŷָȡ������c
			while (*lpszHead == c)
			{
				lpszHead++;
			}
		}

		//��β������c�ַ�ʱ���ڲ�while�Ѿ�ȡ��c����\0,��ֹ�ظ�++Խ��
		if (*lpszHead != '\0')
		{
			strStr += *lpszHead++;
		}
	}

	//β�����*ʱ�������ַ���,У��֮�����
	if (!strStr.empty())
	{
		szaDst.push_back(strStr);
	}
}
*/
