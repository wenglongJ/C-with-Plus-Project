#pragma once
#include<vector>
#include<Windows.h>

typedef std::vector<std::string> StringArray;

/*
* ���ܣ�����ַ�����������**�ָ�Ŀ��ַ���Ĭ����Ч
* ���룺�ַ��� ��ֺ����ַ�����λ�� �ָ��ַ������ַ�����'\0'��
* ��������ز�ֺ���ַ����������StringArray��
*/
void SplitString(LPCTSTR lpszSrc, StringArray &szaDst, char c);

//���Ժ���
void TestSplitString();


