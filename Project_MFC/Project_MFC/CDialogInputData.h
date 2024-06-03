#pragma once
#include "afxdialogex.h"
#include "Project_MFCDoc.h"
#include "MyData.h"
#include "Except1.h"

class CColorBox : public CStatic
{
public:
	COLORREF color;
	MyData* pDat;

	CColorBox() : pDat(NULL) { color = RGB(255, 255, 255); }
	//void SetData(MyData* pData) { pDat = pData; }
	//void SetItem(int i);
	void SetColor(COLORREF col) { color = col; Invalidate(); }

protected:
	DECLARE_MESSAGE_MAP()

	afx_msg void OnPaint();
};

// CDialogInputData dialog

class CDialogInputData : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogInputData)

public:
	CDialogInputData(CProjectMFCDoc* pDoc, CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDialogInputData();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_INPUT_DATA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	CExcept1App* pExcept;
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListCtrl;
	LV_ITEM lvi;
	CImageList m_smallImageList;
	MyData* pDat;
	CProjectMFCDoc* pDocum;
	int m_SelItem;

	double m_x;
	double m_y;
	CString m_name;

	COLORREF m_color;
	CColorBox m_ColorBox;

	afx_msg void OnLvnItemchangedListCtrl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickedButtonAdd();
	afx_msg void OnClickedButtonMod();
	afx_msg void OnClickedButtonDel();
	
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	void ModifyData();
	afx_msg void OnItemchangingListCtrl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickedColor();
	afx_msg void OnClickedClearAllBtn();
	BOOL my_is_empty(CString text);
	CString m_find_name;
	afx_msg void OnClickedButtonFind();
};
