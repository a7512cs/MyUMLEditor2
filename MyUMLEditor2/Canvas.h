#pragma once
#include "CComposite.h"


class Mode;

class Shape;
class BasicObject;
class ObjectManager;
class CComposite;

class CCanvas : public CView
{
protected:
	DECLARE_DYNCREATE(CCanvas)
	DECLARE_MESSAGE_MAP()

	CCanvas();
	virtual ~CCanvas();

	//內建變數
public:
	CRect CanvasRc;//畫布大小
	virtual void OnDraw(CDC* pDC);


	//內建變數
	void DrawAll(CDC* pDC);//畫出全部物件
	void CleanAllCan(CDC* pDc);
	Mode* CurrentMode;
	void SetCurrentMode(Mode* mode);
	Mode* GetCurrentMode();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	void AddObj(Shape* shp);
	Shape* RemoveObj(int i);
	Shape* RemoveObj(Shape* shp);
	vector<Shape*> GetSelectedObj();
	vector<Shape*> GetInsideObject(CPoint point1, CPoint point2);//取得滑鼠選取範圍內的所有物件
	void SelectedMove(CPoint dis);
	void Group();
	void Ungroup();
	Shape* InWhichShape(CPoint point);
	void ClearAllSelectedObj();//清除所有連接控制點
	vector<Shape*> AllObj;



	
};
