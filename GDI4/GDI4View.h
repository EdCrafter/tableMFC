
// GDI4View.h : интерфейс класса CTableView
//

#pragma once
#include "GDI4Doc.h"
#include <string>
#include "CTable.h"


class CTableView : public CScrollView
{
protected: // создать только из сериализации
	CTableView();
	DECLARE_DYNCREATE(CTableView)

// Атрибуты
public:
	CTableDoc* GetDocument() const;
	
	//Пользовательская функция вывода ячейки
	void DrawCell(CDC*, CString, LPRECT, UINT, UINT, int tol = 1, COLORREF t = 0);

// Операции
public:
	CTable table;
// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // вызывается в первый раз после конструктора
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Реализация
public:
	virtual ~CTableView();
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
};

#ifndef _DEBUG  // отладочная версия в GDI4View.cpp
inline CTableDoc* CTableView::GetDocument() const
   { return reinterpret_cast<CTableDoc*>(m_pDocument); }
#endif

