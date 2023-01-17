
// WORD.h : main header file for the WORD application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CWORDApp:
// See WORD.cpp for the implementation of this class
//

class CWORDApp : public CWinAppEx
{
public:
	CWORDApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CWORDApp theApp;
