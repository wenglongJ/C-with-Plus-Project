#pragma once

#include<string>
#include<windows.h>

/*
* 功能：删除指定目录下的，名称包含指定字符串的的目录
* 输入：指定目录，指定字符串
* 输出：删除成功
*/
BOOL RemoveSpecifiedDir(LPCTSTR lpszDirPath, LPCTSTR lpszSpecifiedDir);

//删除文件夹的所有文件
BOOL RmdirALL(LPCTSTR lpszDirPath);

//获取当前文件路径删除Debug
void TesTRemove();

