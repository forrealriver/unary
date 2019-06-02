#include "StdAfx.h"
#include "TreadOperate.h"
#include "Log.h"
TreadOperate::TreadOperate(void){
	m_find=NULL;
}

TreadOperate::~TreadOperate(void){
	m_find=NULL;
}
bool TreadOperate::creadTread(CString sfilepath, CString dfilepath) {
	m_find = new Find(sfilepath, dfilepath);
	m_find->m_ThreadHandle = CreateThread(NULL, 0, m_find->TreadProcess, m_find, 0, NULL);
	if (m_find->m_ThreadHandle == NULL) {
		Log log;
		log.OutputLog(_T("创建线程失败：TreadOperate::creadTread"));
		delete m_find;
		return false;
	}
	return true;
}

void TreadOperate::killTread(void) {
	//线程停止标志置 1
	m_find->m_endflage = 1;
	DWORD dw = WaitForSingleObject(m_find->m_ThreadHandle, 2000);
	if (dw == WAIT_TIMEOUT) {
		TerminateThread(m_find->m_ThreadHandle, -1);
		if (m_find->m_ThreadHandle != NULL) {
			CloseHandle(m_find->m_ThreadHandle);
			m_find->m_ThreadHandle = NULL;
		}
	}
	delete m_find;
}