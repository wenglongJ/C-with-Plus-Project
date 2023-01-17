
// Parent.h : main header file for the Parent application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CParentApp:
// See Parent.cpp for the implementation of this class
//

class CParentApp : public CWinApp
{
public:
	CParentApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CParentApp theApp;
