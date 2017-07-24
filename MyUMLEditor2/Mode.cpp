#include "stdafx.h"
#include "Mode.h"
#include "Canvas.h"
#include "Shape.h"



void Mode::SetMode(Mode* mode) {
	CanvasPtr->SetCurrentMode(mode);
}
void Mode::GetSelectingNormalizationPt(CPoint &LeftTopPt, CPoint &RigBotPt)
{
	if (LeftTopPt.x > RigBotPt.x)
	{
		int t = LeftTopPt.x;
		LeftTopPt.x = RigBotPt.x; 
		RigBotPt.x = t;
	}

	if (LeftTopPt.y > RigBotPt.y)
	{
		int t = LeftTopPt.y;
		LeftTopPt.y = RigBotPt.y;
		RigBotPt.y = t;
	}
}


//
void SelectMode::MousePress(CPoint point)
{
	A aa;
	//0,1,2,3,4,5,6,7,8,9,10,
	//0,1,2
	//3,4
	//[10]  a[0]==0  a[3]==1;

	aa.V.push_back(0);
	aa.V.push_back(1);
	aa.V.push_back(2);
	aa.V2.push_back(aa.V);

	aa.V.push_back(3);
	aa.V.push_back(4);
	aa.V2.push_back(aa.V);

	//aa.acry = new int[10];
// 	aa.acry[1] = aa.V;
// 	aa.acry[0] = aa.V;
// 	aa.acry[2] = aa.V;//-1
// 	
// 	aa.acry[3] = 1;//->0
// 	aa.acry[4] = 1;
	int iii = 10;
	aa.acry = new vector <int>*[iii];

	aa.acry[0] = &(aa.V2[0]);
	aa.acry[1] = &(aa.V2[1]);
	aa.V2.erase(aa.V2.begin() + 0);


		
	//////////////////////////////////////////////////////////////////////////

	/*	�T�ر��p�G
	1. ���U ����w�Q������� �첾��
	2. ���U ���쪫�� ������ ��}�ɿ���L
	3. ���U ���ަ��L���쪫�� ��� �ؿ磌��
	*/

	IsMoving = FALSE;
	IsInObj_mousepress = FALSE;
	Obj1 = CanvasPtr->InWhichShape(point);//�O���O������Ӫ���
	if (Obj1)//���쪫�� 
	{
		IsInObj_mousepress = TRUE;
	}
	else//�S���쪫��
	{
		IsInObj_mousepress = FALSE;
	}
	FirstPoint = point;
}
void SelectMode::MouseMove(CPoint point)
{
	if (IsInObj_mousepress == TRUE && Obj1->IsSelected() == TRUE)
	{
		// move all selected objs
		CanvasPtr->SelectedMove(point - FirstPoint);
		FirstPoint = point;
		IsMoving = TRUE;
	}
	else
	{
		CPoint dis = FirstPoint - point;
		double d = dis.x*dis.x + dis.y*dis.y;
		if (d>8)
		{
			IsInObj_mousepress = FALSE;
		}
	}
}
void SelectMode::MouseRelease(CPoint point)
{
	//�o�䦳�F��S�Q�� �n�b�ק�
	if (IsMoving)//���ʪ����
	{
		IsMoving = FALSE;
	}
	else if (IsInObj_mousepress)
	{
		CanvasPtr->ClearAllSelectedObj();
		Obj1->SetSelect(TRUE);
	}
	else//�ƹ��ؿ��
	{
		CanvasPtr->ClearAllSelectedObj();
		GetSelectingNormalizationPt(FirstPoint, point);
		vector<Shape*> Objs;
		Objs = CanvasPtr->GetInsideObject(FirstPoint, point);

		int n = Objs.size();
		for (int i = 0; i < n; i++)
		{
			Objs[i]->SetSelect(TRUE);
		}
	}
	IsInObj_mousepress = FALSE;
}

void AssociationMode::MousePress(CPoint point)
{
	Obj1 = CanvasPtr->InWhichShape(point);
}
void AssociationMode::MouseMove(CPoint point)
{
	
}
void AssociationMode::MouseRelease(CPoint point)
{
	if (Obj1 == NULL || Obj1->HasChildren)
	{
		return;
	}
	Obj2 = CanvasPtr->InWhichShape(point);//�O���O������Ӫ���
	if (Obj2 == NULL || Obj2->HasChildren)
	{
		return;
	}
	if (Obj2 != Obj1)
	{
		AssociationLine *L = new AssociationLine(Obj1, Obj2);
		CanvasPtr->AddObj(L);
	}
}


void GeneralizationMode::MousePress(CPoint point)
{
	Obj1 = CanvasPtr->InWhichShape(point);
}
void GeneralizationMode::MouseMove(CPoint point)
{

}
void GeneralizationMode::MouseRelease(CPoint point)
{
	if (Obj1 == NULL || Obj1->HasChildren)
	{
		return;
	}
	Obj2 = CanvasPtr->InWhichShape(point);//�O���O������Ӫ���
	if (Obj2 == NULL || Obj2->HasChildren)
	{
		return;
	}
	if (Obj2 != Obj1)
	{
		GeneralizationLine *L = new GeneralizationLine(Obj1, Obj2);
		CanvasPtr->AddObj(L);
	}
}

void CompositionMode::MousePress(CPoint point)
{
	Obj1 = CanvasPtr->InWhichShape(point);
}
void CompositionMode::MouseMove(CPoint point)
{

}
void CompositionMode::MouseRelease(CPoint point)
{
	if (Obj1 == NULL || Obj1->HasChildren)
	{
		return;
	}
	Obj2 = CanvasPtr->InWhichShape(point);//�O���O������Ӫ���
	if (Obj2 == NULL || Obj2->HasChildren)
	{
		return;
	}
	if (Obj2 != Obj1)
	{
		CompositionLine*L = new CompositionLine(Obj1, Obj2);
		CanvasPtr->AddObj(L);
	}
}

void ClassMode::MousePress(CPoint point)
{

}
void ClassMode::MouseMove(CPoint point)
{

}
void ClassMode::MouseRelease(CPoint point)
{
	ClassBox *classbox = NULL;
	classbox = new ClassBox(point);
	if (classbox != NULL)
	{
		CanvasPtr->AddObj(classbox);
	}
}

void UseCaseMode::MousePress(CPoint point) {

}
void UseCaseMode::MouseMove(CPoint point) {

}
void UseCaseMode::MouseRelease(CPoint point)
{
	UseCaseBox* usebox = NULL;
	usebox = new UseCaseBox(point);
	if (usebox != NULL)
	{
		CanvasPtr->AddObj(usebox);
	}
}
