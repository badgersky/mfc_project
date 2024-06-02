// CDialogGraphWind.cpp : implementation file
//

#include "pch.h"
#include "Project_MFC.h"
#include "afxdialogex.h"
#include "CDialogGraphWind.h"


// CDialogGraphWind dialog

IMPLEMENT_DYNAMIC(CDialogGraphWind, CDialogEx)

CDialogGraphWind::CDialogGraphWind(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_GRAPH_WIND, pParent)
	, m_combo(0)
{
}

CDialogGraphWind::~CDialogGraphWind()
{
}

void CDialogGraphWind::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_COMBO_LINES, m_combo);
	DDV_MinMaxInt(pDX, m_combo, 0, 5);
	DDX_Control(pDX, IDC_COMBO_LINES, m_comboCTRL);
}


BEGIN_MESSAGE_MAP(CDialogGraphWind, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_FONT, &CDialogGraphWind::OnClickedButtonFont)
	ON_BN_CLICKED(IDOK, &CDialogGraphWind::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_LINES, &CDialogGraphWind::OnCbnSelchangeComboLines)
END_MESSAGE_MAP()


// CDialogGraphWind message handlers

BOOL CDialogGraphWind::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// combobox for line styles
	m_comboCTRL.AddString(_T("solid"));
	m_comboCTRL.AddString(_T("dash"));
	m_comboCTRL.AddString(_T("dot"));
	m_comboCTRL.AddString(_T("dash-dot"));
	m_comboCTRL.AddString(_T("dash-dot-dot"));
	m_comboCTRL.AddString(_T("null"));

	m_comboCTRL.SetCurSel(0);

	// default font
	memset(&m_logFont, 0, sizeof(LOGFONT));
	m_logFont.lfHeight = 12;
	m_logFont.lfWeight = FW_NORMAL;
	lstrcpy(m_logFont.lfFaceName, _T("Arial"));

	return TRUE;
}

void CDialogGraphWind::OnClickedButtonFont()
{
	CFontDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		dlg.GetCurrentFont(&m_logFont);
	}
}


void CDialogGraphWind::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void CDialogGraphWind::OnCbnSelchangeComboLines()
{
	UpdateData(TRUE);
}
