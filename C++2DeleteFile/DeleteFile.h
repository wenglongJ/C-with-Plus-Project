#pragma once

#include<string>
#include<windows.h>

/*
* ���ܣ�ɾ��ָ��Ŀ¼�µģ����ư���ָ���ַ����ĵ�Ŀ¼
* ���룺ָ��Ŀ¼��ָ���ַ���
* �����ɾ���ɹ�
*/
BOOL RemoveSpecifiedDir(LPCTSTR lpszDirPath, LPCTSTR lpszSpecifiedDir);

//ɾ���ļ��е������ļ�
BOOL RmdirALL(LPCTSTR lpszDirPath);

//��ȡ��ǰ�ļ�·��ɾ��Debug
void TesTRemove();

