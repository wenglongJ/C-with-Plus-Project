#pragma once
#include<vector>
#include<Windows.h>

typedef std::vector<std::string> StringArray;

/*
* 功能：拆分字符串函数，对**分割的空字符串默认无效
* 输入：字符串 拆分后存放字符串的位置 分割字符串的字符（非'\0'）
* 输出：返回拆分后的字符串，存放在StringArray中
*/
void SplitString(LPCTSTR lpszSrc, StringArray &szaDst, char c);

//测试函数
void TestSplitString();


