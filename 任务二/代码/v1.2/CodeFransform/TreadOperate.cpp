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
	m_tansControl = new TansControl(sfilepath, dfilepath, scode, dcode);
	m_tansControl->m_ThreadHandle = CreateThread(NULL, 0, m_tansControl->TreadProcess, m_tansControl, 0, NULL);
	if (m_tansControl->m_ThreadHandle == NULL) {
		SetLastError("创建线程失败：TreadOperate::creadTread");
		log.OutputLog(m_LastError);
		delete m_tansControl;
		return false;
	}
	return true;
}
/******************************************************************
函数名：getState
功能说明：当前转换进度
输入：结构体
输出：获取是否成功
*******************************************************************/
int TreadOperate::getState(TreadState &state) {
	if (m_tansControl != NULL) {
		m_tansControl->GetState(state);
		if (state.m_state == -1) {
			SetLastError(m_tansControl->GetLastError());
			delete m_tansControl;
			return -1;
		}
		if (state.m_state == 2) {
			delete m_tansControl;
		}
		return 1;
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
	//线程停止标志置 1
	m_tansControl->m_endflage = 1;
	DWORD dw = WaitForSingleObject(m_tansControl->m_ThreadHandle, 2000);
	if (dw == WAIT_TIMEOUT) {
		TerminateThread(m_tansControl->m_ThreadHandle, -1);
		if (m_tansControl->m_ThreadHandle != NULL) {
			CloseHandle(m_tansControl->m_ThreadHandle);
			m_tansControl->m_ThreadHandle = NULL;
		}
	}
	delete m_tansControl;
}