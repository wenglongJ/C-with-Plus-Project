#pragma once

#include "resource.h"

#pragma once

#include <windows.h>
#include <atltypes.h>
#include <tchar.h>

//资源ID
#define ID_BUTTON_DRAW      10000
#define ID_BUTTON_SWEEP     10001

// 注册窗口类
ATOM AppRegisterClass(HINSTANCE hInstance);
// 初始化窗口
BOOL InitInstance(HINSTANCE, int);
// 消息处理函数(又叫窗口过程)
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
// (白色背景)按钮事件
void OnButtonWhite();
// (灰色背景)按钮事件
void OnButtonGray();
// 绘制事件
//void OnDraw(HDC hdc);