// BrushDialog.cpp: файл реализации
//

#include "stdafx.h"
#include "BrushDialog.h"
#include "afxdialogex.h"
#include "Resource.h"

// диалоговое окно CBrushDialog

IMPLEMENT_DYNAMIC(CBrushDialog, CDialogEx)

CBrushDialog::CBrushDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_BRUSH_DIALOG)
{
	//m_nBrush = -1;
}

CBrushDialog::~CBrushDialog()
{
}

void CBrushDialog::DoDataExchange(CDataExchange* pDX)
{
	DDX_Radio(pDX, IDC_RADIO1, m_nBrush);
	CDialogEx::DoDataExchange(pDX);
	CString vv;
	vv.Format(L"  %d ", m_nBrush);

	AfxMessageBox(vv);


}


BEGIN_MESSAGE_MAP(CBrushDialog, CDialogEx)
END_MESSAGE_MAP()


// обработчики сообщений CBrushDialog
