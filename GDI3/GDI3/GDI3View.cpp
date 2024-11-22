
// GDI3View.cpp : реализация класса CGDI3View
//

#include "stdafx.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "GDI3.h"
#endif

#include "GDI3Doc.h"
#include "GDI3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGDI3View

IMPLEMENT_DYNCREATE(CGDI3View, CScrollView)

BEGIN_MESSAGE_MAP(CGDI3View, CScrollView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGDI3View::OnFilePrintPreview)

	//Отклики	
	ON_COMMAND(ID_FONT, &CGDI3View::OnFont)
	ON_COMMAND(ID_COLOR, &CGDI3View::OnColor)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// создание/уничтожение CGDI3View

CGDI3View::CGDI3View()
{
	// TODO: добавьте код создания

}

CGDI3View::~CGDI3View()
{
}

BOOL CGDI3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

// рисование CGDI3View

void CGDI3View::OnDraw(CDC* pDC)
{
	CGDI3Doc* pDoc = GetDocument();
	if (!pDoc) return;

	int num_lines = pDoc->m_NumLines;
	LOGFONT logFont = pDoc->logFont;

	CFont font;
	font.CreateFontIndirect(&logFont);
	pDC->SelectObject(&font);
	pDC->SetTextColor(pDoc->m_Color);

	CString string = L" Строка - 1  ";
	string += L"    Проверка скроллинга по длине";
	string += L" первой строки Конец~|";

	//MessageBox(L"222");
	CSize dl = pDC->GetTextExtent(string);
	int chir = pDC->GetTextExtent(L"1").cx;
	int h = abs((int)(logFont.lfHeight*1.2));

	UINT position = 0;
	for (int x = 0; x < num_lines; x++) {
		if (x > 0)
			string.Format(L" Строка - %d", x + 1);
		pDC->TextOut(0, position, string);
		pDC->MoveTo(0, position);
		pDC->LineTo(100, position);
		position += h;
	}
	pDC->MoveTo(0, position);
	pDC->LineTo(100, position);

	CRect rect;
	GetClientRect(&rect);

	//Установка скроллинга
	CSize clientSize(rect.right, rect.bottom);
	CSize docSize(dl.cx, h*num_lines);
	CSize unitSize(chir, h);
	SetScrollSizes(MM_TEXT, docSize, clientSize, unitSize);
}

void CGDI3View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// Начальная установка скроллинга
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// печать CGDI3View


void CGDI3View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGDI3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CGDI3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CGDI3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}



// диагностика CGDI3View

#ifdef _DEBUG
void CGDI3View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CGDI3View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CGDI3Doc* CGDI3View::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGDI3Doc)));
	return (CGDI3Doc*)m_pDocument;
}
#endif //_DEBUG


// обработчики сообщений CGDI3View

//Отклик на левую кнопку мышки
void CGDI3View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	CGDI3Doc* pDoc = GetDocument();
	pDoc->m_NumLines += 5;
	pDoc->SetModifiedFlag();
	Invalidate();
	CScrollView::OnLButtonDown(nFlags, point);
}

//Отклик на правую кнопку мышки
void CGDI3View::OnRButtonDown(UINT nFlags, CPoint point)
{
	CGDI3Doc* pDoc = GetDocument();
	if (pDoc->m_NumLines < 5) return;
	pDoc->m_NumLines -= 5;
	pDoc->SetModifiedFlag();
	Invalidate();
	CScrollView::OnRButtonDown(nFlags, point);
}

//Отклик на изменение шрифта
void CGDI3View::OnFont()
{
	CGDI3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CFontDialog fontDlg(&(pDoc->logFont));

	if (fontDlg.DoModal() == IDOK)
	{
		fontDlg.GetCurrentFont(&(pDoc->logFont));
		pDoc->SetModifiedFlag();
		Invalidate();
	}
}

//Отклик на изменение цвета
void CGDI3View::OnColor()
{
	CGDI3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CColorDialog color(pDoc->m_Color);
	if (color.DoModal() == IDOK) {
		pDoc->m_Color = color.GetColor();
		pDoc->SetModifiedFlag();
		Invalidate();
	}
}