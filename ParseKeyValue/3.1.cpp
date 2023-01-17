#include <iostream>
#include <map>
#include <assert.h>
#include <string.h>

using namespace std;

//key����Ϊ�գ�value����Ϊ��.�ظ�key������
void ParseKeyValues(const char *pszSrc, std::map<std::string, std::string> &mapDst);

void Test();

int main()
{
	Test();

	getchar();
	return 0;
}

void ParseKeyValues(const char *pszSrc, std::map<std::string, std::string> &mapDst)
{
	if (pszSrc == NULL)
	{
		return;
	}

	mapDst.clear();

	int nSrcLen = strlen(pszSrc);
	int nLen = 0;

	bool bStatus = false;
	string strKey;
	string strValue;

	while (nLen < nSrcLen + 1)
	{
		if (pszSrc[nLen] == '&' || pszSrc[nLen] == '\0')
		{
			if (!strKey.empty())
			{
				//����key������key
				if (mapDst.find(strKey) != mapDst.end())
				{
					mapDst[strKey] = strValue;
				}

				mapDst.insert(make_pair(strKey, strValue));
			}

			strKey.clear();
			strValue.clear();
			bStatus = false;
		}
		else
		{
			if (pszSrc[nLen] == '=')
			{
				bStatus = true;
				nLen++;
				continue;
			}

			if (bStatus)
			{
				strValue += pszSrc[nLen];
			}
			else
			{
				strKey += pszSrc[nLen];
			}
		}

	nLen++;
	}
}

void Test()
{
	std::map<std::string, std::string> mapDst;

	//ͷ����\0
	ParseKeyValues("\0key1=value1&key2=value2", mapDst);
	assert(mapDst.size() == 0);
	mapDst.clear();

	//���ڶ��&�ָ�
	ParseKeyValues("key1=value1&&key2=value2", mapDst);
	assert(mapDst.size() == 2);
	mapDst.clear();

	//����
	ParseKeyValues("key1=value1&key2=value2", mapDst);
	assert(mapDst.size() == 2);
	mapDst.clear();

	//һ��
	ParseKeyValues("key1=value1", mapDst);
	assert(mapDst.size() == 1);
	mapDst.clear();

	//�ظ�
	ParseKeyValues("key1=value1&key1=value2", mapDst);
	assert(mapDst.size() == 1);
	mapDst.clear();

	//ȫΪ&&&
	ParseKeyValues("&&&&&&&&&&", mapDst);
	assert(mapDst.size() == 0);
	mapDst.clear();

	//keyΪ��
	ParseKeyValues("=value1&key2=value2", mapDst);
	assert(mapDst.size() == 1);
	mapDst.clear();

	//valueΪ��
	ParseKeyValues("key1=&key2=value2", mapDst);
	assert(mapDst.size() == 2);
	mapDst.clear();

	//ͷβ���ڴ���&
	ParseKeyValues("&&key1=value1&key2=value2&&", mapDst);
	assert(mapDst.size() == 2);
	mapDst.clear();

	//���ַ���
	char pszStr[10] = { 0 };
	ParseKeyValues(pszStr, mapDst);
	assert(mapDst.size() == 0);
	mapDst.clear();

	//��ָ��
	char *pszStrNull = NULL; //��ָ��ָ��Ϊ�գ�������ڵ�ַ
							 //cout<<&pszStrNull;
	ParseKeyValues(pszStrNull, mapDst);
	assert(mapDst.size() == 0);
	mapDst.clear();
}           