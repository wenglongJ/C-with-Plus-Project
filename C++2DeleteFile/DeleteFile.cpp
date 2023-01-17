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
		cout << "ɾ���ɹ�" << endl;
	}
	else
	{
		cout << "ɾ��ʧ��" << endl;
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

	//ȷ��Ŀ¼Ѱ�ҵ�һ����Ŀ¼
	intptr_t hFindFile = _findfirst((szPathFirst + "\\*"), &findData);
	if (hFindFile != -1)
	{
		//ѭ��ȡ��Ŀ¼�ж�
		do
		{
			//�Ƚ��ļ������Ƿ�Ϊ�ļ���
			if (findData.attrib == _A_SUBDIR)
			{
				//��ǰĿ¼����Ŀ¼
				CString szPath = lpszDirPath;
				szPath += "\\";
				szPath += findData.name;

				//�жϵ�ǰĿ¼�Ƿ�Ϊ��Ҫ�ļ������ַ���Debug���������ɾ��
				if (strstr(findData.name,lpszSpecifiedDir) != NULL)
				{
					//ɾ�����ļ�ͬʱɾ�������ļ�,ɾ��ʧ�ܷ���FALSE
					if (!RmdirALL(szPath))
					{
						_findclose(hFindFile);
						return FALSE;
					}
				}
				else if (strcmp(findData.name, "..") != 0 && strcmp(findData.name, ".") != 0)
				{
					//��ǰĿ¼�������ļ���
					//�ݹ�ʵ����Ŀ¼���ң���Ŀ¼����ڰ����ַ������ļ��У�ɾ��ʧ�ܵݹ��𼶷���FLASE
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

	//���ҵ�һ�����ļ�: .
	intptr_t hFindFile = _findfirst((szPath + "\\*"), &findData);
	if (hFindFile != -1)
	{
		do
		{
			//�������ļ������ΪĿ¼��ɾ��Ŀ¼
			if (findData.attrib == _A_SUBDIR)
			{
				//�ݹ����ɾ��Ŀ¼ .��..����
				if (strcmp(findData.name, "..") != 0 && strcmp(findData.name, ".") != 0)
				{
					//��Ŀ¼�ļ�ɾ��ʧ�ܣ��𼶷���ʧ��
					if (RmdirALL(szPath + '\\' + findData.name) == FALSE)
					{
						_findclose(hFindFile);
						return FALSE;
					}
				}
			}
			else
			{
				//ɾ���ļ�,ʧ�ܷ���FALSE
				if (remove((szPath + '\\' + findData.name)) == -1)
				{
					_findclose(hFindFile);
					return FALSE;
				}
			}
		} while (_findnext(hFindFile, &findData) == 0);

		_findclose(hFindFile);
	}

	//ɾ���Ѿ���Ϊ���ļ��е��ļ���
	if (_rmdir(szPath) == -1)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}
