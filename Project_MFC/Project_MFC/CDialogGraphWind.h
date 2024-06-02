#pragma once
#include "afxdialogex.h"


// CDialogGraphWind dialog

class CDialogGraphWind : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogGraphWind)

	LOGFONT m_logFont;
public:
	CDialogGraphWind(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDialogGraphWind();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GRAPH_WIND };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedButtonFont();
	afx_msg void OnBnClickedOk();
	LOGFONT GetLogFont() { return m_logFont; }
};
