#pragma once
#ifndef _QINAFX_H
#define _QINAFX_H
//1.���Ȱ�������afxwin.h������afxwin.h�е�һ���Ͱ�����afx.h.
//2.��afx.h���ְ�����afxver_.h��֮��͸��ݱ���������뵼��⣺
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
// ���ţ������CObject��CRuntimeClass��CException��CFile�ȼ����ؼ����ǰ������.
//3.��afxver_.h�У��ְ�����afxv_w32.h
//4.��afxv_w32.h�У�������windows.h
#include<afxwin.h>
#endif