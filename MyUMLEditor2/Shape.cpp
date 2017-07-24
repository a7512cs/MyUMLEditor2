#include "stdafx.h"
#include "Shape.h"
#include "ConnectedPort.h"


Shape::Shape()
	: HasChildren(FALSE)
	, Selected(FALSE)
{
	//AfxMessageBox(_T("Shape Con.."));
}
Shape::Shape(Shape &G)
{
	//AfxMessageBox(_T("Shape Copy Con.."));
}
Shape &Shape::operator = (Shape &G)
{
	//AfxMessageBox(_T("Shape oper="));
	return *this;
}
Shape::~Shape()
{
	//AfxMessageBox(_T("Shape Desty.."));
}
BOOL Shape::IsSelected()
{
	return Selected;
}
void Shape::SetSelect(BOOL b)
{
	Selected = b;
}



BasicObject::BasicObject(CPoint SP)
	: Shape()
	, StartPosition(SP)
	, ShapeSize(10, 10)
	, Title(_T("empty"))
	, ConPtNum(4)
{
	//AfxMessageBox(_T("BasicObject Con.."));
}
BasicObject::BasicObject(BasicObject &S)
	: Shape(S)
{
	StartPosition = S.StartPosition;
	ShapeSize = S.ShapeSize;
	Title = S.Title;
	ConPtNum = S.ConPtNum;
	//AfxMessageBox(_T("CShape Copy Con.."));
}
BasicObject &BasicObject::operator = (BasicObject &S)
{
	StartPosition = S.StartPosition;
	Title = S.Title;
	ShapeSize = S.ShapeSize;
	//AfxMessageBox(_T("CShape oper="));
	return *this;
}
BasicObject::~BasicObject()
{
	delete[]ports;
	//AfxMessageBox(_T("BasicObject Desty.."));
}
int BasicObject::GetPortNum()
{
	return ConPtNum;
}
void BasicObject::GetChileren(vector<Shape*> &child)
{
}
CPoint BasicObject::GetStartPt()
{ 
	return StartPosition;
}
CPoint BasicObject::GetEndPt()
{
	return StartPosition + ShapeSize; 
}
void BasicObject::ChangeName(CString st)
{
	Title = st; 
}


void BasicObject::SetPortNumber(int n)
{
	ports = new ConnectPort[n];
	for (int i = 0; i < n; i++)
	{
		ports[i].SetBasic(this);
	}

}
void BasicObject::GetConnectPort(int n)
{
	int midx = (GetEndPt().x - GetStartPt().x) / 2;//=ShapeSize/2
	int midy = (GetEndPt().y - GetStartPt().y) / 2;
	//top		
	ports[0].SetRelation(midx, 0);
	//left
	ports[1].SetRelation(0, midy);
	//bot
	ports[2].SetRelation(midx, ShapeSize.y);
	//right
	ports[3].SetRelation(ShapeSize.x, midy);
	//ports[3].SetPoint(0, midy);
}
ConnectPort* BasicObject::GetPort(int n)
{
	if (n >= ConPtNum || n<0)
	{
		return NULL;
	}
	return &(ports[n]);
}

BOOL BasicObject::IsPointInside(CPoint pt) {
	if (pt.x > StartPosition.x && pt.x < StartPosition.x + ShapeSize.x
		&& pt.y>StartPosition.y && pt.y < StartPosition.y + ShapeSize.y
		)
	{
		return TRUE;
	}
	return FALSE;
}
BOOL BasicObject::IsInsideRegin(CPoint pt1, CPoint pt2)
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
void BasicObject::ObjMove(CPoint dis)
{
	StartPosition = StartPosition + dis;
}


