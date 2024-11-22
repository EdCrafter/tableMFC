
// GDI3Doc.h : интерфейс класса CGDI3Doc
//


#pragma once


class CGDI3Doc : public CDocument
{
protected: // создать только из сериализации
	CGDI3Doc();
	DECLARE_DYNCREATE(CGDI3Doc)

// Атрибуты
public:
	int m_NumLines;
	LOGFONT logFont;
	COLORREF m_Color;
// Операции
public:

// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Реализация
public:
	virtual ~CGDI3Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
