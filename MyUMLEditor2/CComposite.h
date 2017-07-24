#include <vector>
#include <algorithm>
using namespace std;

class anObject;
class Shape;

//群組用的容器
class CComposite
{
public:
	CComposite(vector<anObject*> &ContentObject)
		: _child(NULL)
		, _parent(NULL)
		, Selected(FALSE)
	{
		_ContentObject = ContentObject;
		//CreateBBX();
		AfxMessageBox(_T("CComposite con.. First!! so child NULL"));
	}

	CComposite(CComposite* parent
		, vector<anObject*> &ContentObject)
		: _child(parent)
		, _parent(NULL)
		, Selected(FALSE)
	{
		_ContentObject = ContentObject;
		//CreateBBX();
		AfxMessageBox(_T("CComposite con.. p,o"));
	}
	CComposite(CComposite* parent
		, vector<CComposite*> &ContentComposite)
		: _child(parent)
		, _parent(NULL)
		, Selected(FALSE)
	{
		_ContentComposite = ContentComposite;
		//CreateBBX();
		AfxMessageBox(_T("CComposite con.. p,c"));
	}
	CComposite(CComposite* parent
		, vector<anObject*> &ContentObject
		, vector<CComposite*> &ContentComposite)
		: _child(parent)
		, _parent(NULL)
		, Selected(FALSE)
	{
		_ContentObject = ContentObject;
		_ContentComposite = ContentComposite;
		//CreateBBX();
		AfxMessageBox(_T("CComposite con.. p,o,c"));
	}

	~CComposite()
	{
		if (_parent != NULL)
		{
			delete _parent;
			_parent = NULL;
		}
		_child = NULL;
		_ContentObject.clear();
		_ContentComposite.clear();
		AfxMessageBox(_T("CComposite desty.."));
	}

	//void PushIn(anObject *Obj){ _ContentObject.push_back(Obj); };

	void CreateParent(vector<anObject*> &ContentObject)
	{
		_parent = new CComposite(this, ContentObject);
	}
	void CreateParent(vector<CComposite*> &ContentComposite)
	{
		_parent = new CComposite(this, ContentComposite);
	}
	void CreateParent(vector<anObject*> &ContentObject, vector<CComposite*> &ContentComposite)
	{
		_parent = new CComposite(this, ContentObject, ContentComposite);
	}
	CComposite* GetParant()
	{
		return _parent;
	}
	CComposite* GetChild(int index)//沒用
	{
		return _child;
	}
	CPoint GetStartBBX()
	{
		return StartBBX;
	}
	CPoint GetEndBBX()
	{
		return EndBBX;
	}
	void SetSelect(BOOL b)
	{
		Selected = b;
	}
	BOOL IsSelect()
	{
		return Selected;
	}
	//	void CreateBBX();//建立邊界
	CComposite* GetChildComposite(int index){ return _ContentComposite[index]; }
	vector<CComposite*> GetAllChildComposite(){ return _ContentComposite; }
	anObject* GetChildanObject(int index){ return _ContentObject[index]; }
	vector<anObject*> GetAllChildanObject(){ return _ContentObject; }

protected:
	CPoint StartBBX;
	CPoint EndBBX;
	BOOL Selected;
private:
	CComposite *_parent;
	CComposite *_child;
	//CComposite* _ContentObject;
	vector<anObject*> _ContentObject;//記錄被框起來的單獨物件
	vector<CComposite*> _ContentComposite;//記錄被框起來的群組(可能有多個群組)
	//void RemoveObj();//還沒裝上
};

//一個物件的類別
class anObject//裡面放抽象的Geometry
{
public:
	anObject(){};
	anObject(Shape *G, int GType, int dep = 99)
		: _Object(G)
		, Depth(dep)
		, Selected(FALSE)
		, Grouped(FALSE)
		, GeometryType(GType)
	{
		//AfxMessageBox(_T("anObject Con.."));
	};

	anObject(anObject &O)
		: _Object(O._Object)
		, Depth(O.Depth)
		, Selected(O.Selected)
		, Grouped(O.Grouped)
		, GeometryType(O.GeometryType)
	{
		AfxMessageBox(_T("anObject Copy Con.."));
	}

	anObject &operator= (anObject &O)
	{
		_Object = O._Object;
		Depth = O.Depth;
		Selected = O.Selected;
		Grouped = O.Grouped;
		GeometryType = O.GeometryType;
		AfxMessageBox(_T("anObject oper="));
		return *this;
	}

	~anObject();

	//void CreatObject(CGeometry *G, int B);//這會搞的很複雜
	int GetDepth(){ return Depth; };
	void SetDepth(int d){ Depth = d; };
	BOOL IsSelected(){ return Selected; };
	void SetSelect(BOOL slc){ Selected = slc; };
	BOOL IsGrouped(){ return Grouped; };
	void SetGroup(BOOL grp){ Grouped = grp; };
	Shape *GetGObject(){ return _Object; };
	int GetGeometryType(){ return GeometryType; };

private:
	Shape *_Object;//物件的指標
	int GeometryType;//0~5  //好像沒用到
protected:
	COLORREF OColor;//還沒裝上去
	int Depth;
	BOOL Selected;//有被選取狀態
	BOOL Grouped;//有被群組中
};

//裝入多個物件的類別
class ObjectManager//裝anObject(Geometry)的容器
{
public:
	ObjectManager()
	{
		AfxMessageBox(_T("ObjectManager Con.."));
	}

	~ObjectManager()
	{
		AfxMessageBox(_T("ObjectManager Desty.."));
		int _AllGSize = GetObjectSize();
		for (int i = 0; i < _AllGSize; i++)
		{
			delete _AllGeometry[i];
		}
		_AllGeometry.clear();
		AfxMessageBox(_T("ObjectManager Desty..succesful"));
	}
	void AddObject(anObject *O)
	{
		ArrangeObjectDepth(O);
		O->SetDepth(0);
		//使用向前插入 讓他從小排到大 他就會自己照深度圖採 偷懶方法
		_AllGeometry.insert(_AllGeometry.begin(), O);
	};
	anObject *GetAnObject(int i){ return _AllGeometry[i]; };
	int GetObjectSize(){ return _AllGeometry.size(); };
	//void EreaseObject() 還有delete還沒裝上去
	void ArrangeObjectDepth(anObject *O)
	{
		//所有物件深度+1
		for (int i = 0; i < GetObjectSize(); i++)
		{
			O->SetDepth(O->GetDepth() + 1);
		}
	};
private:
	vector<anObject*> _AllGeometry;
};
