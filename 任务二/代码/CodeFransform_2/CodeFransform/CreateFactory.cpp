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
	UnicodeOperate * unicode=new UnicodeOperate();
	UTF8Operate* utf8=new UTF8Operate();
	if (code=="UTF_8")
		return(utf8);
	else if (code=="Unicode")
		return(unicode);
	SetLastError("创建文件失败：CreateFactory::CreateFile");
	log.OutputLog(m_LastError);
	return NULL;
}