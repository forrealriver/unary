#include "StdAfx.h"
#include "CreateFactory.h"

CreateFactory::CreateFactory(void){}
CreateFactory::~CreateFactory(void){}
void CreateFactory::SetLastError(CString lastErrInfo){
	m_LastError=lastErrInfo;
}
CString CreateFactory::GetLastError(){
	return m_LastError;
}
/******************************************************************
函数名：CreateFile
功能说明：根据文件类型创建文件操作类型
输入：code 文件类型
输出：文件操作类
*******************************************************************/
FileOperate* CreateFactory::CreateFile(CString code){
	if(code=="UTF_8")
		return (new UTF8Operate());
	else if(code=="Unicode")
		return (new UnicodeOperate());
	SetLastError("创建文件失败：CreateFactory::CreateFile");
	log.OutputLog(m_LastError);
	return NULL;
}
/******************************************************************
函数名：CreateFrans
功能说明：根据文件类型创建文件转换类型
输入：scode 原文件类型、dcode 目标文件类型
输出：文件转换类
*******************************************************************/
TransformOperate* CreateFactory::CreateFrans(CString sCode,CString dCode){
	if(sCode=="Unicode" && dCode=="UTF_8")
		return (new UnicodeToUTF8());
	else if(sCode=="UTF_8" && dCode=="Unicode")
		return (new UTF8ToUnicode());
	SetLastError("创建转换失败：CreateFactory::CreateFrans");
	log.OutputLog(m_LastError);
	return NULL;
}
