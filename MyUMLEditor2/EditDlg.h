#pragma once


// CEditDlg ��ܤ��
class CCanvas;
class CEditDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEditDlg)

public:
	CEditDlg(CCanvas *m_view, CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~CEditDlg();

// ��ܤ�����
	enum { IDD = IDD_DIALOGEDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString m_Text;
	CCanvas *CanvasPtr; //CCanvas������
};
