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

	//�����ܼ�
public:
	CRect CanvasRc;//�e���j�p
	virtual void OnDraw(CDC* pDC);


	//�����ܼ�
	void DrawAll(CDC* pDC);//�e�X��������
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
	vector<Shape*> GetInsideObject(CPoint point1, CPoint point2);//���o�ƹ�����d�򤺪��Ҧ�����
	void SelectedMove(CPoint dis);
	void Group();
	void Ungroup();
	Shape* InWhichShape(CPoint point);
	void ClearAllSelectedObj();//�M���Ҧ��s�������I
	vector<Shape*> AllObj;



	
};
