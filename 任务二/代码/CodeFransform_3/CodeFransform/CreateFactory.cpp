#include "StdAfx.h"
#include "CreateFactory.h"

CreateFactory::CreateFactory(void)
{
}

CreateFactory::~CreateFactory(void)
{
}
void CreateFactory::SetLastError(CString lastErrInfo)
{
	m_LastError=lastErrInfo;
}
CString CreateFactory::GetLastError()
{
	return m_LastError;
}

FileOperate* CreateFactory::CreateFile(CString code)
{
	if (code=="UTF_8")
		return(new UTF8Operate());
	else if (code=="Unicode")
		return(new UnicodeOperate());
	SetLastError("创建文件失败：CreateFactory::CreateFile");
	log.OutputLog(m_LastError);
	return NULL;
}

TransformOperate* CreateFactory::CreateFrans(CString sCode,CString dCode)
{
	if (sCode=="Unicode" && dCode=="UTF_8")
		return(new UnicodeToUTF8());
	else if (sCode=="UTF_8" && dCode=="Unicode")
		return(new UTF8ToUnicode());
	else
	SetLastError("创建转换失败：CreateFactory::CreateFrans");
	log.OutputLog(m_LastError);
	return NULL;
}
