#pragma once


// ���������� ���� CBrushDialog

class CBrushDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CBrushDialog)

public:
	CBrushDialog(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~CBrushDialog();
	int		m_nBrush;
// ������ ����������� ����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
};
