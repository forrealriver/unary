
// CodeFransform.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCodeFransformApp:
// �йش����ʵ�֣������ CodeFransform.cpp
//

class CCodeFransformApp : public CWinAppEx
{
public:
	CCodeFransformApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCodeFransformApp theApp;