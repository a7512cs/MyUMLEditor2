
// MyUMLEditor2.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CMyUMLEditor2App: 
// �аѾ\��@�����O�� MyUMLEditor2.cpp
//

class CMyUMLEditor2App : public CWinApp
{
public:
	CMyUMLEditor2App();

// �мg
public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern CMyUMLEditor2App theApp;