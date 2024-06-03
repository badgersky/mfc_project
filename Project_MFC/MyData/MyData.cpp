// MyData.cpp : Defines the initialization routines for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "MyData.h"

#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

// CMyDataApp

BEGIN_MESSAGE_MAP(CMyDataApp, CWinApp)
END_MESSAGE_MAP()

// CMyDataApp construction

CMyDataApp::CMyDataApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CMyDataApp object

CMyDataApp theApp;

// CMyDataApp initialization

BOOL CMyDataApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

MyPoint* MyData::allocTab(MyPoint* pTab, int n) {
	try 
	{
		if (!pTab)
		{
			pTab = new MyPoint[n];
			capacity = n;
			return pTab;
		}
	}
	catch (std::bad_alloc)
	{
		//pExcept->PutMessage(1003);
	}
}

MyData::MyData(int no_it) noexcept
{
	//pExcept = GetExceptPtr();
	pTab = NULL;
	Init(no_it);
}

MyData::MyData(const MyData& ob) {
	capacity = ob.capacity;
	last = ob.last;
	pTab = NULL;
	pTab = allocTab(pTab, capacity);
	if (pTab) std::copy(ob.pTab, ob.pTab + last, pTab);
}

void MyData::Init(int no_it)
{
	capacity = no_it;
	last = 0;
	pTab = allocTab(pTab, capacity);
}

void MyData::Push(const MyPoint& point)
{
	if (last >= capacity)
	{
		int delta = last - capacity;
		int new_capacity = 0;
		if (delta > capacity)
		{
			new_capacity = delta + capacity;
		}
		else
		{
			new_capacity = 2 * capacity;
		}

		int old_capacity(capacity);
		MyPoint* newTab(NULL);
		newTab = allocTab(newTab, new_capacity);
		std::copy(pTab, pTab + old_capacity, newTab);
		delete[] pTab;
		pTab = newTab;
	}

	pTab[last++] = point;
}

void MyData::GetMaxMinCoords(double& max_x, double& min_x, double& max_y, double& min_y)
{
	max_x = min_x = max_y = min_y = 0;
	if (pTab && last)
	{
		max_x = min_x = pTab[0].x;
		max_y = min_y = pTab[0].y;

		for (int i = 1; i < last; ++i)
		{
			if (pTab[i].x > max_x)
				max_x = pTab[i].x;
			if (pTab[i].y > max_y)
				max_y = pTab[i].y;
			if (pTab[i].x < min_x)
				min_x = pTab[i].x;
			if (pTab[i].y < min_y)
				min_y = pTab[i].y;
		}
	}
}
