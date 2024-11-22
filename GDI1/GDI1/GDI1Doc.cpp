
// GDI1Doc.cpp : ���������� ������ CGDI1Doc
//

#include "stdafx.h"
// SHARED_HANDLERS ����� ���������� � ������������ �������� ��������� ���������� ������� ATL, �������
// � ������; ��������� ��������� ������������ ��� ��������� � ������ �������.
#ifndef SHARED_HANDLERS
#include "GDI1.h"
#endif

#include "GDI1Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CGDI1Doc

IMPLEMENT_DYNCREATE(CGDI1Doc, CDocument)

BEGIN_MESSAGE_MAP(CGDI1Doc, CDocument)
END_MESSAGE_MAP()


// ��������/����������� CGDI1Doc

CGDI1Doc::CGDI1Doc()
{
	// TODO: �������� ��� ��� ������������ ������ ������������
	font_text.lfHeight = -40;
	font_text.lfWidth = 0;
	font_text.lfEscapement = 0;
	font_text.lfOrientation = 0;
	font_text.lfWeight = FW_NORMAL;
	font_text.lfItalic = 0;
	font_text.lfUnderline = 0;
	font_text.lfStrikeOut = 0;
	font_text.lfCharSet = ANSI_CHARSET;
	font_text.lfOutPrecision = OUT_DEFAULT_PRECIS;
	font_text.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	font_text.lfQuality = PROOF_QUALITY;
	font_text.lfPitchAndFamily = VARIABLE_PITCH | FF_ROMAN;
	wcscpy_s(font_text.lfFaceName, L"Times New Roman");
}

CGDI1Doc::~CGDI1Doc()
{
}

BOOL CGDI1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �������� ��� ��������� �������������
	// (��������� SDI ����� �������� ������������ ���� ��������)

	return TRUE;
}




// ������������ CGDI1Doc

void CGDI1Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �������� ��� ����������
	}
	else
	{
		// TODO: �������� ��� ��������
	}
}

#ifdef SHARED_HANDLERS

// ��������� ��� �������
void CGDI1Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �������� ���� ��� ��� ����������� ������ ���������
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ��������� ������������ ������
void CGDI1Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������� ���������� ������ �� ������ ���������. 
	// ����� ����������� ������ ����������� ������ � ������� ";"

	// ��������:  strSearchContent = _T("�����;�������������;����;������ ole;");
	SetSearchContent(strSearchContent);
}

void CGDI1Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// ����������� CGDI1Doc

#ifdef _DEBUG
void CGDI1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGDI1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// ������� CGDI1Doc
