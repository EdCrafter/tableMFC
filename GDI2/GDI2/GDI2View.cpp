
// GDI2View.cpp : реализация класса CGDI2View
//

#include "stdafx.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
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
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGDI2View::OnFilePrintPreview)
	
	//Отклики на левую и правую кнопки мышки
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// создание/уничтожение CGDI2View

CGDI2View::CGDI2View()
{
	// TODO: добавьте код создания
	nBrushStyle = 0;
}

CGDI2View::~CGDI2View()
{
}

BOOL CGDI2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// рисование CGDI2View

void CGDI2View::OnDraw(CDC* /*pDC*/)
{
	CGDI2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	
}


// печать CGDI2View


void CGDI2View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGDI2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CGDI2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CGDI2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
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


// диагностика CGDI2View

#ifdef _DEBUG
void CGDI2View::AssertValid() const
{
	CView::AssertValid();
}

void CGDI2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGDI2Doc* CGDI2View::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGDI2Doc)));
	return (CGDI2Doc*)m_pDocument;
}
#endif //_DEBUG


// обработчики сообщений CGDI2View

//Отклик на нажатие левой кнопки мышки
void CGDI2View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

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

//Отклик на нажатие правой кнопки мышки
void CGDI2View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	CBrushDialog	dlg;

	    dlg.m_nBrush = nBrushStyle;
	    
	    if (dlg.DoModal() == IDOK)
		nBrushStyle = dlg.m_nBrush;
		CString vv;
		vv.Format(L"  %d  ", nBrushStyle); 
		AfxMessageBox(vv);
		 
	CView::OnRButtonDown(nFlags, point);
}
