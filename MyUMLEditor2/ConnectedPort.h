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
	int Rx;//相對物件的偏移量
	int Ry;
	CPoint ConPtSize;//連接點的大小 10*10
};