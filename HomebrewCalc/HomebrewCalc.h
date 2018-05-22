
// HomebrewCalc.h : main header file for the HomebrewCalc application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CHomebrewCalcApp:
// See HomebrewCalc.cpp for the implementation of this class
//

class CHomebrewCalcApp : public CWinApp
{
public:
	CHomebrewCalcApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CHomebrewCalcApp theApp;
