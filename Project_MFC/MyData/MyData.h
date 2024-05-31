// MyData.h : main header file for the MyData DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "Except1.h"

#ifdef MY_DATA_EXPORTS
#define MyDataAPI __declspec(dllexport)
#else
#define MyDataAPI __declspec(dllexport)
#endif //MY_DATA_EXPORTS


// CMyDataApp
// See MyData.cpp for the implementation of this class
//

class CMyDataApp : public CWinApp
{
public:
	CMyDataApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

class MyDataAPI MyPoint
{
public:
	double x;
	double y;
	CString name;
	COLORREF color;
public:
	MyPoint() : x(0), y(0), color(RGB(0, 0, 0)), name("vertex") {}
	MyPoint(double xx, double yy, COLORREF new_color, CString new_name) : x(xx), y(yy), color(new_color), name(new_name) {}
	~MyPoint() {}
	void set(double xx, double yy, COLORREF new_color, CString new_name) { x = xx; y = yy; color = new_color; name = new_name; }
	MyPoint get() { return *this; }
	COLORREF get_color() { return color; }
};

class MyDataAPI MyData : public MyPoint
{
protected:
	MyPoint* pTab;
	int capacity;
	int last;
public:
	MyData(int no_it) noexcept;
	MyData(const MyData& ob);
	~MyData() { Free(); }
	int size() { return last; }
	void Free() { if (pTab) delete[] pTab; pTab = NULL; }
	void Init(int no_it);
	void Push(const MyPoint& point);
	void clear() { last = 0; }
	void MyData::GetMaxMinCoords(double& max_x, double& min_x, double& max_y, double& min_y);

	CExcept1App* pExcept;

	MyPoint& operator [] (const int i) {
		return pTab[i];
	}
private:
	MyPoint* allocTab(MyPoint* pTab, int n);
};
