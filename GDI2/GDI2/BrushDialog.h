#pragma once


// диалоговое окно CBrushDialog

class CBrushDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CBrushDialog)

public:
	CBrushDialog(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CBrushDialog();
	int		m_nBrush;
// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
};
