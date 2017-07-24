#pragma once


// CEditDlg 對話方塊
class CCanvas;
class CEditDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEditDlg)

public:
	CEditDlg(CCanvas *m_view, CWnd* pParent = NULL);   // 標準建構函式
	virtual ~CEditDlg();

// 對話方塊資料
	enum { IDD = IDD_DIALOGEDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString m_Text;
	CCanvas *CanvasPtr; //CCanvas的指標
};
