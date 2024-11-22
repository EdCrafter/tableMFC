
// GDI3Doc.cpp : реализация класса CGDI3Doc
//

#include "stdafx.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
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


// создание/уничтожение CGDI3Doc

CGDI3Doc::CGDI3Doc()
{
	// Инициализация данных

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

	//Открытие документа
	if (OnOpenDocument(L"scroll.ini")) 
	{
		return TRUE;
	}

	return TRUE;
}




// сериализация CGDI3Doc

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

// Поддержка для эскизов
void CGDI3Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Измените этот код для отображения данных документа
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

// Поддержка обработчиков поиска
void CGDI3Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// Задайте содержимое поиска из данных документа. 
	// Части содержимого должны разделяться точкой с запятой ";"

	// Например:  strSearchContent = _T("точка;прямоугольник;круг;объект ole;");
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

// диагностика CGDI3Doc

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


// команды CGDI3Doc
