#include "stdafx.h"
#include "CComposite.h"
#include "Shape.h"

anObject::~anObject()
{
	delete _Object;
	AfxMessageBox(_T("anObject Desty.."));
}