ClassBox::ClassBox(CPoint SP)
	: BasicObject(SP)
{
	ShapeSize.x = 60;
	ShapeSize.y = 75;

	SetPortNumber(ConPtNum);
	GetConnectPort(ConPtNum);
	//AfxMessageBox(_T("ClassBox Con.."));
}
ClassBox::ClassBox(ClassBox &S)
	: BasicObject(S)
{
	//AfxMessageBox(_T("ClassBox Copy Con.."));
}
ClassBox &ClassBox::operator= (ClassBox &S)
{
	StartPosition = S.StartPosition;
	Title = S.Title;
	ShapeSize = S.ShapeSize;
	//AfxMessageBox(_T("ClassBox oper="));
	return *this;
}
ClassBox::~ClassBox()
{
	//AfxMessageBox(_T("ClassBox Desty.."));
}
void ClassBox::Draw(CDC* pDC)
{
	if (Selected == TRUE)
	{
		for (int i = 0; i < ConPtNum; i++)
		{
			GetPort(i)->ShowConnectPoint(pDC);
		}
	}
	this->ShowRec(pDC);//draw class
	this->ShowTitle(pDC);
	
}
void ClassBox::ShowTitle(CDC* pDC)
{
	CFont text1;
	pDC->SetTextColor(RGB(250, 0, 0)); //按下後的文字顏色 紅色
	pDC->SelectObject(&text1);
	pDC->TextOut(StartPosition.x + 5, StartPosition.y + 5, Title);
}
void ClassBox::ShowRec(CDC* pDC)
{
	CPoint EndPosition = StartPosition + ShapeSize;
	CRect rect(StartPosition, EndPosition);
	CPen pen(PS_SOLID, 3, RGB(255, 0, 0));//創立一個畫筆
	CBrush BrushWhite(RGB(255, 255, 255));//填滿白色畫刷
	pDC->SelectObject(&pen);
	pDC->SelectObject(&BrushWhite);//白色實心
	pDC->Rectangle(rect);
	pDC->MoveTo(StartPosition.x, StartPosition.y + ShapeSize.y / 3);//起始點
	pDC->LineTo(EndPosition.x, StartPosition.y + ShapeSize.y / 3);//終點
	pDC->MoveTo(StartPosition.x, StartPosition.y + ShapeSize.y / 3 * 2);//起始點
	pDC->LineTo(EndPosition.x, StartPosition.y + ShapeSize.y / 3 * 2);//終點
}

UseCaseBox::UseCaseBox(CPoint SP)
	: BasicObject(SP)
{
	ShapeSize.x = 60;
	ShapeSize.y = 40;

	SetPortNumber(ConPtNum);
	GetConnectPort(ConPtNum);
	//AfxMessageBox(_T("UseCaseBox Con.."));
}
UseCaseBox::UseCaseBox(UseCaseBox &S)
	: BasicObject(S)
{
	//AfxMessageBox(_T("UseCaseBox Copy Con.."));
}
UseCaseBox &UseCaseBox::operator = (UseCaseBox &S)
{
	StartPosition = S.StartPosition;
	Title = S.Title;
	ShapeSize = S.ShapeSize;
	//AfxMessageBox(_T("UseCaseBox oper="));
	return *this;
}
UseCaseBox::~UseCaseBox()
{
	//AfxMessageBox(_T("CShapeCircle Desty.."));
}
void UseCaseBox::Draw(CDC* pDC)
{
	if (Selected == TRUE)
	{
		for (int i = 0; i < ConPtNum; i++)
		{
			GetPort(i)->ShowConnectPoint(pDC);
		}
	}

	CRect rect(StartPosition, StartPosition + ShapeSize);
	CPen pen(PS_SOLID, 3, RGB(255, 0, 0));//創立一個畫筆
	CBrush BrushWhite(RGB(255, 255, 255));//填滿白色畫刷
	pDC->SelectObject(&BrushWhite);//白色實心
	pDC->SelectObject(&pen);
	pDC->Ellipse(rect);

	this->ShowTitle(pDC);

}
void UseCaseBox::ShowTitle(CDC* pDC)
{
	CFont text1;
	pDC->SetTextColor(RGB(0, 250, 0)); //按下後的文字顏色 綠色
	pDC->SelectObject(&text1);
	pDC->TextOut(StartPosition.x + 10, StartPosition.y + 10, Title);
};


