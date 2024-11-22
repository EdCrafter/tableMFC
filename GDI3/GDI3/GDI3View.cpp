
// GDI3View.cpp : ���������� ������ CGDI3View
//

#include "stdafx.h"
// SHARED_HANDLERS ����� ���������� � ������������ �������� ��������� ���������� ������� ATL, �������
// � ������; ��������� ��������� ������������ ��� ��������� � ������ �������.
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
	// ����������� ������� ������
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGDI3View::OnFilePrintPreview)

	//�������	
	ON_COMMAND(ID_FONT, &CGDI3View::OnFont)
	ON_COMMAND(ID_COLOR, &CGDI3View::OnColor)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// ��������/����������� CGDI3View

CGDI3View::CGDI3View()
{
	// TODO: �������� ��� ��������

}

CGDI3View::~CGDI3View()
{
}

BOOL CGDI3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �������� ����� Window ��� ����� ����������� ���������
	//  CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

// ��������� CGDI3View

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

	CString string = L" ������ - 1  ";
	string += L"    �������� ���������� �� �����";
	string += L" ������ ������ �����~|";

	//MessageBox(L"222");
	CSize dl = pDC->GetTextExtent(string);
	int chir = pDC->GetTextExtent(L"1").cx;
	int h = abs((int)(logFont.lfHeight*1.2));

	UINT position = 0;
	for (int x = 0; x < num_lines; x++) {
		if (x > 0)
			string.Format(L" ������ - %d", x + 1);
		pDC->TextOut(0, position, string);
		pDC->MoveTo(0, position);
		pDC->LineTo(100, position);
		position += h;
	}
	pDC->MoveTo(0, position);
	pDC->LineTo(100, position);

	CRect rect;
	GetClientRect(&rect);

	//��������� ����������
	CSize clientSize(rect.right, rect.bottom);
	CSize docSize(dl.cx, h*num_lines);
	CSize unitSize(chir, h);
	SetScrollSizes(MM_TEXT, docSize, clientSize, unitSize);
}

void CGDI3View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// ��������� ��������� ����������
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// ������ CGDI3View


void CGDI3View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGDI3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// ���������� �� ���������
	return DoPreparePrinting(pInfo);
}

void CGDI3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �������� �������������� ������������� ����� �������
}

void CGDI3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �������� ������� ����� ������
}



// ����������� CGDI3View

#ifdef _DEBUG
void CGDI3View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CGDI3View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CGDI3Doc* CGDI3View::GetDocument() const // �������� ������������ ������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGDI3Doc)));
	return (CGDI3Doc*)m_pDocument;
}
#endif //_DEBUG


// ����������� ��������� CGDI3View

//������ �� ����� ������ �����
void CGDI3View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �������� ���� ��� ����������� ��������� ��� ����� ������������
	CGDI3Doc* pDoc = GetDocument();
	pDoc->m_NumLines += 5;
	pDoc->SetModifiedFlag();
	Invalidate();
	CScrollView::OnLButtonDown(nFlags, point);
}

//������ �� ������ ������ �����
void CGDI3View::OnRButtonDown(UINT nFlags, CPoint point)
{
	CGDI3Doc* pDoc = GetDocument();
	if (pDoc->m_NumLines < 5) return;
	pDoc->m_NumLines -= 5;
	pDoc->SetModifiedFlag();
	Invalidate();
	CScrollView::OnRButtonDown(nFlags, point);
}

//������ �� ��������� ������
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

//������ �� ��������� �����
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