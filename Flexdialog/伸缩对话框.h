
// �����Ի���.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// C�����Ի���App:
// See �����Ի���.cpp for the implementation of this class
//

class C�����Ի���App : public CWinApp
{
public:
	C�����Ի���App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern C�����Ի���App theApp;