#include "StdAfx.h"
#include "TreadOperate.h"

TreadOperate::TreadOperate(void)
{
}

TreadOperate::~TreadOperate(void)
{
}
void TreadOperate::SetLastError(CString lastErrInfo){
	m_LastError=lastErrInfo;
}
CString TreadOperate::GetLastError(){
	return m_LastError;
}
bool TreadOperate::creadTread(CString sfilepath,CString dfilepath,CString scode,CString dcode){
	tansControl=new TansControl(sfilepath,dfilepath,scode,dcode);
	tansControl->m_ThreadHandle=CreateThread(NULL,0,tansControl->TreadProcess,tansControl,0,NULL);
	if (tansControl->m_ThreadHandle==NULL){
		SetLastError("线程创建失败");
		log.OutputLog(m_LastError);
		return false;
	}
	return true;
}