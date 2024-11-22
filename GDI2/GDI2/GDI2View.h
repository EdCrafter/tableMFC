
// GDI2View.h : ��������� ������ CGDI2View
//

#pragma once


class CGDI2View : public CView
{
protected: // ������� ������ �� ������������
	CGDI2View();
	DECLARE_DYNCREATE(CGDI2View)

// ��������
public:
	CGDI2Doc* GetDocument() const;
	int		nBrushStyle;
// ��������
public:

// ���������������
public:
	virtual void OnDraw(CDC* pDC);  // �������������� ��� ��������� ����� �������������
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ����������
public:
	virtual ~CGDI2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ��������� ������� ����� ���������
protected:
	afx_msg void OnFilePrintPreview();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // ���������� ������ � GDI2View.cpp
inline CGDI2Doc* CGDI2View::GetDocument() const
   { return reinterpret_cast<CGDI2Doc*>(m_pDocument); }
#endif

