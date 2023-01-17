#pragma once
#ifndef _QINAFX_H
#define _QINAFX_H
//1.首先包含的是afxwin.h，而在afxwin.h中第一个就包含了afx.h.
//2.在afx.h中又包含了afxver_.h，之后就根据编译参数引入导入库：
// Win32 libraries
//
//#ifndef _AFXDLL
//	#ifndef _UNICODE
//		#ifdef _DEBUG
//			#pragma comment(lib, "nafxcwd.lib")
//		#else
//			#pragma comment(lib, "nafxcw.lib")
//		#endif
//	#else
//		#ifdef _DEBUG
//			#pragma comment(lib, "uafxcwd.lib")
//		#else
//			#pragma comment(lib, "uafxcw.lib")
//		#endif
//	#endif
//#else
//	#ifndef _UNICODE
//		#ifdef _DEBUG
//			#pragma comment(lib, "mfc" _MFC_FILENAME_VER "d.lib")
//			#pragma comment(lib, "mfcs" _MFC_FILENAME_VER "d.lib")
//		#else
//			#pragma comment(lib, "mfc" _MFC_FILENAME_VER ".lib")
//			#pragma comment(lib, "mfcs" _MFC_FILENAME_VER ".lib")
//		#endif
//	#else
//		#ifdef _DEBUG
//			#pragma comment(lib, "mfc" _MFC_FILENAME_VER "ud.lib")
//			#pragma comment(lib, "mfcs" _MFC_FILENAME_VER "ud.lib")
//		#else
//			#pragma comment(lib, "mfc" _MFC_FILENAME_VER "u.lib")
//			#pragma comment(lib, "mfcs" _MFC_FILENAME_VER "u.lib")
//		#endif
//	#endif
//#endif
//
//#ifdef _DLL
//	#if !defined(_AFX_NO_DEBUG_CRT) && defined(_DEBUG)
//		#pragma comment(lib, "msvcrtd.lib")
//	#else
//		#pragma comment(lib, "msvcrt.lib")
//	#endif
//#else
//	#if !defined(_AFX_NO_DEBUG_CRT) && defined(_DEBUG)
//		#pragma comment(lib, "libcmtd.lib")
//	#else
//		#pragma comment(lib, "libcmt.lib")
//	#endif
//#endif
//  #pragma comment(lib, "kernel32.lib")
//  #pragma comment(lib, "user32.lib")
//  #pragma comment(lib, "gdi32.lib")
//  #pragma comment(lib, "msimg32.lib")
//  #pragma comment(lib, "comdlg32.lib")
//  #pragma comment(lib, "winspool.lib")
//  #pragma comment(lib, "advapi32.lib")
//  #pragma comment(lib, "shell32.lib")
//  #pragma comment(lib, "comctl32.lib")
//  #pragma comment(lib, "shlwapi.lib")
// 接着，添加了CObject、CRuntimeClass、CException、CFile等几个关键类的前向声明.
//3.在afxver_.h中，又包含了afxv_w32.h
//4.在afxv_w32.h中，包含了windows.h
#include<afxwin.h>
#endif