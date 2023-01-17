
// C++Á·Ï°4MFCone.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFConeApp:
// See C++Á·Ï°4MFCone.cpp for the implementation of this class
//

class CMFConeApp : public CWinApp
{
public:
	CMFConeApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFConeApp theApp;