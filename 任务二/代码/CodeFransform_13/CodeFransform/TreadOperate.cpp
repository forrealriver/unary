#include "StdAfx.h"
#include "TreadOperate.h"

TreadOperate::TreadOperate(void){}
TreadOperate::~TreadOperate(void){}
void TreadOperate::SetLastError(CString lastErrInfo){
	m_LastError=lastErrInfo;
}
CString TreadOperate::GetLastError(){
	return m_LastError;
}
/******************************************************************
函数名：creadTread
功能说明：创建线程
输入：CString sfilepath,CString dfilepath,CString scode,CString dcode
输出：bool
*******************************************************************/
bool TreadOperate::creadTread(CString sfilepath, CString dfilepath, CString scode, CString dcode) {
	tansControl = new TansControl(sfilepath, dfilepath, scode, dcode);
	tansControl->m_ThreadHandle = CreateThread(NULL, 0, tansControl->TreadProcess, tansControl, 0, NULL);
	if (tansControl->m_ThreadHandle == NULL) {
		SetLastError("创建线程失败：TreadOperate::creadTread");
		log.OutputLog(m_LastError);
		return false;
	}
	return true;
}
/******************************************************************
函数名：getState
功能说明：当前转换进度
输入：void
输出：进度（0-100）
*******************************************************************/
int TreadOperate::getState(void) {
	if (tansControl != NULL) {
		if (tansControl->state == -1) {
			SetLastError(tansControl->GetLastError());
			log.OutputLog(m_LastError);
			return -1;
		}
		m_filesize = tansControl->allWork;
		m_nowsize = tansControl->nowWork;
		if (tansControl->state == 2) {
			return 100;
		}
		else if (tansControl->state == 1) {
			float rate = (float)tansControl->nowWork / (float)tansControl->allWork;
			return (int)(rate * 100);
		}
	}
	return 0;
}
/******************************************************************
函数名：killTread
功能说明：取消转换
输入：void
输出：void
*******************************************************************/
void TreadOperate::killTread(void) {
	DWORD dw = WaitForSingleObject(tansControl->m_ThreadHandle, 0);
	if (dw == WAIT_TIMEOUT) {
		TerminateThread(tansControl->m_ThreadHandle, -1);
		if (tansControl->m_ThreadHandle != NULL) {
			CloseHandle(tansControl->m_ThreadHandle);
			tansControl->m_ThreadHandle = NULL;
		}
		tansControl->CloseFile();
		delete tansControl;
		tansControl = NULL;
	}
}