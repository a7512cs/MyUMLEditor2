#include "stdafx.h"
#include "GroupObject.h"
//#include "Shape.h"
#include <vector>
using namespace std;




GroupObject::GroupObject()
	: Shape()	
	, StartPosition(0,0)
	, ShapeSize(0, 0)
{
	HasChildren = TRUE;
	//AfxMessageBox(_T("GroupObject Con.."));
}
GroupObject::GroupObject(GroupObject &S)
	: Shape(S)
{
	//AfxMessageBox(_T("GroupObject Copy Con.."));
}
GroupObject::~GroupObject()
{
	//AfxMessageBox(_T("GroupObject Desty.."));
}

void GroupObject::GetChileren(vector<Shape*> &child)
{
	for (int i = 0; i < (int)GroupObj.size(); i++)
	{
		child.push_back(GroupObj[i]);
	}
}
void GroupObject::Draw(CDC* pDC)
{	
	for (int i = 0; i < (int)GroupObj.size(); i++)
	{
			GroupObj[i]->Draw(pDC);
	}
	
	if (IsSelected())
	{
		CPen pen(PS_DOT, 1, RGB(20, 20, 20));//創立一個畫筆
		pDC->SelectObject(&pen);
		CPoint P1, P2;
		P1 = GetStartPt();
		P2 = GetEndPt();
		pDC->MoveTo(P1);
		pDC->LineTo(P1.x, P2.y);
		pDC->LineTo(P2);
		pDC->LineTo(P2.x,P1.y);
		pDC->LineTo(P1);
	}
}
BOOL GroupObject::IsPointInside(CPoint pt)
{
	if (pt.x>StartPosition.x && pt.x < StartPosition.x + ShapeSize.x
		&& pt.y>StartPosition.y && pt.y < StartPosition.y + ShapeSize.y
		)
	{
		return TRUE;
	}
	return FALSE;
}
BOOL GroupObject::IsInsideRegin(CPoint pt1, CPoint pt2)
{
	if (GetStartPt().x > pt1.x
		&& GetEndPt().x < pt2.x
		&& GetStartPt().y > pt1.y
		&& GetEndPt().y < pt2.y
		)
	{
		return TRUE;
	}
	return FALSE;
}


CPoint GroupObject::GetStartPt(){ return StartPosition; };
CPoint GroupObject::GetEndPt(){ return StartPosition + ShapeSize ; };
ConnectPort* GroupObject::GetPort(int n){ return NULL; };
int GroupObject::GetPortNum(){ return 0; };
void GroupObject::ObjMove(CPoint dis)
{
	int n = GroupObj.size();
	for (int i = 0; i < n; i++)
	{
		GroupObj[i]->ObjMove(dis);
	}
	CalculateBBX();
}
void GroupObject::ChangeName(CString st)
{
	//do nothing
}
void GroupObject::CalculateBBX()
{
	CPoint LT(999999999, 999999999), RB(-1, -1);
	int g = GroupObj.size();
	for (int i = 0; i < g; i++)
	{
		int tmp_X = GroupObj[i]->GetStartPt().x;
		int tmp_X2 = GroupObj[i]->GetEndPt().x;
		if (tmp_X < LT.x)
		{
			LT.x = tmp_X;
		}
		if (tmp_X2 > RB.x)
		{
			RB.x = tmp_X2;
		}

		int tmp_Y1 = GroupObj[i]->GetStartPt().y;
		int tmp_Y2 = GroupObj[i]->GetEndPt().y;
		if (tmp_Y1 < LT.y)
		{
			LT.y = tmp_Y1;
		}
		if (tmp_Y2 > RB.y)
		{
			RB.y = tmp_Y2;
		}
	}

	StartPosition = LT;
	ShapeSize = RB - LT;
}


void GroupObject::AddGroup(vector<Shape*> Obj)
{
	int n = Obj.size();
	for (int i = 0; i < n; i++)
	{
		GroupObj.push_back(Obj[i]);
	}
}


