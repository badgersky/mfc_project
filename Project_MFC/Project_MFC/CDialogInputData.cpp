// CDialogInputData.cpp : implementation file
//

#include "pch.h"
#include "Project_MFC.h"
#include "afxdialogex.h"
#include "CDialogInputData.h"


// CDialogInputData dialog

IMPLEMENT_DYNAMIC(CDialogInputData, CDialogEx)

CDialogInputData::CDialogInputData(CProjectMFCDoc* pDoc, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_INPUT_DATA, pParent)
	, m_x(0)
	, m_y(0)
	, m_name(_T(""))
	, m_find_name(_T(""))
{
	pDocum = pDoc;
	memset((void*)&lvi, 0, sizeof(LVITEMA));
	pDat = pDocum->pDat;
	m_color = RGB(0, 0, 0);
}

CDialogInputData::~CDialogInputData()
{
	m_smallImageList.DeleteImageList();
}

void CDialogInputData::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CTRL, m_ListCtrl);
	DDX_Text(pDX, IDC_EDIT_X, m_x);
	DDX_Text(pDX, IDC_EDIT_Y, m_y);
	DDX_Text(pDX, IDC_EDIT_NAME, m_name);
	DDV_MaxChars(pDX, m_name, 50);
	DDX_Text(pDX, IDC_FIND_ITEM, m_find_name);
	DDV_MaxChars(pDX, m_find_name, 50);
}


BEGIN_MESSAGE_MAP(CDialogInputData, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CTRL, &CDialogInputData::OnLvnItemchangedListCtrl)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CDialogInputData::OnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_MOD, &CDialogInputData::OnClickedButtonMod)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CDialogInputData::OnClickedButtonDel)
	ON_BN_CLICKED(IDOK, &CDialogInputData::OnBnClickedOk)
	ON_NOTIFY(LVN_ITEMCHANGING, IDC_LIST_CTRL, &CDialogInputData::OnItemchangingListCtrl)
	ON_BN_CLICKED(IDC_COLOR, &CDialogInputData::OnClickedColor)
	ON_BN_CLICKED(IDC_CLEAR_ALL_BTN, &CDialogInputData::OnClickedClearAllBtn)
	ON_BN_CLICKED(IDC_BUTTON_FIND, &CDialogInputData::OnClickedButtonFind)
END_MESSAGE_MAP()


// CDialogInputData message handlers

