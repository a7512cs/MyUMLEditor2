
// MyUMLEditor2Dlg.h : 標頭檔
//

#pragma once
#include "afxmenubutton.h"
#include "Canvas.h"
#include "afxwin.h"


class Mode;
class SelectMode;
class AssociationMode;
class GeneralizationMode;
class CompositionMode;
class ClassMode;
class UseCaseMode;

// CMainUMLEditorDlg 對話方塊
class CMainUMLEditorDlg : public CDialogEx
{
// 建構
public:
	CMainUMLEditorDlg(CWnd* pParent = NULL);	// 標準建構函式

// 對話方塊資料
	enum { IDD = IDD_MYUMLEDITOR2_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支援
	
// 程式碼實作
protected:
	HICON m_hIcon;

	// 產生的訊息對應函式
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	void SetViewSize();//設定畫布大小

//內建變數
public:
	afx_msg void OnEditEdittext(); //打開編輯文字的對話框
	afx_msg void OnBnClickedSelected();
	afx_msg void OnBnClickedLineori();
	afx_msg void OnBnClickedLinetriangle();
	afx_msg void OnBnClickedLinediamond();
	afx_msg void OnBnClickedRectangle();
	afx_msg void OnBnClickedCircle();
	CCanvas *m_view;//控制VIEW

	//六種按鈕
	CButton m_Select;
	CButton m_Line;
	CButton m_LineT;
	CButton m_LineD;
	CButton m_rectangle;
	CButton m_Circle;
	CRect rcPic;//畫布大小

	SelectMode *selectmode;
	AssociationMode *associationmode;
	GeneralizationMode *generalizationmode;
	CompositionMode *compositionmode;
	ClassMode *classmode;
	UseCaseMode *usecasemode;

//自定變數
public:
	void AllButtonEnable();
	afx_msg void OnEditGroup();
	afx_msg void OnEditUngroup();
};
