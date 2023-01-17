#include <string.h>
#include <windows.h>
#include <iostream>
#include <io.h>
#include <shlwapi.h>
#include <direct.h>
#include "stdafx.h"
#include "DeleteFile.h"

using namespace std;

int main()
{
	TesTRemove();
	return 0;
}

void TesTRemove()
{
	char pszPath[100] = { 0 };
	_getcwd(pszPath, 100);

	char pszDeleteStr[100] = "Debug";

	BOOL bRemoved = RemoveSpecifiedDir(pszPath, pszDeleteStr);

	if (bRemoved)
	{
		cout << "删除成功" << endl;
	}
	else
	{
		cout << "删除失败" << endl;
	}
}

BOOL RemoveSpecifiedDir(LPCTSTR lpszDirPath, LPCTSTR lpszSpecifiedDir)
{
	if (lpszDirPath == NULL || lpszSpecifiedDir == NULL)
	{
		return FALSE;
	}

	struct _finddata_t findData;
	memset(&findData, 0, sizeof(_finddata_t));

	CString szPathFirst(lpszDirPath);

	//确定目录寻找第一个子目录
	intptr_t hFindFile = _findfirst((szPathFirst + "\\*"), &findData);
	if (hFindFile != -1)
	{
		//循环取出目录判断
		do
		{
			//比较文件类型是否为文件夹
			if (findData.attrib == _A_SUBDIR)
			{
				//当前目录的子目录
				CString szPath = lpszDirPath;
				szPath += "\\";
				szPath += findData.name;

				//判断当前目录是否为需要文件包含字符串Debug，如存在则删除
				if (strstr(findData.name,lpszSpecifiedDir) != NULL)
				{
					//删除该文件同时删除其子文件,删除失败返回FALSE
					if (!RmdirALL(szPath))
					{
						_findclose(hFindFile);
						return FALSE;
					}
				}
				else if (strcmp(findData.name, "..") != 0 && strcmp(findData.name, ".") != 0)
				{
					//当前目录存在子文件夹
					//递归实现子目录查找，子目录里存在包含字符串的文件夹，删除失败递归逐级返回FLASE
					if (!RemoveSpecifiedDir(szPath, lpszSpecifiedDir))
					{
						_findclose(hFindFile);
						return FALSE;
					}
				}
				else
				{
					;
				}
			}
		} while (_findnext(hFindFile, &findData) == 0);

		_findclose(hFindFile);
	}

	return TRUE;
}

BOOL RmdirALL(LPCTSTR lpszDirPath)
{
	if (lpszDirPath == NULL)
	{
		return FALSE;
	}

	struct _finddata_t findData;
	memset(&findData, 0, sizeof(_finddata_t));

	CString szPath(lpszDirPath);

	//查找第一个子文件: .
	intptr_t hFindFile = _findfirst((szPath + "\\*"), &findData);
	if (hFindFile != -1)
	{
		do
		{
			//查找子文件，如果为目录则删除目录
			if (findData.attrib == _A_SUBDIR)
			{
				//递归调用删除目录 .和..过滤
				if (strcmp(findData.name, "..") != 0 && strcmp(findData.name, ".") != 0)
				{
					//子目录文件删除失败，逐级返回失败
					if (RmdirALL(szPath + '\\' + findData.name) == FALSE)
					{
						_findclose(hFindFile);
						return FALSE;
					}
				}
			}
			else
			{
				//删除文件,失败返回FALSE
				if (remove((szPath + '\\' + findData.name)) == -1)
				{
					_findclose(hFindFile);
					return FALSE;
				}
			}
		} while (_findnext(hFindFile, &findData) == 0);

		_findclose(hFindFile);
	}

	//删除已经成为空文件夹的文件夹
	if (_rmdir(szPath) == -1)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}
