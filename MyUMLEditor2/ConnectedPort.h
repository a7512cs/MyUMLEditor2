#pragma once
#include <vector>
using namespace std;

class LineObject;
class BasicObject;

class ConnectPort {
public:
	ConnectPort();
	~ConnectPort();

	CPoint GetPoint();
	void ShowConnectPoint(CDC* pDC);
	void SetBasic(BasicObject* Basic);
	void SetRelation(int x, int y);
	BasicObject* _Basic;
protected:
	int Rx;//�۹磌�󪺰����q
	int Ry;
	CPoint ConPtSize;//�s���I���j�p 10*10
};