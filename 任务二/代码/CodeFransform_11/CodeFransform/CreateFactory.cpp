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
��������CreateFile
����˵���������ļ����ʹ����ļ���������
���룺code �ļ�����
������ļ�������
*******************************************************************/
FileOperate* CreateFactory::CreateFile(CString code){
	if(code=="UTF_8")
		return (new UTF8Operate());
	else if(code=="Unicode")
		return (new UnicodeOperate());
	SetLastError("�����ļ�ʧ�ܣ�CreateFactory::CreateFile");
	log.OutputLog(m_LastError);
	return NULL;
}
/******************************************************************
��������CreateFrans
����˵���������ļ����ʹ����ļ�ת������
���룺scode ԭ�ļ����͡�dcode Ŀ���ļ�����
������ļ�ת����
*******************************************************************/
TransformOperate* CreateFactory::CreateFrans(CString sCode,CString dCode){
	if(sCode=="Unicode" && dCode=="UTF_8")
		return (new UnicodeToUTF8());
	else if(sCode=="UTF_8" && dCode=="Unicode")
		return (new UTF8ToUnicode());
	SetLastError("����ת��ʧ�ܣ�CreateFactory::CreateFrans");
	log.OutputLog(m_LastError);
	return NULL;
}
