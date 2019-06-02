#pragma once

#include "UnicodeOperate.h"
#include "UTF8Operate.h"
#include "string"
#include "iostream"
#include "Log.h"
using namespace std;
class CreateFactory
{
public:
	CreateFactory(void);
	~CreateFactory(void);  
	void CreateFactory::SetLastError(CString lastErrInfo);
	CString CreateFactory::GetLastError(void);
	FileOperate* CreateFactory::CreateFile(CString code);
	CString m_LastError;
	Log log;
};
