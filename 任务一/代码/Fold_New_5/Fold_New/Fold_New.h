
// Fold_New.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CFold_NewApp:
// �йش����ʵ�֣������ Fold_New.cpp
//

class CFold_NewApp : public CWinAppEx
{
public:
	CFold_NewApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CFold_NewApp theApp;