LineObject::LineObject(Shape* sp1, Shape*sp2)
	:Shape()
{
	//AfxMessageBox(_T("LineObject  2 shpae* Con.."));
}
LineObject::LineObject(LineObject &S)
	: Shape()
	, StartPort(S.StartPort)
	, EndPort(S.EndPort)
{
	//AfxMessageBox(_T("CLine Copy Con.."));
}
LineObject &LineObject::operator = (LineObject &S)
{
	//AfxMessageBox(_T("CLine oper="));
	return *this;
}
LineObject::~LineObject()
{
	//AfxMessageBox(_T("CLine Desty.."));
}
ConnectPort* LineObject::GetPort(int n)
{
	return NULL;
}
void LineObject::GetChileren(vector<Shape*> &child)
{
}
BOOL LineObject::IsPointInside(CPoint pt1)
{
	return FALSE;
	//cannot choose line
}
BOOL LineObject::IsInsideRegin(CPoint pt1, CPoint pt2)
{
	return FALSE;
	//cannot choose line
}
int LineObject::GetPortNum()//return 0 因為不用寫
{
	return 0; 
}
void LineObject::ObjMove(CPoint dis)
{
}
void LineObject::SetCloestPortInLine(Shape* Shp1, Shape* Shp2)//更新連接點的位置
{
	int SP, EP;
	CPoint cp1;
	
	cp1.SetPoint((Shp1->GetStartPt().x + Shp1->GetEndPt().x) / 2,
		(Shp1->GetStartPt().y + Shp1->GetEndPt().y) / 2);
	CPoint cp2;
	cp2.SetPoint((Shp2->GetStartPt().x + Shp2->GetEndPt().x) / 2,
		(Shp2->GetStartPt().y + Shp2->GetEndPt().y) / 2);

	double dis = 999999999999999;
	double temp;
	for (int i = 0; i < Shp1->GetPortNum(); i++)
	{
		temp = (Shp1->GetPort(i)->GetPoint().x - cp2.x)*(Shp1->GetPort(i)->GetPoint().x - cp2.x) +
			(Shp1->GetPort(i)->GetPoint().y - cp2.y)*(Shp1->GetPort(i)->GetPoint().y - cp2.y);
		if (temp < dis)
		{
			SP = i;
			dis = temp;
		}
	}
	dis = 999999999999999;
	for (int i = 0; i < Shp2->GetPortNum(); i++)
	{
		temp = (Shp2->GetPort(i)->GetPoint().x - cp1.x)*(Shp2->GetPort(i)->GetPoint().x - cp1.x) +
			(Shp2->GetPort(i)->GetPoint().y - cp1.y)*(Shp2->GetPort(i)->GetPoint().y - cp1.y);
		if (temp < dis)
		{
			EP = i;
			dis = temp;
		}
	}
// 	Shape1_SP = SP;//為了讓現有轉折 所以增加這項 不好
// 	Shape2_EP = EP;
	StartPort = Shp1->GetPort(SP);
	EndPort = Shp2->GetPort(EP); 
}
CPoint LineObject::GetStartPt()
{
	return StartPort->GetPoint();
}
CPoint LineObject::GetEndPt()
{
	return EndPort->GetPoint();
}
void LineObject::ChangeName(CString st)
{
	//do nothing
}
void LineObject::ZZLine_TopDown(CDC* pDC)
{
	CPoint pt;
	pt.SetPoint(StartPort->GetPoint().x,
		(StartPort->GetPoint().y + EndPort->GetPoint().y) / 2);
	pDC->LineTo(pt);
	pt.SetPoint(EndPort->GetPoint().x,
		(StartPort->GetPoint().y + EndPort->GetPoint().y) / 2);
	pDC->LineTo(pt);
	pt.SetPoint(EndPort->GetPoint().x,
		EndPort->GetPoint().y);
	pDC->LineTo(pt);
}
void LineObject::ZZLine_LeftRight(CDC* pDC)
{
    CPoint pt;
    pt.SetPoint((StartPort->GetPoint().x + EndPort->GetPoint().x) / 2,
        StartPort->GetPoint().y);
    pDC->LineTo(pt);
    pt.SetPoint((StartPort->GetPoint().x + EndPort->GetPoint().x) / 2,
        EndPort->GetPoint().y);
    pDC->LineTo(pt);
    pt.SetPoint(EndPort->GetPoint().x,
        EndPort->GetPoint().y);
    pDC->LineTo(pt);
}

