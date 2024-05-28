#pragma once
#include "afxdialogex.h"
#include "Project_MFCDoc.h"
#include "MyData.h"

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

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListCtrl;
	LV_ITEM lvi;
	CImageList m_smallImageList;
	MyData* pDat;
	CProjectMFCDoc* pDocum;
	int m_SelItem;


	afx_msg void OnLvnItemchangedListCtrl(NMHDR* pNMHDR, LRESULT* pResult);
//	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnClickedButtonAdd();
	afx_msg void OnClickedButtonMod();
	afx_msg void OnClickedButtonDel();
	double m_x;
	double m_y;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	void ModifyData();
	afx_msg void OnItemchangingListCtrl(NMHDR* pNMHDR, LRESULT* pResult);
};
