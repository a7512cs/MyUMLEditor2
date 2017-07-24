
#pragma once
#include "stdafx.h"
#include "Mode.h"
#include "MyUMLEditor2.h"
#include "Canvas.h"
#include "afxdialogex.h"
#include "GroupObject.h"

IMPLEMENT_DYNCREATE(CCanvas, CView)

BEGIN_MESSAGE_MAP(CCanvas, CView)
	ON_WM_MOUSEACTIVATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


CCanvas::CCanvas()
{

}
CCanvas::~CCanvas()
{
	for (int i = 0; i < (int)AllObj.size(); i++)
	{
		delete AllObj[i];
	}
};
void CCanvas::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	//以下為繪圖區的程式碼

	DrawAll(pDC);	
}
void CCanvas::SetCurrentMode(Mode* mode)
{
	CurrentMode = mode;
}
Mode* CCanvas::GetCurrentMode()
{
	return CurrentMode; 
}
void CCanvas::OnLButtonDown(UINT nFlags, CPoint point)
{
	CurrentMode->MousePress(point);
	
	Invalidate(FALSE);
	CView::OnLButtonDown(nFlags, point);
}

void CCanvas::OnMouseMove(UINT nFlags, CPoint point)
{
	CurrentMode->MouseMove(point);
	
	Invalidate(FALSE);
	CView::OnMouseMove(nFlags, point);
}

void CCanvas::OnLButtonUp(UINT nFlags, CPoint point)
{
	CurrentMode->MouseRelease(point);
	

	Invalidate(FALSE);
	CView::OnLButtonUp(nFlags, point);
}

void CCanvas::AddObj(Shape* shp)
{
	AllObj.push_back(shp);
}

Shape* CCanvas::RemoveObj(int i)
{
	if (i < 0 || i >= (int)AllObj.size())
	{
		AfxMessageBox(_T("ERROR: remove a wrong element in the AllObj."));
		return NULL;
	}
	else
	{
		Shape* ret = AllObj[i];
		ret->SetSelect(FALSE);
		AllObj.erase(AllObj.begin() + i);
		return ret;
	}
}
Shape* CCanvas::RemoveObj(Shape* shp)
{
	for (int i = (int)AllObj.size() - 1; i >= 0; i--)
	{
		if (AllObj[i] == shp)
		{
			return RemoveObj(i);
		}
	}
	return NULL;
}
vector<Shape*> CCanvas::GetSelectedObj()
{
	vector<Shape*> retShp;
	int num = AllObj.size();
	for (int i = 0; i < num; i++)
	{
		if (AllObj[i]->IsSelected() == TRUE)
		{
			retShp.push_back(AllObj[i]);
		}
	}
	return retShp;
}
void CCanvas::Group() 
{
	vector<Shape*> tempObj = GetSelectedObj();
	if (tempObj.size()<2)
	{
		AfxMessageBox(_T("Please select more than one Pic."));
		return;
	}
	for (int i = 0; i < (int)tempObj.size(); i++)
	{
		RemoveObj(tempObj[i]);
	}
	GroupObject *G = new GroupObject();
	G->AddGroup(tempObj);
	G->CalculateBBX();
	AddObj(G);
	ClearAllSelectedObj();
}
void CCanvas::Ungroup()
{
	vector<Shape*> tempObj = GetSelectedObj();
	if (tempObj.size() != 1 || tempObj[0]->HasChildren == FALSE)
	{
		AfxMessageBox(_T("Please select one Group."));
		return;
	}
	vector<Shape*> child;
	tempObj[0]->GetChileren(child);
	RemoveObj(tempObj[0]);
	for (int i = 0; i < (int)child.size(); i++)
	{
		AddObj(child[i]);
	}
	child.clear();
	delete tempObj[0];
	ClearAllSelectedObj();
}

void CCanvas::DrawAll(CDC* pDC)//畫出全部物件
{
	//先全部清空 再畫上新的物件
	CleanAllCan(pDC);

	int num = AllObj.size();
	for (int i = 0; i <num; i++)
	{
		AllObj[i]->Draw(pDC);
	}

}
void CCanvas::CleanAllCan(CDC* pDC)
{
    CPoint p1(0, 0), p2(CanvasRc.Width(), CanvasRc.Height());
    CRect rect(p1, p2);
    CPen pen(PS_NULL, 1, RGB(0, 0, 0));//創立一個畫筆
    CBrush BrushWhite(RGB(255, 255, 255));//填滿白色畫刷
    pDC->SelectObject(&pen);
    pDC->SelectObject(&BrushWhite);//白色實心
    pDC->Rectangle(rect);
}
Shape* CCanvas::InWhichShape(CPoint point)
{
	int num = AllObj.size();
	for (int i = num - 1; i >= 0; i--)
	{
		if (AllObj[i]->IsPointInside(point))
		{
			return AllObj[i];
		}
	}
	return NULL;
}



vector<Shape*> CCanvas::GetInsideObject(CPoint point1, CPoint point2)
{
	vector<Shape*> Objs;
	for (int i = 0; i < (int)AllObj.size(); i++)
	{
		if (AllObj[i]->IsInsideRegin(point1, point2))
		{
			Objs.push_back(AllObj[i]);
		}
	}
	return Objs;
}
void CCanvas::SelectedMove(CPoint dis)
{
	int num = AllObj.size();
	for (int i = 0; i < num; i++)
	{
		if (AllObj[i]->IsSelected() == TRUE)
		{
			AllObj[i]->ObjMove(dis);
		}
	}
}
void CCanvas::ClearAllSelectedObj()
{
	int num = AllObj.size();

	for (int i = 0; i < num; i++)
	{
		AllObj[i]->SetSelect(FALSE);
	}
}





