
// C++Á·Ï°MFCthree.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CthreeApp:
// See C++Á·Ï°MFCthree.cpp for the implementation of this class
//

class CThreeApp : public CWinApp
{
public:
	CThreeApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CThreeApp theApp;