#include <iostream>
#include <map>
#include <assert.h>
#include <string.h>

using namespace std;

//key不能为空，value允许为空.重复key将更新
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
				//存在key，更新key
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

	//头部有\0
	ParseKeyValues("\0key1=value1&key2=value2", mapDst);
	assert(mapDst.size() == 0);
	mapDst.clear();

	//存在多个&分割
	ParseKeyValues("key1=value1&&key2=value2", mapDst);
	assert(mapDst.size() == 2);
	mapDst.clear();

	//正常
	ParseKeyValues("key1=value1&key2=value2", mapDst);
	assert(mapDst.size() == 2);
	mapDst.clear();

	//一个
	ParseKeyValues("key1=value1", mapDst);
	assert(mapDst.size() == 1);
	mapDst.clear();

	//重复
	ParseKeyValues("key1=value1&key1=value2", mapDst);
	assert(mapDst.size() == 1);
	mapDst.clear();

	//全为&&&
	ParseKeyValues("&&&&&&&&&&", mapDst);
	assert(mapDst.size() == 0);
	mapDst.clear();

	//key为空
	ParseKeyValues("=value1&key2=value2", mapDst);
	assert(mapDst.size() == 1);
	mapDst.clear();

	//value为空
	ParseKeyValues("key1=&key2=value2", mapDst);
	assert(mapDst.size() == 2);
	mapDst.clear();

	//头尾存在大量&
	ParseKeyValues("&&key1=value1&key2=value2&&", mapDst);
	assert(mapDst.size() == 2);
	mapDst.clear();

	//空字符串
	char pszStr[10] = { 0 };
	ParseKeyValues(pszStr, mapDst);
	assert(mapDst.size() == 0);
	mapDst.clear();

	//空指针
	char *pszStrNull = NULL; //空指针指向为空，但其存在地址
							 //cout<<&pszStrNull;
	ParseKeyValues(pszStrNull, mapDst);
	assert(mapDst.size() == 0);
	mapDst.clear();
}           