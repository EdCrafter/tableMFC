
// GDI1View.cpp : реализация класса CGDI1View
//

#include "stdafx.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "GDI1.h"
#endif

#include "GDI1Doc.h"
#include "GDI1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGDI1View

IMPLEMENT_DYNCREATE(CGDI1View, CView)

BEGIN_MESSAGE_MAP(CGDI1View, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGDI1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()

	//Отклики на меню
	ON_COMMAND(ID_LINES, &CGDI1View::OnLines)
	ON_COMMAND(ID_FIGURES, &CGDI1View::OnFigures)
	ON_COMMAND(ID_TEXT, &CGDI1View::OnText)
	ON_COMMAND(ID_TEXT2, &CGDI1View::OnText2)
END_MESSAGE_MAP()

// создание/уничтожение CGDI1View

CGDI1View::CGDI1View()
{
	// TODO: добавьте код создания
	kod_graf = 0;
}

CGDI1View::~CGDI1View()
{
}

BOOL CGDI1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// рисование CGDI1View

void CGDI1View::OnDraw(CDC* pDC)
{
	CGDI1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);


	//Вывод информации

	CPen pen;
	CPen* pen_st;

	CBrush br;
	CBrush* br_st;

	CFont font;
	CFont* font_st;

	CRect rect;
	GetClientRect(&rect);

	if (kod_graf == 1)
	{

		pen.CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
		pen_st = pDC->SelectObject(&pen);
		pDC->MoveTo(0, 0);
		pDC->LineTo(rect.right, rect.bottom);

		pen.DeleteObject();

		pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
		pDC->SelectObject(&pen);
		pDC->MoveTo(rect.right, 0);
		pDC->LineTo(0, rect.bottom);
		pen.DeleteObject();

		pen.CreatePen(PS_DASH, 1, RGB(0, 255, 255));
		pDC->SelectObject(&pen);
		pDC->MoveTo(0, rect.bottom / 2);
		pDC->LineTo(rect.right, rect.bottom / 2);
		pen.DeleteObject();

		pen.CreatePen(PS_DOT, 1, RGB(255, 0, 255));
		pDC->SelectObject(&pen);
		pDC->MoveTo(rect.right / 2, 0);
		pDC->LineTo(rect.right / 2, rect.bottom);

		pDC->SelectObject(pen_st);
		return;
	}

	if (kod_graf == 2)
	{
		pen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		pen_st = pDC->SelectObject(&pen);
		br.CreateSolidBrush(RGB(255, 0, 0));
		br_st = pDC->SelectObject(&br);

		rect.InflateRect(-rect.right / 8, -rect.bottom / 8);
		pDC->Rectangle(&rect);

		br.DeleteObject();
		br.CreateSolidBrush(RGB(0, 255, 0));
		pDC->SelectObject(&br);
		rect.InflateRect(-rect.right / 8, -rect.bottom / 8);
		pDC->Rectangle(&rect);

		br.DeleteObject();
		br.CreateSolidBrush(RGB(0, 0, 255));
		pDC->SelectObject(&br);
		rect.InflateRect(-rect.right / 8, -rect.bottom / 8);
		pDC->Ellipse(&rect);

		pDC->SelectObject(pen_st);
		pDC->SelectObject(br_st);
	}

	if (kod_graf == 3)
	{

		pDoc->font_text.lfHeight = -14;

		font.CreateFontIndirect(&(pDoc->font_text));
		font_st = pDC->SelectObject(&font);

		int i, y = 20;

		//Включение генератора случайных чисел
		srand(kol_sec);

		for (i = 0; i<10; i++)
		{
			pDC->SetTextColor(RGB(rand() % 256, rand() % 256, rand() % 256));
			pDC->TextOut(20, y, L"Привет программистам!");
			pDoc->font_text.lfHeight -= 5;

			y += (int)fabs(1.3*pDoc->font_text.lfHeight);

			font.DeleteObject();
			font.CreateFontIndirect(&pDoc->font_text);


			pDC->SelectObject(&font);
		}	
		pDC->SelectObject(font_st);
	}


	if (kod_graf == 4)
	{


		int i, h = 200, y = 20;		
		font.CreatePointFont(h, L"Times New Roman");
		font_st = pDC->SelectObject(&font);			

		for (i = 0; i<10; i++)
		{
			pDC->SetTextColor(RGB(rand() % 256, rand() % 256, rand() % 256));
			pDC->TextOut(20, y, L"Привет программистам!");
			
			y += (int)fabs(h/4 );			
		}

		pDC->SelectObject(font_st);
	}

	// TODO: добавьте здесь код отрисовки для собственных данных
}


// печать CGDI1View


void CGDI1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGDI1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CGDI1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CGDI1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}

void CGDI1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGDI1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// диагностика CGDI1View

#ifdef _DEBUG
void CGDI1View::AssertValid() const
{
	CView::AssertValid();
}

void CGDI1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGDI1Doc* CGDI1View::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGDI1Doc)));
	return (CGDI1Doc*)m_pDocument;
}
#endif //_DEBUG


// обработчики сообщений CGDI1View

// --------------Отклики---------------
void CGDI1View::OnLines()
{
	kod_graf = 1;
	Invalidate();
}


void CGDI1View::OnFigures()
{
	kod_graf = 2;
	Invalidate();
}


void CGDI1View::OnText()
{
	

	srand((int)time(0));
	kod_graf = 3;
	Invalidate();
}


void CGDI1View::OnText2()
{
	srand((int)time(0));
	kod_graf = 4;
	Invalidate();
}
