#pragma once
#include "afxdialogex.h"


// CDialogGraphWind dialog

class CDialogGraphWind : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogGraphWind)

	LOGFONT m_logFont;
	int m_combo;
	CComboBox m_comboCTRL;
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
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedButtonFont();
	afx_msg void OnBnClickedOk();
	LOGFONT GetLogFont() { return m_logFont; }
	afx_msg void OnCbnSelchangeComboLines();
	int GetLineStyle() { return m_combo; }
};
