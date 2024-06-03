
// Project_MFCView.cpp : implementation of the CProjectMFCView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Project_MFC.h"
#endif

#include "Project_MFCDoc.h"
#include "Project_MFCView.h"

#include "CDialogInputData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "CDialogGraphWind.h"


// CProjectMFCView

IMPLEMENT_DYNCREATE(CProjectMFCView, CView)

BEGIN_MESSAGE_MAP(CProjectMFCView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CProjectMFCView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_OPERATE_INPUTDATA, &CProjectMFCView::OnOperateInputdata)
	ON_COMMAND(ID_OPERATE_GRAPHWIND, &CProjectMFCView::OnOperateGraphwind)
END_MESSAGE_MAP()

// CProjectMFCView construction/destruction

CProjectMFCView::CProjectMFCView() noexcept
{
	// TODO: add construction code here
    m_scaleX = m_scaleY = 1.0;

    line = 0;
    radius = 6;
    color = RGB(69, 69, 69);

    changed = false;

    memset(&lf, 0, sizeof(LOGFONT));
    lf.lfHeight = 12;
    lf.lfWeight = FW_NORMAL;
    lstrcpy(lf.lfFaceName, _T("Arial"));

    font.CreateFontIndirect(&lf);
}

CProjectMFCView::~CProjectMFCView()
{
}

void CProjectMFCView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	CWnd* ptrWnd = this->GetActiveWindow();
	CProjectMFCDoc* pDoc = GetDocument();
	if (pDoc && pDoc->pDat)
	{
		MyData* pdat = pDoc->pDat;
		pDoc->pExcept->SetWnd(ptrWnd, pdat);
		//pDoc->pExcept->ClearOutWnd();
	}
}

BOOL CProjectMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CProjectMFCView drawing

void CProjectMFCView::OnDraw(CDC* pDC)
{
    CProjectMFCDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc || !pDoc->pDat || !pDoc->pDat->size())
        return;

    // Set mapping mode
    pDC->SetMapMode(MM_TEXT);
    pDC->SetGraphicsMode(GM_ADVANCED);

    CString str;
    TEXTMETRIC tm;

    CPen newpen;
    CPen* oldpen;
    CBrush newbrush;
    CBrush* oldbrush;

    CPoint scr;					  // Screen coordinates
    SIZE size1;					 // Client rect extension in pixels 
    SIZE marg = { 80, 80 };		// Margins in pixels

    // Set font
    CFont* def_font = nullptr;
    if (font.GetSafeHandle() != nullptr)  // Check if a new font is set
    {
        def_font = pDC->SelectObject(&font);
    }

    pDC->GetOutputTextMetrics(&tm);

    CRect rect;
    this->GetClientRect(&rect);

    double max_x, min_x, max_y, min_y;
    pDoc->pDat->GetMaxMinCoords(max_x, min_x, max_y, min_y);

    size1.cx = static_cast<long>(m_scaleX * (rect.right - rect.left));
    size1.cy = static_cast<long>(m_scaleY * (rect.bottom - rect.top));

    newbrush.CreateSolidBrush(RGB(250, 250, 250));
    oldbrush = pDC->SelectObject(&newbrush);
    pDC->Rectangle(0, 0, (rect.right - rect.left), (rect.bottom - rect.top));
    pDC->SelectObject(oldbrush);
    newbrush.DeleteObject();

    DCOORD Coord(0, 0), mmin(min_x, min_y), mmax(max_x, max_y);

    const int npoints = pDoc->pDat->size();

    newpen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    oldpen = pDC->SelectObject(&newpen);

    for (int ipoint = 0; ipoint < npoints; ++ipoint)
    {
        Coord.x = (*pDoc->pDat)[ipoint].x;
        Coord.y = (*pDoc->pDat)[ipoint].y;
        scr = GetScreenCoord(Coord, mmin, mmax, size1, marg, 1, 1);
        MyPoint point = (*pDoc->pDat)[ipoint];
        COLORREF color2;
        if (!changed)
        {
            color2 = point.get_color();
        }
        else 
        {
            color2 = color;
        }
        newbrush.CreateSolidBrush(color2);
        oldbrush = pDC->SelectObject(&newbrush);
        pDC->Ellipse(scr.x + radius, scr.y + radius, scr.x - radius, scr.y - radius);
        pDC->SelectObject(oldbrush);
        newbrush.DeleteObject();

        // Draw lines
        pDC->SelectObject(oldpen);
        newpen.DeleteObject();
        newpen.CreatePen(line, 1, RGB(69, 69, 69));
        oldpen = pDC->SelectObject(&newpen);

        if (ipoint == 0)
            pDC->MoveTo(scr);
        else
            pDC->LineTo(scr);

        pDC->SelectObject(oldpen);
        newpen.DeleteObject();

        // Output text
        str = point.name;
        pDC->TextOut(scr.x + radius + 2, scr.y, str);
    }

    pDC->SelectObject(oldpen);
    newpen.DeleteObject();

    if (def_font)
    {
        pDC->SelectObject(def_font);  // Restore the default font
    }
}



