#include "StdAfx.h"
#include "TansControl.h"

#define BUFFER_SIZE 1024*20

TansControl::TansControl(CString sfilepath, CString dfilepath, CString scode, CString dcode) {
	m_sFilePath = sfilepath;
	m_dFilePath = dfilepath;
	m_sCode = scode;
	m_dCode = dcode;
	m_treadstate.m_state = 0;
	m_endflage = 0;
	InitializeCriticalSection(&m_cs);
}
TansControl::~TansControl(void) {
	m_createFac.Release(m_read,m_write,m_TransCode,m_sCode,m_dCode);
}
void TansControl::SetLastError(CString lastErrInfo){
	m_LastError=lastErrInfo;
}
CString TansControl::GetLastError(){
	return m_LastError;
}
/******************************************************************
��������TreadProcess
����˵�����̺߳������
���룺lpParam ����
�����DWORD
*******************************************************************/
DWORD WINAPI TansControl::TreadProcess(LPVOID lpParam) {
	TansControl *tansControl = (TansControl*)lpParam;
	int x = tansControl->TransformFile();
	return x;
}
/******************************************************************
��������BulidFile
����˵���������߳���Ҫ���ļ��ࡢת����
���룺void
�����bool
*******************************************************************/
bool TansControl::BulidFile() {
	m_read = m_createFac.CreateFile(m_sCode);
	m_write = m_createFac.CreateFile(m_dCode);
	m_TransCode = m_createFac.CreateFrans(m_sCode, m_dCode);
	if (!m_read || !m_write || !m_TransCode) {
		EnterCriticalSection(&m_cs);
		m_treadstate.m_state = -1;
		LeaveCriticalSection(&m_cs);
		SetLastError(m_createFac.GetLastError());
		return false;
	}
	return true;
}
/******************************************************************
��������TransformFile
����˵��������ת��
���룺void
�����0ʧ�� 1�ɹ�
*******************************************************************/
int TansControl::TransformFile() {
	bool flage = false;
	//bulid
	if (!BulidFile())
		return 0;
	//open
	string spath = m_sFilePath;
	if (!m_read->OpenFile(spath)) {
		EnterCriticalSection(&m_cs);
		m_treadstate.m_state = -1;
		LeaveCriticalSection(&m_cs);
		SetLastError("ԭ�ļ���ʧ�ܣ�FileOperate::OpenFile");
		log.OutputLog(m_LastError);
		return 0;
	}
	if (m_read->m_FileSize == 0){
		EnterCriticalSection(&m_cs);
		m_treadstate.m_state = -1;
		LeaveCriticalSection(&m_cs);
		SetLastError("�ļ�Ϊ�գ�FileOperate::OpenFile");
		log.OutputLog(m_LastError);
		return 0;
	}
	string dpath = m_dFilePath;
	if (!m_write->OpenFile(dpath)) {
		EnterCriticalSection(&m_cs);
		m_treadstate.m_state = -1;
		LeaveCriticalSection(&m_cs);
		SetLastError("Ŀ���ļ���ʧ�ܣ�FileOperate::OpenFile");
		log.OutputLog(m_LastError);
		return 0;
	}
	EnterCriticalSection(&m_cs);
	m_treadstate.m_state = 1;
	m_treadstate.m_allWork = m_read->m_FileSize;
	LeaveCriticalSection(&m_cs);
	//transform
	DWORD  readLineSize = 0;
	DWORD  transformSize = 0;
	byte *readByte = new byte[BUFFER_SIZE];
	byte *writeByte = new byte[BUFFER_SIZE];
	while (m_read->m_FileSize != m_read->m_FileReadSize) {
		//�߳���ֹ
		if (m_endflage == 1){
			EnterCriticalSection(&m_cs);
			m_treadstate.m_state = 0;
			LeaveCriticalSection(&m_cs);
			delete readByte;
			delete writeByte;
			return 2;
		}
		EnterCriticalSection(&m_cs);
		m_treadstate.m_nowWork = m_read->m_FileReadSize;
		LeaveCriticalSection(&m_cs);
		//read
		readLineSize = m_read->ReadFileLine(readByte, BUFFER_SIZE);
		if (readLineSize == -1) {
			EnterCriticalSection(&m_cs);
			m_treadstate.m_state = -1;
			LeaveCriticalSection(&m_cs);
			SetLastError(m_read->GetLastError());
			delete readByte;
			delete writeByte;
			return 0;
		}
		//transform
		transformSize = m_TransCode->TransformCode(readByte, writeByte, readLineSize);
		if (transformSize == -1) {
			EnterCriticalSection(&m_cs);
			m_treadstate.m_state = -1;
			LeaveCriticalSection(&m_cs);
			SetLastError(m_TransCode->GetLastError());
			delete readByte;
			delete writeByte;
			return 0;
		}
		//write
		if (!m_write->WriteFileline(writeByte, transformSize)) {
			EnterCriticalSection(&m_cs);
			m_treadstate.m_state = -1;
			LeaveCriticalSection(&m_cs);
			SetLastError(m_write->GetLastError());
			delete readByte;
			delete writeByte;
			return 0;
		}
	}
	//close
	delete readByte;
	delete writeByte;
	EnterCriticalSection(&m_cs);
	m_treadstate.m_state = 2;
	LeaveCriticalSection(&m_cs);
	return 1;
}
/******************************************************************
��������GetState
����˵�������ص�ǰ����
���룺�ṹ�巵������
�����void
*******************************************************************/
void TansControl::GetState(TreadState &state){
	EnterCriticalSection(&m_cs);
	state.m_allWork = m_treadstate.m_allWork;
	state.m_nowWork = m_treadstate.m_nowWork;
	state.m_state = m_treadstate.m_state;
	LeaveCriticalSection(&m_cs);
}
