
// MyUMLEditor2Dlg.cpp : 實作檔
//

#include "stdafx.h"
#include "Mode.h"
#include "MyUMLEditor2.h"
#include "MainUMLEditorDlg.h"
#include "afxdialogex.h"
#include "EditDlg.h"
//#include "Shape.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainUMLEditorDlg 對話方塊
CMainUMLEditorDlg::CMainUMLEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMainUMLEditorDlg::IDD, pParent)	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	selectmode = NULL;
	associationmode = NULL;
	generalizationmode = NULL;
	compositionmode = NULL;
	classmode = NULL;
	usecasemode = NULL;
}

void CMainUMLEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Rectangle, m_rectangle);
	DDX_Control(pDX, IDC_Circle, m_Circle);
	DDX_Control(pDX, IDC_LineDiamond, m_LineD);
	DDX_Control(pDX, IDC_LineTriangle, m_LineT);
	DDX_Control(pDX, IDC_LineOri, m_Line);
	DDX_Control(pDX, IDC_Selected, m_Select);
}

BEGIN_MESSAGE_MAP(CMainUMLEditorDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_EDIT_EDITTEXT, &CMainUMLEditorDlg::OnEditEdittext)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_Rectangle, &CMainUMLEditorDlg::OnBnClickedRectangle)
	ON_BN_CLICKED(IDC_Selected, &CMainUMLEditorDlg::OnBnClickedSelected)
	ON_BN_CLICKED(IDC_LineOri, &CMainUMLEditorDlg::OnBnClickedLineori)
	ON_BN_CLICKED(IDC_LineTriangle, &CMainUMLEditorDlg::OnBnClickedLinetriangle)
	ON_BN_CLICKED(IDC_LineDiamond, &CMainUMLEditorDlg::OnBnClickedLinediamond)
	ON_BN_CLICKED(IDC_Circle, &CMainUMLEditorDlg::OnBnClickedCircle)
	ON_COMMAND(ID_EDIT_GROUP, &CMainUMLEditorDlg::OnEditGroup)
	ON_COMMAND(ID_EDIT_UNGROUP, &CMainUMLEditorDlg::OnEditUngroup)
END_MESSAGE_MAP()


// CMainUMLEditorDlg 訊息處理常式

BOOL CMainUMLEditorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	//Canvas畫布的初始設定
	CRect rect;
	CRuntimeClass *pViewClass;
	pViewClass = RUNTIME_CLASS(CCanvas);
	CWnd *pWnd = (CWnd *)pViewClass->CreateObject();
	CCreateContext pContext;
	pContext.m_pNewViewClass = pViewClass;
	m_view = (CCanvas *)pWnd;
	m_view->Create(NULL, _T("2D_VIEW"),
		WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPCHILDREN,
		rect, this, IDC_PictureShown, &pContext);
	SetViewSize();//設定Canvas大小

	OnBnClickedSelected();
	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CMainUMLEditorDlg::OnPaint()
{

	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CMainUMLEditorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMainUMLEditorDlg::SetViewSize()
{
	CWnd *pWnd;
	CRect rFrame, rRect;
	pWnd = GetDlgItem(IDC_PictureShown);
	pWnd->GetWindowRect(&rFrame);
	m_view->GetWindowRect(&rRect);
	ScreenToClient(rFrame);
	m_view->SetWindowPos(NULL, rFrame.left, rFrame.top, rFrame.Width(), rFrame.Height(),
		SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_NOACTIVATE);
	pWnd->GetClientRect(rcPic);//抓畫布大小
	m_view->CanvasRc = rcPic;
}




//打開編輯文字的對話框
void CMainUMLEditorDlg::OnEditEdittext()
{	
	vector<Shape*> tempObj = m_view->GetSelectedObj();
	if (tempObj.size() != 1)
	{
		AfxMessageBox(_T("Please select one Pic, and only."));
		return;
	}
	else
	{//打開編輯文字的對話框
		CEditDlg EditDlg(m_view);
		EditDlg.DoModal();
	}
}
void CMainUMLEditorDlg::OnEditGroup()
{
	m_view->Group();
}

void CMainUMLEditorDlg::OnEditUngroup()
{
	m_view->Ungroup();	
}

void CMainUMLEditorDlg::OnBnClickedSelected()
{
	AllButtonEnable();
	m_Select.EnableWindow(FALSE);

	if (selectmode == NULL)
	{
		selectmode = new SelectMode(m_view);
	}
	m_view->SetCurrentMode(selectmode);
}

void CMainUMLEditorDlg::OnBnClickedLineori()
{
	AllButtonEnable();
	m_Line.EnableWindow(FALSE);

	if (associationmode == NULL)
	{
		associationmode = new AssociationMode(m_view);
	}
	m_view->SetCurrentMode(associationmode);
}

void CMainUMLEditorDlg::OnBnClickedLinetriangle()
{
	AllButtonEnable();
	m_LineT.EnableWindow(FALSE);

	if (generalizationmode == NULL)
	{
		generalizationmode = new GeneralizationMode(m_view);
	}
	m_view->SetCurrentMode(generalizationmode);
}

void CMainUMLEditorDlg::OnBnClickedLinediamond()
{
	AllButtonEnable();
	m_LineD.EnableWindow(FALSE);

	if (compositionmode == NULL)
	{
		compositionmode = new CompositionMode(m_view);
	}
	m_view->SetCurrentMode(compositionmode);
}

void CMainUMLEditorDlg::OnBnClickedRectangle()
{
	AllButtonEnable();
	m_rectangle.EnableWindow(FALSE);

	if (classmode == NULL)
	{
		classmode = new ClassMode(m_view);
	}
	m_view->SetCurrentMode(classmode);
}

void CMainUMLEditorDlg::OnBnClickedCircle()
{
	AllButtonEnable();
	m_Circle.EnableWindow(FALSE);

	if (usecasemode == NULL)
	{
		usecasemode = new UseCaseMode(m_view);
	}
	m_view->SetCurrentMode(usecasemode);
}

void CMainUMLEditorDlg::AllButtonEnable()
{
	m_Select.EnableWindow(TRUE);
	m_Line.EnableWindow(TRUE);
	m_LineT.EnableWindow(TRUE);
	m_LineD.EnableWindow(TRUE);
	m_rectangle.EnableWindow(TRUE);
	m_Circle.EnableWindow(TRUE);
	m_view->ClearAllSelectedObj();
}




