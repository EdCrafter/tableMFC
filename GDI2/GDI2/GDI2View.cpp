
// GDI2View.cpp : ���������� ������ CGDI2View
//

#include "stdafx.h"
// SHARED_HANDLERS ����� ���������� � ������������ �������� ��������� ���������� ������� ATL, �������
// � ������; ��������� ��������� ������������ ��� ��������� � ������ �������.
#ifndef SHARED_HANDLERS
#include "GDI2.h"
#endif

#include "GDI2Doc.h"
#include "GDI2View.h"
#include "BrushDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGDI2View

IMPLEMENT_DYNCREATE(CGDI2View, CView)

BEGIN_MESSAGE_MAP(CGDI2View, CView)
	// ����������� ������� ������
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGDI2View::OnFilePrintPreview)
	
	//������� �� ����� � ������ ������ �����
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// ��������/����������� CGDI2View

CGDI2View::CGDI2View()
{
	// TODO: �������� ��� ��������
	nBrushStyle = 0;
}

CGDI2View::~CGDI2View()
{
}

BOOL CGDI2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �������� ����� Window ��� ����� ����������� ���������
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// ��������� CGDI2View

void CGDI2View::OnDraw(CDC* /*pDC*/)
{
	CGDI2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	
}


// ������ CGDI2View


void CGDI2View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGDI2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// ���������� �� ���������
	return DoPreparePrinting(pInfo);
}

void CGDI2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �������� �������������� ������������� ����� �������
}

void CGDI2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �������� ������� ����� ������
}

//void CGDI2View::OnRButtonUp(UINT /* nFlags */, CPoint point)
//{
//	ClientToScreen(&point);
//	OnContextMenu(this, point);
//}

//void CGDI2View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
//{
//#ifndef SHARED_HANDLERS
//	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
//#endif
//}


// ����������� CGDI2View

#ifdef _DEBUG
void CGDI2View::AssertValid() const
{
	CView::AssertValid();
}

void CGDI2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGDI2Doc* CGDI2View::GetDocument() const // �������� ������������ ������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGDI2Doc)));
	return (CGDI2Doc*)m_pDocument;
}
#endif //_DEBUG


// ����������� ��������� CGDI2View

//������ �� ������� ����� ������ �����
void CGDI2View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �������� ���� ��� ����������� ��������� ��� ����� ������������

	CClientDC	dc(this);

	CPen		pen(PS_SOLID, 0, RGB(0, 0, 255));
	CPen*		oldPen = dc.SelectObject(&pen);
	CBrush*  brush;
	brush = new CBrush(1, RGB(0, 0, 0));

	if (nBrushStyle)
		brush = new CBrush(nBrushStyle - 1, RGB(0, 0, 0));
	else
		brush = new CBrush(RGB(255, 0, 0));


	CBrush*	oldBrush = dc.SelectObject(brush);

	dc.Rectangle(point.x, point.y, point.x + 40, point.y + 40);
	dc.SelectObject(oldBrush);
	dc.SelectObject(oldPen);
	delete brush;
	CView::OnLButtonDown(nFlags, point);
}

//������ �� ������� ������ ������ �����
void CGDI2View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �������� ���� ��� ����������� ��������� ��� ����� ������������
	CBrushDialog	dlg;

	    dlg.m_nBrush = nBrushStyle;
	    
	    if (dlg.DoModal() == IDOK)
		nBrushStyle = dlg.m_nBrush;
		CString vv;
		vv.Format(L"  %d  ", nBrushStyle); 
		AfxMessageBox(vv);
		 
	CView::OnRButtonDown(nFlags, point);
}
