
// Additions.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CAdditionsApp: 
// �йش����ʵ�֣������ Additions.cpp
//

class CAdditionsApp : public CWinApp
{
public:
	CAdditionsApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CAdditionsApp theApp;