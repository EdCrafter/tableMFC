#pragma once
#include "afxdialogex.h"


// CDialFont dialog

class CDialFont : public CDialogEx
{
	DECLARE_DYNAMIC(CDialFont)

public:
	CDialFont(LOGFONT& refFont, COLORREF& fgColor,CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDialFont();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	int fontSizeValue[16] = {8,10,11,12,14,16,18,20,22,24,26,28,36,48,72};
public:
	LOGFONT& font;
	CMFCFontComboBox fontFamily;
	CComboBox fontSize;
	CMFCColorButton fg;
	virtual BOOL OnInitDialog();
	CEdit exampleText;
	COLORREF& fgColor;
	afx_msg void OnCbnSelchangeMfcfontcombo1();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedMfccolorbutton1();
};
