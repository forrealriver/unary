#pragma once
#include "UnicodeToUTF8.h"
#include "UTF8ToUnicode.h"
#include "UnicodeOperate.h"
#include "UTF8Operate.h"
#include "Log.h"
class CreateFactory
{
public:
	CreateFactory(void);
	~CreateFactory(void);  
	void CreateFactory::SetLastError(CString lastErrInfo);
	CString CreateFactory::GetLastError(void);
	FileOperate* CreateFactory::CreateFile(CString code);
	TransformOperate* CreateFactory::CreateFrans(CString sCode,CString dCode);
	CString m_LastError;
	Log log;
};
