//#include "stdafx.h"
//#include "MyUMLEditor2Dlg.h"
#include <vector>
using namespace std;

class ConnectPort;

class Shape
{
public:
	Shape();
	Shape(Shape &G);
	Shape &operator= (Shape &G);
	virtual ~Shape();

	BOOL HasChildren;

	virtual void GetChileren(vector<Shape*> &child) = 0;

	virtual void Draw(CDC* pDC) = 0;
	virtual BOOL IsPointInside(CPoint pt1) = 0;//滑鼠的點 在物件內嗎
	virtual BOOL IsInsideRegin(CPoint pt1, CPoint pt2) = 0;//在滑鼠的兩個點的範圍內嗎
	BOOL IsSelected();
	void SetSelect(BOOL b);
	virtual CPoint GetStartPt() = 0;
	virtual CPoint GetEndPt() = 0;
	virtual ConnectPort* GetPort(int n) = 0;
	virtual int GetPortNum() = 0;
	virtual void ObjMove(CPoint dis) = 0;
	virtual void ChangeName(CString st) = 0;
protected:
	BOOL Selected;

};
class BasicObject : public Shape
{
public:
	BasicObject(CPoint SP);
	BasicObject(BasicObject &S);
	BasicObject & operator= (BasicObject &S);
	virtual ~BasicObject();

	
	void SetPortNumber(int n);
	void GetConnectPort(int n);
	ConnectPort* GetPort(int n);
	int GetPortNum();
	void GetChileren(vector<Shape*> &child);

	virtual void Draw(CDC* pDC) = 0;
	BOOL IsPointInside(CPoint pt);
	BOOL IsInsideRegin(CPoint pt1, CPoint pt2);

	CPoint GetStartPt();
	CPoint GetEndPt();
	void ChangeName(CString st);
	void ObjMove(CPoint dis);
	virtual void ShowTitle(CDC* pDC) = 0;
protected:
	CPoint StartPosition;
	CPoint ShapeSize;//形狀的大小
	ConnectPort *ports;
	CString Title;
	int ConPtNum;//連接點的數量 4
};
class ClassBox : public BasicObject
{
public:
	ClassBox();
	ClassBox(CPoint SP);
	ClassBox(ClassBox &S);
	ClassBox & operator= (ClassBox &S);
	/*
	ClassBox & operator= (ClassBox &S)
	{
		StartPosition = S.StartPosition;
		Title = S.Title;
		ShapeSize = S.ShapeSize;
		//AfxMessageBox(_T("ClassBox oper="));
		return *this;
	}
	*/

protected:
	virtual ~ClassBox();
	virtual void Draw(CDC* pDC);
	void ShowRec(CDC* pDC);
	virtual void ShowTitle(CDC* pDC);

};
class UseCaseBox : public BasicObject
{
public:
	UseCaseBox(CPoint SP);
	UseCaseBox(UseCaseBox &S);
	UseCaseBox & operator= (UseCaseBox &S);
	
protected:
	virtual ~UseCaseBox();
	virtual void Draw(CDC* pDC);
	virtual void ShowTitle(CDC* pDC);
};
class LineObject : public Shape
{
public:
	LineObject(Shape* sp1, Shape*sp2);
	LineObject(LineObject &S);
	LineObject & operator= (LineObject &S);
	void GetChileren(vector<Shape*> &child);
	BOOL IsPointInside(CPoint pt1);
	BOOL IsInsideRegin(CPoint pt1, CPoint pt2);

	CPoint GetStartPt();
	CPoint GetEndPt();
	ConnectPort* GetPort(int n);
	int GetPortNum();
	void ObjMove(CPoint dis);
	void SetCloestPortInLine(Shape* Shp1, Shape* Shp2);//更新連接點的位置
	void ChangeName(CString st);

protected:
	virtual ~LineObject();
	ConnectPort *StartPort;
	ConnectPort *EndPort;

	virtual void Draw(CDC* pDC) = 0;
	void ZZLine_TopDown(CDC* pDC);
	void ZZLine_LeftRight(CDC* pDC);

};
class AssociationLine : public LineObject
{
public:

	AssociationLine(Shape* sp1, Shape*sp2);
	AssociationLine(AssociationLine &S);
	AssociationLine & operator= (AssociationLine &S);

protected:
	virtual ~AssociationLine();
	void Draw(CDC* pDC);
	
};
class GeneralizationLine : public LineObject
{
public:

	GeneralizationLine(Shape* sp1, Shape*sp2);
	GeneralizationLine(GeneralizationLine &S);
	GeneralizationLine & operator= (GeneralizationLine &S);

protected:
	~GeneralizationLine();

	void Draw(CDC* pDC);
	
	CPoint TriHeadSize;//設定箭頭大小 20*20

};
class CompositionLine : public LineObject
{
public:

	CompositionLine(Shape* sp1, Shape*sp2);
	CompositionLine(CompositionLine &S);
	CompositionLine & operator= (CompositionLine &S);

protected:
	~CompositionLine();

	void Draw(CDC* pDC);
	CPoint DiaHeadSize;//設定箭頭大小 20*20
};