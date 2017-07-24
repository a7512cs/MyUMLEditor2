#include "stdafx.h"
#include "Shape.h"
#include "ConnectedPort.h"


ConnectPort::ConnectPort()
	: Rx(0)
	, Ry(0)
	, ConPtSize(5, 5)
{

}
ConnectPort::~ConnectPort()
{
	//AfxMessageBox(_T("ConnectPort Desty.."));
}
CPoint ConnectPort::GetPoint()
{
	CPoint pt(_Basic->GetStartPt().x + Rx, _Basic->GetStartPt().y + Ry);
	return pt;
}
void ConnectPort::ShowConnectPoint(CDC* pDC)
{
	CPen pen(PS_NULL, 1, RGB(0, 0, 0));//透明畫筆
	CBrush BrushBlack(RGB(0, 0, 0));//填滿畫刷
	pDC->SelectObject(&pen);//透明框
	pDC->SelectObject(&BrushBlack);//黑色實心
	CPoint P1((_Basic->GetStartPt().x + Rx) - ConPtSize.x, (_Basic->GetStartPt().y + Ry) - ConPtSize.y);
	CPoint P2((_Basic->GetStartPt().x + Rx) + ConPtSize.x, (_Basic->GetStartPt().y + Ry) + ConPtSize.y);
	CRect rec(P1, P2);
	pDC->Rectangle(rec);
}
void ConnectPort::SetBasic(BasicObject* Basic)
{
	_Basic = Basic; 
}
void ConnectPort::SetRelation(int x, int y)
{
	Rx = x;
	Ry = y;
}
