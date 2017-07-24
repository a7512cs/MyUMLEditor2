#pragma once
#include "stdafx.h"
#include <vector>
using namespace std;

class CCanvas;
class Shape;

class A
{
public:
	vector <int> V;
	vector<vector <int>> V2;

	//vector ** acv;
	vector <int> **acry;
protected:
private:
};



class Mode {
public:
	Mode(CCanvas* canvasPtr)
	{
		CanvasPtr = canvasPtr;
	}
	

	void SetMode(Mode* mode);

	virtual void MousePress(CPoint point) = 0;

	virtual void MouseMove(CPoint point) = 0;

	virtual void MouseRelease(CPoint point) = 0;

	//�� �O���ƹ���ܮ� ���W �M�k�U
	void GetSelectingNormalizationPt(CPoint &LeftTopPt, CPoint &RigBotPt);
protected:
	virtual ~Mode(){};
	CCanvas* CanvasPtr;
	Shape *Obj1, *Obj2;

};

class SelectMode : public Mode {
public:
	SelectMode(CCanvas* canvasPtr)
		:Mode(canvasPtr)
		, IsInObj_mousepress(FALSE)
		, IsMoving(FALSE)
	{
		FirstPoint.SetPoint(0, 0);
	}
	~SelectMode()
	{
	}


	void MousePress(CPoint point);

	void MouseMove(CPoint point);

	void MouseRelease(CPoint point);
protected:
	BOOL IsInObj_mousepress;//�u�q ���Ĥ@�Ӫ���
	BOOL IsMoving;//�O�_�����ʼҦ�
	CPoint FirstPoint;

};
class AssociationMode : public Mode {
public:
	AssociationMode(CCanvas* canvasPtr) :Mode(canvasPtr){};
	~AssociationMode(){};

	void MousePress(CPoint point);

	void MouseMove(CPoint point);

	void MouseRelease(CPoint point);
};
class GeneralizationMode : public Mode {
public:
	GeneralizationMode(CCanvas* canvasPtr) :Mode(canvasPtr){};
	~GeneralizationMode(){};

	void MousePress(CPoint point);

	void MouseMove(CPoint point);

	void MouseRelease(CPoint point);
};
class CompositionMode : public Mode {
public:
	CompositionMode(CCanvas* canvasPtr) :Mode(canvasPtr){};
	~CompositionMode(){};
	void MousePress(CPoint point);

	void MouseMove(CPoint point);

	void MouseRelease(CPoint point);
};
class ClassMode : public Mode {
public:
	ClassMode(CCanvas* canvasPtr) :Mode(canvasPtr){};
	~ClassMode(){};

	void MousePress(CPoint point);

	void MouseMove(CPoint point);

	void MouseRelease(CPoint point);
};
class UseCaseMode : public Mode {
public:
	UseCaseMode(CCanvas* canvasPtr) :Mode(canvasPtr){};
	~UseCaseMode(){};
	void MousePress(CPoint point);

	void MouseMove(CPoint point);

	void MouseRelease(CPoint point);
};