
// GDI4View.h : ��������� ������ CTableView
//

#pragma once
#include "GDI4Doc.h"
#include <string>
#include "CTable.h"


class CTableView : public CScrollView
{
protected: // ������� ������ �� ������������
	CTableView();
	DECLARE_DYNCREATE(CTableView)

// ��������
public:
	CTableDoc* GetDocument() const;
	
	//���������������� ������� ������ ������
	void DrawCell(CDC*, CString, LPRECT, UINT, UINT, int tol = 1, COLORREF t = 0);

// ��������
public:
	CTable table;
// ���������������
public:
	virtual void OnDraw(CDC* pDC);  // �������������� ��� ��������� ����� �������������
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ���������� � ������ ��� ����� ������������
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ����������
public:
	virtual ~CTableView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ��������� ������� ����� ���������
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // ���������� ������ � GDI4View.cpp
inline CTableDoc* CTableView::GetDocument() const
   { return reinterpret_cast<CTableDoc*>(m_pDocument); }
#endif

