
// GDI3Doc.cpp : ���������� ������ CGDI3Doc
//

#include "stdafx.h"
// SHARED_HANDLERS ����� ���������� � ������������ �������� ��������� ���������� ������� ATL, �������
// � ������; ��������� ��������� ������������ ��� ��������� � ������ �������.
#ifndef SHARED_HANDLERS
#include "GDI3.h"
#endif

#include "GDI3Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CGDI3Doc

IMPLEMENT_DYNCREATE(CGDI3Doc, CDocument)

BEGIN_MESSAGE_MAP(CGDI3Doc, CDocument)
END_MESSAGE_MAP()


// ��������/����������� CGDI3Doc

CGDI3Doc::CGDI3Doc()
{
	// ������������� ������

	m_NumLines = 0;
	m_Color = 0L;
	m_NumLines = 5;
	logFont.lfHeight = -20;
	logFont.lfWidth = 0;
	logFont.lfEscapement = 0;
	logFont.lfOrientation = 0;
	logFont.lfWeight = FW_NORMAL;
	logFont.lfItalic = 0;
	logFont.lfUnderline = 0;
	logFont.lfStrikeOut = 0;
	logFont.lfCharSet = ANSI_CHARSET;
	logFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
	logFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	logFont.lfQuality = PROOF_QUALITY;
	logFont.lfPitchAndFamily = VARIABLE_PITCH | FF_ROMAN;
	wcscpy_s(logFont.lfFaceName, _T("Arial"));//Times New Roman

}

CGDI3Doc::~CGDI3Doc()
{
}

BOOL CGDI3Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	//�������� ���������
	if (OnOpenDocument(L"scroll.ini")) 
	{
		return TRUE;
	}

	return TRUE;
}




// ������������ CGDI3Doc

void CGDI3Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring()) {
		ar << m_NumLines << m_Color;
		ar.Write(&logFont, sizeof(logFont));

	}
	else {
		ar >> m_NumLines >> m_Color;
		ar.Read(&logFont, sizeof(logFont));
	}
}

#ifdef SHARED_HANDLERS

// ��������� ��� �������
void CGDI3Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CGDI3Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������� ���������� ������ �� ������ ���������. 
	// ����� ����������� ������ ����������� ������ � ������� ";"

	// ��������:  strSearchContent = _T("�����;�������������;����;������ ole;");
	SetSearchContent(strSearchContent);
}

void CGDI3Doc::SetSearchContent(const CString& value)
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

// ����������� CGDI3Doc

#ifdef _DEBUG
void CGDI3Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGDI3Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// ������� CGDI3Doc