BOOL CDialogInputData::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// highlighting selected rows
	m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	// TODO:  Add extra initialization here
	VERIFY(m_ColorBox.SubclassDlgItem(IDC_STATIC_COLOR, this));

	CString strx, stry, color, name;

	lvi.mask = LVIF_TEXT;
	lvi.state = 0;
	lvi.stateMask = 0;
	lvi.iImage = 0;

	HICON hIcon = ::LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(IDR_ProjectMFCTYPE));

	m_smallImageList.Create(16, 16, FALSE, 1, 0);
	m_smallImageList.Add(hIcon);
	m_ListCtrl.SetImageList(&m_smallImageList, LVSIL_SMALL);

	CRect rectListCtrl;
	memset(rectListCtrl, 0, sizeof(rectListCtrl));
	m_ListCtrl.GetClientRect(&rectListCtrl);

	int list_ctrl_width = rectListCtrl.right - rectListCtrl.left;
	int column_width = list_ctrl_width / 4;

	int ret;
	int nFormat = LVCFMT_LEFT;
	ret = m_ListCtrl.InsertColumn(0, _T("name"), nFormat, column_width, 0);
	ret = m_ListCtrl.InsertColumn(1, _T("X"), nFormat, column_width, 1);
	ret = m_ListCtrl.InsertColumn(2, _T("Y"), nFormat, column_width, 2);
	ret = m_ListCtrl.InsertColumn(3, _T("color"), nFormat, column_width, 3);

	ASSERT(pDat);
	int no_item = pDat->size();

	lvi.iSubItem = 0;
	m_ListCtrl.SetItemCount(no_item);

	for (int i = 0; i < no_item; i++)
	{
		MyPoint pt = (*pDat)[i];
		lvi.iItem = i;
		name = pt.name;
		size_t Len = name.GetLength();
		strx.Format(_T("%le"), pt.x);
		Len += strx.GetLength();
		stry.Format(_T("%le"), pt.y);
		Len += stry.GetLength();
		color.Format(_T("%u"), pt.color);
		Len += color.GetLength();

		lvi.pszText = _T(" ");
		lvi.cchTextMax = Len;
		ret = m_ListCtrl.InsertItem(&lvi);

		m_ListCtrl.SetItemText(lvi.iItem, 0, name);
		m_ListCtrl.SetItemText(lvi.iItem, 1, strx);
		m_ListCtrl.SetItemText(lvi.iItem, 2, stry);
		m_ListCtrl.SetItemText(lvi.iItem, 3, color);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDialogInputData::OnLvnItemchangedListCtrl(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}



void CDialogInputData::OnClickedButtonAdd()
{
	// TODO: Add your control notification handler code here
	int nItem = m_ListCtrl.GetItemCount();
	int ret = -1;
	MyPoint tmp;
	CString strx, stry, color, name;

	UpdateData(TRUE);

	if (m_name.IsEmpty() || my_is_empty(m_name)) {
		m_name = "vertex";
	}

	tmp.x = m_x;
	tmp.y = m_y;
	m_color = m_ColorBox.color;
	tmp.color = m_color;
	tmp.name = m_name;
	name = m_name;
	size_t Len = name.GetLength();
	strx.Format(_T("%le"), m_x);
	Len += strx.GetLength();
	stry.Format(_T("%le"), m_y);
	Len += stry.GetLength();
	color.Format(_T("%u"), m_color);
	Len += color.GetLength();

	lvi.iItem = nItem;
	lvi.pszText = _T(" ");
	lvi.cchTextMax = (int)Len;
	ret = m_ListCtrl.InsertItem(&lvi);
	m_ListCtrl.SetItemText(lvi.iItem, 0, name);
	m_ListCtrl.SetItemText(lvi.iItem, 1, strx);
	m_ListCtrl.SetItemText(lvi.iItem, 2, stry);
	m_ListCtrl.SetItemText(lvi.iItem, 3, color);

	UpdateData(FALSE);

	ASSERT_VALID(pDocum);
	pDocum->SetModifiedFlag();
	pDocum->UpdateAllViews(NULL);
}


void CDialogInputData::OnClickedButtonMod()
{
	// TODO: Add your control notification handler code here
	{
		// TODO: Add your control notification handler code here
		int ret = -1;
		int no_item = m_ListCtrl.GetItemCount();

		if (m_SelItem < 0 || m_SelItem >= no_item)
			return;

		MyPoint tmp;
		CString strx, stry, color, name;
		int nItem = m_SelItem;

		UpdateData(TRUE);

		if (m_name.IsEmpty() || my_is_empty(m_name)) {
			m_name = "vertex";
		}

		tmp.x = m_x;
		tmp.y = m_y;
		m_color = m_ColorBox.color;
		tmp.color = m_color;
		tmp.name = m_name;
		name = m_name;
		size_t Len = name.GetLength();
		strx.Format(_T("%le"), m_x);
		Len += strx.GetLength();
		stry.Format(_T("%le"), m_y);
		Len += stry.GetLength();
		color.Format(_T("%u"), m_color);
		Len += color.GetLength();

		lvi.iItem = nItem;
		//lvi.pszText = _T(" ");
		//lvi.cchTextMax = (int)Len;
		//ret = m_ListCtrl.InsertItem(&lvi);
		m_ListCtrl.SetItemText(lvi.iItem, 0, name);
		m_ListCtrl.SetItemText(lvi.iItem, 1, strx);
		m_ListCtrl.SetItemText(lvi.iItem, 2, stry);
		m_ListCtrl.SetItemText(lvi.iItem, 3, color);

		UpdateData(FALSE);

		ModifyData();
	}
}


void CDialogInputData::OnClickedButtonDel()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int no_item = m_ListCtrl.GetItemCount();

	if (m_SelItem < 0 || m_SelItem >= no_item)
		return;

	m_ListCtrl.DeleteItem(m_SelItem);
	UpdateData(FALSE);

	ASSERT_VALID(pDocum);
	pDocum->SetModifiedFlag();
	pDocum->UpdateAllViews(NULL);
}


void CDialogInputData::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();

	ModifyData();
}


void CDialogInputData::ModifyData()
{
	TCHAR st[512];
	BOOL ret(0);
	MyPoint tmp;

	UpdateData(TRUE);
	const int no_it(m_ListCtrl.GetItemCount());

	if (pDat)
		delete pDat;
	pDocum->pDat = pDat = new MyData(no_it);

	for (int nItem = 0; nItem < no_it; ++nItem)
	{
		BOOL ret = m_ListCtrl.GetItemText(nItem, 0, st, sizeof(st));
		tmp.name = st;
		if (st[0] == _T('\0') || my_is_empty(st))
		{
			tmp.name = "vertex";
		}
		ret = m_ListCtrl.GetItemText(nItem, 1, st, sizeof(st));
		tmp.x = _ttof(st);
		ret = m_ListCtrl.GetItemText(nItem, 2, st, sizeof(st));
		tmp.y = _ttof(st);
		ret = m_ListCtrl.GetItemText(nItem, 3, st, sizeof(st));
		tmp.color = _ttof(st);

		pDat->Push(tmp);
	}

	UpdateData(FALSE);

	ASSERT_VALID(pDocum);
	pDocum->SetModifiedFlag();
	pDocum->UpdateAllViews(NULL);
}