// CProjectMFCView printing


void CProjectMFCView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CProjectMFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CProjectMFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CProjectMFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CProjectMFCView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CProjectMFCView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CProjectMFCView diagnostics

#ifdef _DEBUG
void CProjectMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CProjectMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CProjectMFCDoc* CProjectMFCView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CProjectMFCDoc)));
	return (CProjectMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CProjectMFCView message handlers


void CProjectMFCView::OnOperateInputdata()
{
	// TODO: Add your command handler code here
	CProjectMFCDoc* pDoc = GetDocument();
	CDialogInputData dlg(pDoc);
	dlg.DoModal();
}

CPoint CProjectMFCView::GetScreenCoord(DCOORD Coord, DCOORD min, DCOORD max, SIZE size1, SIZE marg, int hsbpos, int vsbpos)
{
    CPoint scr;
    const double eps = 1e-40;
    if (fabs(min.y - max.y) < eps)
    {
        scr.y = size1.cy / 2;
    }
    else
        scr.y = (long)(marg.cy + (Coord.y - max.y) / (min.y - max.y) * (size1.cy - 2 * marg.cy));

    if (fabs(min.x - max.x) < eps)
    {
        scr.x = size1.cx / 2;
    }
    else
        scr.x = (long)(marg.cx + (Coord.x - min.x) / (max.x - min.x) * (size1.cx - 2 * marg.cx));

    scr.x -= hsbpos * size1.cx / 100;
    scr.y -= vsbpos * size1.cy / 100;

    return scr;
}

void CProjectMFCView::UpdateFont(LOGFONT& logFont)
{
	lf = logFont;

	if (font.GetSafeHandle() != nullptr)
	{
		font.DeleteObject();
	}

	font.CreateFontIndirect(&logFont);
}

void CProjectMFCView::UpdateLine(int num)
{
    line = num;
}

void CProjectMFCView::UpdateRadius(int num)
{
    radius = num;
}

void CProjectMFCView::UpdateColor(COLORREF colorx)
{
    color = colorx;
  
}

void CProjectMFCView::OnOperateGraphwind()
{
	CDialogGraphWind dlg(this);

	if (dlg.DoModal() == IDOK)
	{
		LOGFONT logFont = dlg.GetLogFont();
        int line_style = dlg.GetLineStyle();
        int new_radius = dlg.GetRadius();
        COLORREF new_color = dlg.GetColor();

		UpdateFont(logFont);
        UpdateLine(line_style);
        UpdateRadius(new_radius);
        UpdateColor(new_color);

        changed = true;

        if (dlg.didReset()) {
            changed = false;
            radius = 6;
        }

        Invalidate();
        UpdateWindow();
	}
}