AssociationLine::AssociationLine(Shape* sp1, Shape*sp2)
	: LineObject(sp1, sp2)//之後把SetCloestPortInLine放進來
{
	this->SetCloestPortInLine(sp1, sp2);
	//AfxMessageBox(_T("AssociationLine  2 shape* Con.."));
}
AssociationLine::AssociationLine(AssociationLine &S)
	: LineObject(S)
{
	//AfxMessageBox(_T("AssociationLine Copy Con.."));
}
AssociationLine &AssociationLine::operator = (AssociationLine &S)
{
	//AfxMessageBox(_T("AssociationLine oper="));
	return *this;
}
AssociationLine::~AssociationLine()
{
	//AfxMessageBox(_T("AssociationLine Desty.."));
}
void AssociationLine::Draw(CDC* pDC)
{
	//draw Point
	StartPort->ShowConnectPoint(pDC);
	EndPort->ShowConnectPoint(pDC);
	//draw line
	CPen pen(PS_SOLID, 2, RGB(0, 0, 0));//創立一個黑色畫筆
	pDC->SelectObject(&pen);
	pDC->MoveTo(StartPort->GetPoint());
	pDC->LineTo(EndPort->GetPoint());
}

GeneralizationLine::GeneralizationLine(Shape* sp1, Shape*sp2)
	: LineObject(sp1, sp2)//之後把SetCloestPortInLine放進來
{
	TriHeadSize.SetPoint(20, 20);//設定箭頭大小
	this->SetCloestPortInLine(sp1, sp2);
	//AfxMessageBox(_T("GeneralizationLine  2 shape* Con.."));
}
GeneralizationLine::GeneralizationLine(GeneralizationLine &S)
	: LineObject(S)
{
	TriHeadSize = S.TriHeadSize;
	//AfxMessageBox(_T("GeneralizationLine Copy Con.."));
}
GeneralizationLine &GeneralizationLine::operator = (GeneralizationLine &S)
{
	TriHeadSize = S.TriHeadSize;
	//AfxMessageBox(_T("GeneralizationLine oper="));
	return *this;
}
GeneralizationLine::~GeneralizationLine()
{
	//AfxMessageBox(_T("GeneralizationLine Desty.."));
}
void GeneralizationLine::Draw(CDC* pDC)
{
	//draw Point
	StartPort->ShowConnectPoint(pDC);
	EndPort->ShowConnectPoint(pDC);

	//draw line
	CPen pen(PS_SOLID, 2, RGB(0, 0, 0));//創立一個黑色畫筆
	pDC->SelectObject(&pen);

	//取得port位置
	int PortDirection = -1;
	for (int i = 0; i <StartPort->_Basic->GetPortNum(); i++)
	{
		if (StartPort == StartPort->_Basic->GetPort(i))
		{
			PortDirection = i;
		}
	}

	CPoint pt;
	if (PortDirection == 0)
	{
		pDC->MoveTo(StartPort->GetPoint());
		pt.SetPoint(StartPort->GetPoint().x - TriHeadSize.x / 2,
			StartPort->GetPoint().y - TriHeadSize.y);
		pDC->LineTo(pt);
		pt.SetPoint(StartPort->GetPoint().x + TriHeadSize.x / 2,
			StartPort->GetPoint().y - TriHeadSize.y);
		pDC->LineTo(pt);
		pDC->LineTo(StartPort->GetPoint());

		pt.SetPoint(StartPort->GetPoint().x,
			StartPort->GetPoint().y - TriHeadSize.y);
		pDC->MoveTo(pt);

		ZZLine_TopDown(pDC);
	}
	else if (PortDirection == 1)
	{
		pDC->MoveTo(StartPort->GetPoint());
		pt.SetPoint(StartPort->GetPoint().x - TriHeadSize.x,
			StartPort->GetPoint().y - TriHeadSize.y / 2);
		pDC->LineTo(pt);
		pt.SetPoint(StartPort->GetPoint().x - TriHeadSize.x,
			StartPort->GetPoint().y + TriHeadSize.y / 2);
		pDC->LineTo(pt);
		pDC->LineTo(StartPort->GetPoint());

		pt.SetPoint(StartPort->GetPoint().x - TriHeadSize.x,
			StartPort->GetPoint().y);
		pDC->MoveTo(pt);

		ZZLine_LeftRight(pDC);
	}
	else if (PortDirection == 2)
	{
		pDC->MoveTo(StartPort->GetPoint());
		pt.SetPoint(StartPort->GetPoint().x - TriHeadSize.x / 2,
			StartPort->GetPoint().y + TriHeadSize.y);
		pDC->LineTo(pt);
		pt.SetPoint(StartPort->GetPoint().x + TriHeadSize.x / 2,
			StartPort->GetPoint().y + TriHeadSize.y);
		pDC->LineTo(pt);
		pDC->LineTo(StartPort->GetPoint());

		pt.SetPoint(StartPort->GetPoint().x,
			StartPort->GetPoint().y + TriHeadSize.y);
		pDC->MoveTo(pt);

		ZZLine_TopDown(pDC);
	}
	else if (PortDirection == 3)
	{
		pDC->MoveTo(StartPort->GetPoint());
		pt.SetPoint(StartPort->GetPoint().x + TriHeadSize.x,
			StartPort->GetPoint().y - TriHeadSize.y / 2);
		pDC->LineTo(pt);
		pt.SetPoint(StartPort->GetPoint().x + TriHeadSize.x,
			StartPort->GetPoint().y + TriHeadSize.y / 2);
		pDC->LineTo(pt);
		pDC->LineTo(StartPort->GetPoint());

		pt.SetPoint(StartPort->GetPoint().x + TriHeadSize.x,
			StartPort->GetPoint().y);
		pDC->MoveTo(pt);

		ZZLine_LeftRight(pDC);
	}
}


