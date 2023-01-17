#pragma once

#include <vector>
#include <array>
#include <windows.h>
#include <atlstr.h>

typedef std::vector<CString> CStringArray;

//typedef std::array<CString,100> CStringArray;

/*
* 功能：拆分字符串函数
* 输入：字符串 拆分后存放字符串的位置 分割字符串的字符（非'\0'）
* 输出：返回拆分后的字符串，存放在StringArray中
*/
void SplitBufferByZero(LPCTSTR lpBuf, int nBufLen, CStringArray &szaDst);

//测试函数
void TestSplitString();

//打印容器内容
void PrintCString(const CStringArray &vctCString);