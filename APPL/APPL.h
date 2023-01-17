
// APPL.h : main header file for the APPL application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CAPPLApp:
// See APPL.cpp for the implementation of this class
//

class CAPPLApp : public CWinAppEx
{
public:
	CAPPLApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CAPPLApp theApp;
