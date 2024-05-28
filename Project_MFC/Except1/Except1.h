// Except1.h : main header file for the Except1 DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CExcept1App
// See Except1.cpp for the implementation of this class
//

class CExcept1App : public CWinApp
{
public:
	CExcept1App();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