void CDialogInputData::OnItemchangingListCtrl(NMHDR* pNMHDR, LRESULT* pResult)
{
	{
		LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
		// TODO: Add your control notification handler code here
		*pResult = 0;

		UpdateData(TRUE);

		int nItem = m_SelItem = pNMLV->iItem;
		int no_item = m_ListCtrl.GetItemCount();

		if (m_SelItem < 0 || m_SelItem >= no_item)
			return;

		int ncol = 0;
		TCHAR st[512];
		BOOL ret = m_ListCtrl.GetItemText(nItem, ncol, st, sizeof(st));
		m_name = st;
		if (st[0] == _T('\0') || my_is_empty(st))
		{
			m_name = "vertex";
		}
		ncol = 1;
		ret = m_ListCtrl.GetItemText(nItem, ncol, st, sizeof(st));
		m_x = _ttof(st);
		ncol = 2;
		ret = m_ListCtrl.GetItemText(nItem, ncol, st, sizeof(st));
		m_y = _ttof(st);
		ncol = 3;
		ret = m_ListCtrl.GetItemText(nItem, ncol, st, sizeof(st));
		m_color = _ttof(st);

		m_ColorBox.SetColor(m_color);

		UpdateData(FALSE);
	}
}


///////////////////////////////////////////////////////////////////////////////////////////
////////////// CColorBox

BEGIN_MESSAGE_MAP(CColorBox, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()


void CColorBox::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnPaint() for painting messages

	CRect rect;
	this->GetClientRect(&rect);

	CBrush newbrush;
	CBrush* oldbrush;
	newbrush.CreateSolidBrush(color);
	oldbrush = dc.SelectObject(&newbrush);

	dc.Rectangle(0, 0, (rect.right - rect.left), (rect.bottom - rect.top));

	dc.SelectObject(oldbrush);
	newbrush.DeleteObject();
}

//void CColorBox::SetItem(int i)
//{
	//COLORREF tab[] = { RGB(0, 0, 0), RGB(255, 0, 0), RGB(0, 255, 0), RGB(0, 0, 255) };
	//int ii = i % (sizeof(tab) / sizeof(tab[0]));
	//color = tab[ii];
//}

void CDialogInputData::OnClickedColor()
{
	// TODO: Add your control notification handler code here

	CColorDialog dlg;

	if (dlg.DoModal())
	{
		m_ColorBox.SetColor(dlg.GetColor());
		m_ColorBox.Invalidate();
	}
}

void CDialogInputData::OnClickedClearAllBtn()
{
	m_ListCtrl.DeleteAllItems();

	if (pDat) {
		pDat->Free();
		pDat->clear();
		pDat = NULL;
	}

	ASSERT_VALID(pDocum);
	pDocum->SetModifiedFlag();
	pDocum->UpdateAllViews(NULL);
}

BOOL CDialogInputData::my_is_empty(CString text)
{
	BOOL res = true;
	WCHAR tmp;

	for (int i = 0; i < text.GetLength(); i++)
	{
		tmp = text[i];

		if (tmp != 32 && tmp != 9 && tmp != 10)
		{
			res = false;
		}
	}

	return res;
}


void CDialogInputData::OnClickedButtonFind()
{
	UpdateData(TRUE);

	MyPoint* start = &(*pDat)[0];
	MyPoint* stop = &(*pDat)[pDat->size() - 1];
	MyPoint* found = pDat->find(start, stop, m_find_name);

	if (found) {
		CString message;

		for (int i = 0; i < m_ListCtrl.GetItemCount(); ++i) {
			m_ListCtrl.SetItemState(i, 0, LVIS_SELECTED | LVIS_FOCUSED);
		}

		int index = found - &(*pDat)[0];
		// Set focus on and select the found item in the list control
		m_ListCtrl.SetItemState(index, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
		m_ListCtrl.EnsureVisible(index, FALSE);

		// Highlight the selected item
		m_ListCtrl.SetSelectionMark(index);
		m_ListCtrl.SetFocus();
		m_ListCtrl.RedrawItems(index, index);
		//message.Format(_T("Point found:\nName: %s\nX: %lf\nY: %lf\n"), found->name, found->x, found->y);
		//AfxMessageBox(message);
	}
	else {
		AfxMessageBox(_T("Point not found"));
	}
}
