// CDialogGraphWind.cpp : implementation file
//

#include "pch.h"
#include "Project_MFC.h"
#include "afxdialogex.h"
#include "CDialogGraphWind.h"


// CDialogGraphWind dialog

IMPLEMENT_DYNAMIC(CDialogGraphWind, CDialogEx)

CDialogGraphWind::CDialogGraphWind(CProjectMFCView* view, CWnd* pParent /*nullptr*/)
	: CDialogEx(IDD_DIALOG_GRAPH_WIND, pParent)
{
	m_logFont = view->lf;
	m_combo = view->line;
	m_radius = view->radius;
	m_colorCTRL.SetColor(view->color);
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
	DDX_Text(pDX, IDC_EDIT_RADIUS, m_radius);
	DDV_MinMaxInt(pDX, m_radius, 0, INT_MAX);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON, m_colorCTRL);
}


BEGIN_MESSAGE_MAP(CDialogGraphWind, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_FONT, &CDialogGraphWind::OnClickedButtonFont)
	ON_BN_CLICKED(IDOK, &CDialogGraphWind::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_LINES, &CDialogGraphWind::OnCbnSelchangeComboLines)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON, &CDialogGraphWind::OnClickedMfccolorbutton)
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

	m_comboCTRL.SetCurSel(m_combo);

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


void CDialogGraphWind::OnChangeEditRadius()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(TRUE);

	if (!m_radius) m_radius = 6;
}


void CDialogGraphWind::OnClickedMfccolorbutton()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}
