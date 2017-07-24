#pragma once
#include "stdafx.h"
#include "Shape.h"
#include <vector>
using namespace std;

//class Shape;
class ConnectPort;
class GroupObject : public Shape
{
public:
	GroupObject();
	GroupObject(GroupObject &S);
	GroupObject &operator= (GroupObject &S)
	{
		//AfxMessageBox(_T("GroupObject oper="));
		return *this;
	}

	virtual void GetChileren(vector<Shape*> &child);
	virtual void Draw(CDC* pDC);
	virtual BOOL IsPointInside(CPoint pt);
	virtual BOOL IsInsideRegin(CPoint pt1, CPoint pt2);
	virtual CPoint GetStartPt();
	virtual CPoint GetEndPt();
	virtual ConnectPort* GetPort(int n);
	virtual int GetPortNum();
	virtual void ObjMove(CPoint dis);
	virtual void ChangeName(CString st);
	void CalculateBBX();
	void AddGroup(vector<Shape*> Obj);

	
protected:
	virtual ~GroupObject();
	vector<Shape*> GroupObj;

	CPoint StartPosition;
	CPoint ShapeSize;//形狀的大小



};