CompositionLine::CompositionLine(Shape* sp1, Shape*sp2) : LineObject(sp1, sp2)//之後把SetCloestPortInLine放進來
{
	DiaHeadSize.SetPoint(20, 20);//設定箭頭大小
	this->SetCloestPortInLine(sp1, sp2);
	//AfxMessageBox(_T("CompositionLine  2 shape* Con.."));
}
CompositionLine::CompositionLine(CompositionLine &S)
	: LineObject(S)
{
	DiaHeadSize = S.DiaHeadSize;
	//AfxMessageBox(_T("CompositionLine Copy Con.."));
}
CompositionLine &CompositionLine::operator = (CompositionLine &S)
{
	DiaHeadSize = S.DiaHeadSize;
	//AfxMessageBox(_T("CompositionLine oper="));
	return *this;
}
CompositionLine::~CompositionLine()
{
	//AfxMessageBox(_T("CLineDiamond Desty.."));
}
void CompositionLine::Draw(CDC* pDC)
{
	//draw Point
	StartPort->ShowConnectPoint(pDC);
	EndPort->ShowConnectPoint(pDC);

	//draw line
	CPen pen(PS_SOLID, 2, RGB(0, 0, 0));//創立一個黑色畫筆
	pDC->SelectObject(&pen);

	//取得port位置
	int PortDirection = -1;
	for (int i = 0; i < StartPort->_Basic->GetPortNum(); i++)
	{
		if (StartPort == StartPort->_Basic->GetPort(i))
		{
			PortDirection = i;
		}
	}

	CPoint pt;
	if (PortDirection == 0)
	{
		pDC->MoveTo(StartPort->GetPoint());
		pt.SetPoint(StartPort->GetPoint().x - DiaHeadSize.x / 2,
			StartPort->GetPoint().y - DiaHeadSize.y / 2);
		pDC->LineTo(pt);
		pt.SetPoint(StartPort->GetPoint().x,
			StartPort->GetPoint().y - DiaHeadSize.y);
		pDC->LineTo(pt);
		pt.SetPoint(StartPort->GetPoint().x + DiaHeadSize.x / 2,
			StartPort->GetPoint().y - DiaHeadSize.y / 2);
		pDC->LineTo(pt);
		pDC->LineTo(StartPort->GetPoint());

		pt.SetPoint(StartPort->GetPoint().x,
			StartPort->GetPoint().y - DiaHeadSize.y);
		pDC->MoveTo(pt);

		ZZLine_TopDown(pDC);
	}
	else if (PortDirection == 1)
	{
		pDC->MoveTo(StartPort->GetPoint());
		pt.SetPoint(StartPort->GetPoint().x - DiaHeadSize.x / 2,
			StartPort->GetPoint().y - DiaHeadSize.y / 2);
		pDC->LineTo(pt);
		pt.SetPoint(StartPort->GetPoint().x - DiaHeadSize.x,
			StartPort->GetPoint().y);
		pDC->LineTo(pt);
		pt.SetPoint(StartPort->GetPoint().x - DiaHeadSize.x / 2,
			StartPort->GetPoint().y + DiaHeadSize.y / 2);
		pDC->LineTo(pt);
		pDC->LineTo(StartPort->GetPoint());

		pt.SetPoint(StartPort->GetPoint().x - DiaHeadSize.x,
			StartPort->GetPoint().y);
		pDC->MoveTo(pt);

		ZZLine_LeftRight(pDC);
	}
	else if (PortDirection == 2)
	{
		pDC->MoveTo(StartPort->GetPoint());
		pt.SetPoint(StartPort->GetPoint().x - DiaHeadSize.x / 2,
			StartPort->GetPoint().y + DiaHeadSize.y / 2);
		pDC->LineTo(pt);
		pt.SetPoint(StartPort->GetPoint().x,
			StartPort->GetPoint().y + DiaHeadSize.y);
		pDC->LineTo(pt);
		pt.SetPoint(StartPort->GetPoint().x + DiaHeadSize.x / 2,
			StartPort->GetPoint().y + DiaHeadSize.y / 2);
		pDC->LineTo(pt);
		pDC->LineTo(StartPort->GetPoint());

		pt.SetPoint(StartPort->GetPoint().x,
			StartPort->GetPoint().y + DiaHeadSize.y);
		pDC->MoveTo(pt);

		ZZLine_TopDown(pDC);
	}
	else if (PortDirection == 3)
	{
		pDC->MoveTo(StartPort->GetPoint());
		pt.SetPoint(StartPort->GetPoint().x + DiaHeadSize.x / 2,
			StartPort->GetPoint().y - DiaHeadSize.y / 2);
		pDC->LineTo(pt);
		pt.SetPoint(StartPort->GetPoint().x + DiaHeadSize.x,
			StartPort->GetPoint().y);
		pDC->LineTo(pt);
		pt.SetPoint(StartPort->GetPoint().x + DiaHeadSize.x / 2,
			StartPort->GetPoint().y + DiaHeadSize.y / 2);
		pDC->LineTo(pt);
		pDC->LineTo(StartPort->GetPoint());

		pt.SetPoint(StartPort->GetPoint().x + DiaHeadSize.x,
			StartPort->GetPoint().y);
		pDC->MoveTo(pt);

		ZZLine_LeftRight(pDC);
	}
}
