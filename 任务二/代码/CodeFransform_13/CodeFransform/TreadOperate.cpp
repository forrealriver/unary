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
��������creadTread
����˵���������߳�
���룺CString sfilepath,CString dfilepath,CString scode,CString dcode
�����bool
*******************************************************************/
bool TreadOperate::creadTread(CString sfilepath, CString dfilepath, CString scode, CString dcode) {
	tansControl = new TansControl(sfilepath, dfilepath, scode, dcode);
	tansControl->m_ThreadHandle = CreateThread(NULL, 0, tansControl->TreadProcess, tansControl, 0, NULL);
	if (tansControl->m_ThreadHandle == NULL) {
		SetLastError("�����߳�ʧ�ܣ�TreadOperate::creadTread");
		log.OutputLog(m_LastError);
		return false;
	}
	return true;
}
/******************************************************************
��������getState
����˵������ǰת������
���룺void
��������ȣ�0-100��
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
��������killTread
����˵����ȡ��ת��
���룺void
�����void
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