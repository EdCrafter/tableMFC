
// GDI4View.cpp : ���������� ������ CTableView
//

#include "stdafx.h"
// SHARED_HANDLERS ����� ���������� � ������������ �������� ��������� ���������� ������� ATL, �������
// � ������; ��������� ��������� ������������ ��� ��������� � ������ �������.
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
	// ����������� ������� ������
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTableView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// ��������/����������� CTableView

CTableView::CTableView()
{
	// TODO: �������� ��� ��������

}

CTableView::~CTableView()
{
}

BOOL CTableView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �������� ����� Window ��� ����� ����������� ���������
	//  CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

// ��������� CTableView

void CTableView::OnDraw(CDC* pDC)
{
	CTableDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	

	table.draw(pDC);
	//��������� �������
	
	//int dl1, dl2, dl3, dl4;
	//int ots1, ots2, vis;
	//double cena;
	//int i, kol, tol;
	//CString str;
	//CRect rect;

	//ots1 = 10;
	//ots2 = 10;
	//tol = 2;

	////��������� ����������
	//srand(1000);

	//dl1 = pDC->GetTextExtent(L"  ������������ ������  ").cx;
	//dl2 = pDC->GetTextExtent(L"  ���� ������� ������  ").cx;
	//dl3 = pDC->GetTextExtent(L"  ���������� ������  ").cx;
	//dl4 = pDC->GetTextExtent(L"  ������� �� ����������  ").cx;

	//vis = pDC->GetTextExtent(L"�").cy;

	//rect.SetRect(ots1, ots2, ots1 + dl1 + dl2 + dl3 + dl4, ots2 + 2 * vis);

	////��������� ��������� �������
	//pDC->SetTextColor(RGB(0, 0, 255));
	//DrawCell(pDC, L"������� �� ���������� �������",
	//	&rect, 15, DT_CENTER | DT_VCENTER | DT_SINGLELINE, tol);

	////��������� ����� �������
	//rect.SetRect(ots1, ots2 + 2 * vis, ots1 + dl1, ots2 + 4 * vis);
	//DrawCell(pDC, L"������������ ������", &rect, 13,
	//	DT_CENTER | DT_VCENTER | DT_SINGLELINE, tol);
	//rect.OffsetRect(dl1, 0);
	//rect.right = rect.left + dl2;

	//DrawCell(pDC, L"���� ������� ������", &rect, 13,
	//	DT_CENTER | DT_VCENTER | DT_SINGLELINE, tol);
	//rect.OffsetRect(dl2, 0);
	//rect.right = rect.left + dl3;

	//DrawCell(pDC, L"���������� ������", &rect, 13,
	//	DT_CENTER | DT_VCENTER | DT_SINGLELINE, tol);
	//rect.OffsetRect(dl3, 0);
	//rect.right = rect.left + dl4;

	//DrawCell(pDC, L"������� �� ����������", &rect, 13,
	//	DT_CENTER | DT_VCENTER | DT_SINGLELINE, tol);

	////��������� ����� �������
	//pDC->SetTextColor(RGB(0, 0, 0));
	//rect.SetRect(ots1, ots2 + 4 * vis, ots1 + dl1, ots2 + 6 * vis);

	//for (i = 0; i<100; i++) {

	//	//1-� ��������
	//	str.Format(L"����� � %d", i + 1);
	//	DrawCell(pDC, str, &rect, 13, DT_CENTER | DT_VCENTER | DT_SINGLELINE, tol);
	//	rect.OffsetRect(dl1, 0);
	//	rect.right = rect.left + dl2;

	//	//2-� ��������
	//	cena = rand() % 6001 + 4000;
	//	str.Format(L"%0.2f", cena);
	//	DrawCell(pDC, str, &rect, 12, DT_CENTER | DT_VCENTER | DT_SINGLELINE, tol);
	//	rect.OffsetRect(dl2, 0);
	//	rect.right = rect.left + dl3;

	//	//3-� ��������
	//	kol = rand() % 15 + 1;
	//	str.Format(L"%d", kol);
	//	DrawCell(pDC, str, &rect, 12, DT_CENTER | DT_VCENTER | DT_SINGLELINE, tol);
	//	rect.OffsetRect(dl3, 0);
	//	rect.right = rect.left + dl4;
	//	//4-� ��������
	//	str.Format(L"%0.2f", cena*kol);
	//	DrawCell(pDC, str, &rect, 12,
	//		DT_CENTER | DT_VCENTER | DT_SINGLELINE, tol);

	//	rect.OffsetRect(0, 2 * vis);
	//	rect.left = ots1;
	//	rect.right = rect.left + dl1;
	//}

	//��������� ��������
	//SetScrollSizes(MM_TEXT, CSize(ots1 + dl1 + dl2 + dl3 + dl4 + 1, rect.top + 1));


	// TODO: �������� ����� ��� ��������� ��� ����������� ������
}

