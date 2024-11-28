
// GDI4View.cpp : реализаци€ класса CTableView
//

#include "stdafx.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позвол€ет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "GDI4.h"
#endif

#include "GDI4Doc.h"
#include "GDI4View.h"

#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTableView

IMPLEMENT_DYNCREATE(CTableView, CScrollView)

BEGIN_MESSAGE_MAP(CTableView, CScrollView)
	// —тандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTableView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// создание/уничтожение CTableView

CTableView::CTableView()
{
	// TODO: добавьте код создани€

}

CTableView::~CTableView()
{
}

BOOL CTableView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменени€
	//  CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

// рисование CTableView

void CTableView::OnDraw(CDC* pDC)
{
	CTableDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	

	table.draw(pDC);
	
	SetScrollSizes(MM_TEXT, CSize(table.getWidht(),table.getHeight()));
}

void CTableView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	table.setName("Table").addColumn("Name", CTable::STRING,300).addColumn("Price", CTable::DOUBLE).addColumn("Count", CTable::INT)
		.addColumn("Revenue", CTable::DOUBLE, 300).addRow().addRow().addRow().addRow();

	table.addColumn("Photo", CTable::IMG,400);

	table.setCell(0, 0, new std::string("Product some another information that highly important for  1 Product some another information that highly important for  1"));
	table.setCell(0, 1, new double(100.0)).setCell(0, 2, new int(1000000000)).setCell(0, 3, new double(1000.0));
	table.setCell(0, 4, new std::string("C:\\Users\\verde\\Downloads\\2.jfif"))
		.setCell(1, 4, new std::string("C:\\Users\\verde\\Downloads\\3.jpg"));

	table.addRow({ new std::string("Product 2"), new double(200.0), new int(20), new double(4000.0), new std::string("C:\\Users\\verde\\Downloads\\1.jfif")});


	CSize sizeTotal;
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


void CTableView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CTableView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CTableView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CTableView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}

void CTableView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CTableView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// диагностика CTableView

#ifdef _DEBUG
void CTableView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CTableView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CTableDoc* CTableView::GetDocument() const // встроена неотлаженна€ верси€
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTableDoc)));
	return (CTableDoc*)m_pDocument;
}
#endif //_DEBUG

