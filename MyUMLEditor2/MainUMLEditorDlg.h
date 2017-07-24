
// MyUMLEditor2Dlg.h : ���Y��
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

// CMainUMLEditorDlg ��ܤ��
class CMainUMLEditorDlg : public CDialogEx
{
// �غc
public:
	CMainUMLEditorDlg(CWnd* pParent = NULL);	// �зǫغc�禡

// ��ܤ�����
	enum { IDD = IDD_MYUMLEDITOR2_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �䴩
	
// �{���X��@
protected:
	HICON m_hIcon;

	// ���ͪ��T�������禡
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	void SetViewSize();//�]�w�e���j�p

//�����ܼ�
public:
	afx_msg void OnEditEdittext(); //���}�s���r����ܮ�
	afx_msg void OnBnClickedSelected();
	afx_msg void OnBnClickedLineori();
	afx_msg void OnBnClickedLinetriangle();
	afx_msg void OnBnClickedLinediamond();
	afx_msg void OnBnClickedRectangle();
	afx_msg void OnBnClickedCircle();
	CCanvas *m_view;//����VIEW

	//���ث��s
	CButton m_Select;
	CButton m_Line;
	CButton m_LineT;
	CButton m_LineD;
	CButton m_rectangle;
	CButton m_Circle;
	CRect rcPic;//�e���j�p

	SelectMode *selectmode;
	AssociationMode *associationmode;
	GeneralizationMode *generalizationmode;
	CompositionMode *compositionmode;
	ClassMode *classmode;
	UseCaseMode *usecasemode;

//�۩w�ܼ�
public:
	void AllButtonEnable();
	afx_msg void OnEditGroup();
	afx_msg void OnEditUngroup();
};