void CTableView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	table.setName("Table").addColumn("Name", CTable::STRING,300).addColumn("Price", CTable::DOUBLE).addColumn("Count", CTable::INT)
		.addColumn("Revenue", CTable::DOUBLE, 300).addRow().addRow().addRow().addRow();

	table.addColumn("Photo", CTable::IMG,700);


	table.setCell(0, 0, new std::string("Product 1"));
	table.setCell(0, 1, new double(100.0)).setCell(0, 2, new int(10)).setCell(0, 3, new double(1000.0));

	try {
		table.addRow({ new std::string("Product 2"), new double(200.0), new int(20), new double(4000.0), new std::string("C:\\Users\\Fdk\\Fdkndl\\Ooo\\")});
	}
	catch (std::exception& e) {
		std::ofstream logFile("error_log.txt", std::ios::app);  // �������� ����� ��� ���������� ������
		if (logFile.is_open()) {
			logFile << "Error: " << e.what() << std::endl;  // ������ ������ ������ � ����
			logFile.close();  // �������� �����
		}
	}

	CSize sizeTotal;
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// ������ CTableView


void CTableView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CTableView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// ���������� �� ���������
	return DoPreparePrinting(pInfo);
}

void CTableView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �������� �������������� ������������� ����� �������
}

void CTableView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �������� ������� ����� ������
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


// ����������� CTableView

#ifdef _DEBUG
void CTableView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CTableView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CTableDoc* CTableView::GetDocument() const // �������� ������������ ������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTableDoc)));
	return (CTableDoc*)m_pDocument;
}
#endif //_DEBUG


//-----------------------------------------------
//���������������� ������� ������ ������ �������
//-----------------------------------------------
/*
dc - ��������
text - ����� ��� ������
lpRect - �������������
border - ������� ���� ��� ������ ����� ������
par - ���� ������ ��������� ��� ������� DrawText
tol - ������� �����
color - ���� �����
*/
void CTableView::DrawCell(CDC*dc, CString text, LPRECT lpRect,
	UINT border, UINT par, int tol, COLORREF color) {

	CPen pen(PS_SOLID, tol, color);
	CPen* old_pen;
	old_pen = dc->SelectObject(&pen);

	if (border & 1) {
		dc->MoveTo(lpRect->left, lpRect->top);
		dc->LineTo(lpRect->left, lpRect->bottom);
	}
	if (border & 2) {
		dc->MoveTo(lpRect->left, lpRect->top);
		dc->LineTo(lpRect->right, lpRect->top);
	}
	if (border & 4) {
		dc->MoveTo(lpRect->right, lpRect->top);
		dc->LineTo(lpRect->right, lpRect->bottom);
	}
	if (border & 8) {
		dc->MoveTo(lpRect->left, lpRect->bottom);
		dc->LineTo(lpRect->right, lpRect->bottom);
	}
	dc->DrawText(text, lpRect, par);
	dc->SelectObject(old_pen);
}

