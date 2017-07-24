// EditDlg.cpp : 實作檔
//

#include "stdafx.h"
#include "MyUMLEditor2.h"
#include "EditDlg.h"
#include "afxdialogex.h"
#include "Canvas.h"
#include "GroupObject.h"
#include <vector>
using namespace std;

// CEditDlg 對話方塊

IMPLEMENT_DYNAMIC(CEditDlg, CDialogEx)

CEditDlg::CEditDlg(CCanvas *m_view, CWnd* pParent /*=NULL*/)
	: CDialogEx(CEditDlg::IDD, pParent)
	, m_Text(_T(""))
{
	CanvasPtr = m_view;
}

CEditDlg::~CEditDlg()
{
}

void CEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Text);
}


BEGIN_MESSAGE_MAP(CEditDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CEditDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CEditDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CEditDlg 訊息處理常式


void CEditDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	vector<Shape*> tempObj = CanvasPtr->GetSelectedObj();
	tempObj[0]->ChangeName(m_Text);
	CDialogEx::OnOK();
}


void CEditDlg::OnBnClickedCancel()
{
	// DO nothing
	CDialogEx::OnCancel();
}
