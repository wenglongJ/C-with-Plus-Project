
// C++Á·Ï°5MFCtwo.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCtwoApp:
// See C++Á·Ï°5MFCtwo.cpp for the implementation of this class
//

class CMFCtwoApp : public CWinApp
{
public:
	CMFCtwoApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCtwoApp theApp;