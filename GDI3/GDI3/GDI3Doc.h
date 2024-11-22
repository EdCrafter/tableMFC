
// GDI3Doc.h : ��������� ������ CGDI3Doc
//


#pragma once


class CGDI3Doc : public CDocument
{
protected: // ������� ������ �� ������������
	CGDI3Doc();
	DECLARE_DYNCREATE(CGDI3Doc)

// ��������
public:
	int m_NumLines;
	LOGFONT logFont;
	COLORREF m_Color;
// ��������
public:

// ���������������
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ����������
public:
	virtual ~CGDI3Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ��������� ������� ����� ���������
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ��������������� �������, �������� ���������� ������ ��� ����������� ������
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
