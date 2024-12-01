#include "stdafx.h"
#include "GDI4.h"
#include "afxdialogex.h"
#include "CDialFont.h"

IMPLEMENT_DYNAMIC(CDialFont, CDialogEx)

CDialFont::CDialFont(LOGFONT& refFont, COLORREF& fgColor,CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent), font(refFont), fgColor(fgColor)
{

}

CDialFont::~CDialFont()
{
}

void CDialFont::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCFONTCOMBO1, fontFamily);
	DDX_Control(pDX, IDC_COMBO1, fontSize);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, fg);
	DDX_Control(pDX, IDC_INSTTEXT, exampleText);
}


BEGIN_MESSAGE_MAP(CDialFont, CDialogEx)
	ON_CBN_SELCHANGE(IDC_MFCFONTCOMBO1, &CDialFont::OnCbnSelchangeMfcfontcombo1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDialFont::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON1, &CDialFont::OnBnClickedMfccolorbutton1)
END_MESSAGE_MAP()


// CDialFont message handlers


BOOL CDialFont::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	fontFamily.SelectFont(font.lfFaceName);
	int fS = -MulDiv(font.lfHeight, 72, 192);
	bool found = false;
	CString str;
	int ind = 0;
	for (int i = 0; fontSizeValue[i]; i++) {
		str.Format(L"%d", fontSizeValue[i]);
		fontSize.AddString(str);
		if (fontSizeValue[i] == fS) {
			ind = i;
			found = true;
		}
		else if (fontSizeValue[i] > fS && !found) {
			ind = i - 1;
			found = true;
		}
	}
	fontSize.SetCurSel(ind);
	fg.SetColor(fgColor);
	CFont customFont;
	if (customFont.CreateFontIndirect(&font))
	{
		exampleText.SetFont(&customFont);
	}

	exampleText.SetWindowTextW(L"AaBbGgYyWw");

	return TRUE; 
}



void CDialFont::OnCbnSelchangeMfcfontcombo1()
{
	CString str;
	fontFamily.GetLBText(fontFamily.GetCurSel(), str);
	wcscpy_s(font.lfFaceName, str);

	int ind = fontSize.GetCurSel();
	int fS = fontSizeValue[ind];
	font.lfHeight = -MulDiv(fS, 192, 72);
	CFont customFont;
	if (customFont.CreateFontIndirect(&font))
	{
		exampleText.SetFont(&customFont);
	}

}


void CDialFont::OnCbnSelchangeCombo1()
{
	int ind = fontSize.GetCurSel();
	int fS = fontSizeValue[ind];
	font.lfHeight = -MulDiv(fS, 192, 72);
	CFont customFont;
	if (customFont.CreateFontIndirect(&font))
	{
		exampleText.SetFont(&customFont);
	}
}


void CDialFont::OnBnClickedMfccolorbutton1()
{
	fgColor = fg.GetColor();
	/*CFont customFont;
	if (customFont.CreateFontIndirect(&font))
	{
		exampleText.SetFont(&customFont);
	}*/
}
