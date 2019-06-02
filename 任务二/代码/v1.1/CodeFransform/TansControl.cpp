#include "StdAfx.h"
#include "TansControl.h"

#define BUFFER_SIZE 1024*20

TansControl::TansControl(CString sfilepath, CString dfilepath, CString scode, CString dcode) {
	m_sFilePath = sfilepath;
	m_dFilePath = dfilepath;
	m_sCode = scode;
	m_dCode = dcode;
	m_treadstate.m_state = 0;
	m_readByte = new byte[BUFFER_SIZE];
	m_writeByte = new byte[BUFFER_SIZE];
	m_endflage = 0;
	InitializeCriticalSection(&m_cs);
}
TansControl::~TansControl(void){}
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
		m_treadstate.m_state = -1;
		SetLastError(m_createFac.GetLastError());
		m_createFac.Release(m_read,m_write,m_TransCode,m_sCode,m_dCode);
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
	//bulid
	if (!BulidFile())
		return 0;
	//open
	string spath = m_sFilePath;
	if (!m_read->OpenFile(spath)) {
		m_treadstate.m_state = -1;
		SetLastError("ԭ�ļ���ʧ�ܣ�FileOperate::OpenFile");
		log.OutputLog(m_LastError);
		m_createFac.Release(m_read,m_write,m_TransCode,m_sCode,m_dCode);
		return 0;
	}
	if (m_read->m_FileSize == 0){
		m_treadstate.m_state = -1;
		SetLastError("�ļ�Ϊ�գ�FileOperate::OpenFile");
		log.OutputLog(m_LastError);
		m_read->CloseFile();
		m_createFac.Release(m_read,m_write,m_TransCode,m_sCode,m_dCode);
		return 0;
	}
	string dpath = m_dFilePath;
	if (!m_write->OpenFile(dpath)) {
		m_treadstate.m_state = -1;
		SetLastError("Ŀ���ļ���ʧ�ܣ�FileOperate::OpenFile");
		log.OutputLog(m_LastError);
		m_read->CloseFile();
		m_createFac.Release(m_read,m_write,m_TransCode,m_sCode,m_dCode);
		return 0;
	}
	m_treadstate.m_state = 1;
	m_treadstate.m_allWork = m_read->m_FileSize;
	//transform
	DWORD  readLineSize = 0;
	DWORD  transformSize = 0;
	m_readByte = new byte[BUFFER_SIZE];
	m_writeByte = new byte[BUFFER_SIZE];
	while (m_read->m_FileSize != m_read->m_FileReadSize) {
		EnterCriticalSection(&m_cs);
		//�߳���ֹ
		if (m_endflage == 1){
			CloseFile();
			m_treadstate.m_state = 0;
			return 2;
		}
		LeaveCriticalSection(&m_cs);
		m_treadstate.m_nowWork = m_read->m_FileReadSize;
		//read
		readLineSize = m_read->ReadFileLine(m_readByte, BUFFER_SIZE);
		if (readLineSize == -1) {
			m_treadstate.m_state = -1;
			SetLastError(m_read->GetLastError());
			CloseFile();
			return 0;
		}
		//transform
		transformSize = m_TransCode->TransformCode(m_readByte, m_writeByte, readLineSize);
		if (transformSize == -1) {
			m_treadstate.m_state = -1;
			SetLastError(m_TransCode->GetLastError());
			CloseFile();
			return 0;
		}
		//write
		if (!m_write->WriteFileline(m_writeByte, transformSize)) {
			m_treadstate.m_state = -1;
			SetLastError(m_write->GetLastError());
			CloseFile();
			return 0;
		}
	}
	//close
	if (!CloseFile())
		return 0;
	m_treadstate.m_state = 2;
	return 1;
}
/******************************************************************
��������CloseFile
����˵�����ر��ļ��ࡢת����
���룺void
�����bool
*******************************************************************/
bool TansControl::CloseFile(void) {
	delete  m_readByte;
	delete  m_writeByte;
	if (!m_write->CloseFile()) {
		m_treadstate.m_state = -1;
		SetLastError(m_write->GetLastError());
		return false;
	}
	if (!m_read->CloseFile()) {
		m_treadstate.m_state = -1;
		SetLastError(m_read->GetLastError());
		return false; 
	}
	m_createFac.Release(m_read,m_write,m_TransCode,m_sCode,m_dCode);
	return true;
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
