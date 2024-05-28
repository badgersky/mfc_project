// MyData.h : main header file for the MyData DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

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
public:
	MyPoint() : x(0), y(0) {}
	MyPoint(double xx, double yy) : x(xx), y(yy) {}
	~MyPoint() {}
	void set(double xx, double yy) { x = xx; y = yy; }
	MyPoint get() { return *this; }
};

class MyDataAPI MyData : public MyPoint
{
protected:
	MyPoint* pTab;
	int capacity;
	int last;
public:
	MyData(int no_it);
	MyData(const MyData& ob);
	~MyData() { Free(); }
	int size() { return last; }
	void Free() { if (pTab) delete[] pTab; pTab = NULL; }
	void Init(int no_it);
	void Push(const MyPoint& point);
	void clear() { last = 0; }
	void MyData::GetMaxMinCoords(double& max_x, double& min_x, double& max_y, double& min_y);

	MyPoint& operator [] (const int i) {
		return pTab[i];
	}
private:
	MyPoint* allocTab(MyPoint* pTab, int n);
};
