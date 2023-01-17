#pragma once

#include <vector>
#include <array>
#include <windows.h>
#include <atlstr.h>

typedef std::vector<CString> CStringArray;

//typedef std::array<CString,100> CStringArray;

/*
* ���ܣ�����ַ�������
* ���룺�ַ��� ��ֺ����ַ�����λ�� �ָ��ַ������ַ�����'\0'��
* ��������ز�ֺ���ַ����������StringArray��
*/
void SplitBufferByZero(LPCTSTR lpBuf, int nBufLen, CStringArray &szaDst);

//���Ժ���
void TestSplitString();

//��ӡ��������
void PrintCString(const CStringArray &vctCString);