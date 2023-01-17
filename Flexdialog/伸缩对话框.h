
// 伸缩对话框.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// C伸缩对话框App:
// See 伸缩对话框.cpp for the implementation of this class
//

class C伸缩对话框App : public CWinApp
{
public:
	C伸缩对话框App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern C伸缩对话框App theApp;