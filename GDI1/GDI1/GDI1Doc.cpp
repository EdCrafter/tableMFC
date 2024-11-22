
// GDI1Doc.cpp : реализация класса CGDI1Doc
//

#include "stdafx.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
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


// создание/уничтожение CGDI1Doc

CGDI1Doc::CGDI1Doc()
{
	// TODO: добавьте код для одноразового вызова конструктора
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

	// TODO: добавьте код повторной инициализации
	// (Документы SDI будут повторно использовать этот документ)

	return TRUE;
}




// сериализация CGDI1Doc

void CGDI1Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: добавьте код сохранения
	}
	else
	{
		// TODO: добавьте код загрузки
	}
}

#ifdef SHARED_HANDLERS

// Поддержка для эскизов
void CGDI1Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CGDI1Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// Задайте содержимое поиска из данных документа. 
	// Части содержимого должны разделяться точкой с запятой ";"

	// Например:  strSearchContent = _T("точка;прямоугольник;круг;объект ole;");
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

// диагностика CGDI1Doc

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


// команды CGDI1Doc
