
// GDI1View.h : интерфейс класса CGDI1View
//

#pragma once


class CGDI1View : public CView
{
protected: // создать только из сериализации
	CGDI1View();
	DECLARE_DYNCREATE(CGDI1View)

// Атрибуты
public:
	CGDI1Doc* GetDocument() const;
	CGDI1Doc* docum;
// Операции
public:
	int kod_graf;
	int kol_sec;
// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Реализация
public:
	virtual ~CGDI1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLines();
	afx_msg void OnFigures();
	afx_msg void OnText();
	afx_msg void OnText2();
};

#ifndef _DEBUG  // отладочная версия в GDI1View.cpp
inline CGDI1Doc* CGDI1View::GetDocument() const
   { return reinterpret_cast<CGDI1Doc*>(m_pDocument); }
#endif

