#include "StdAfx.h"
#include "TansControl.h"
#define BUFFER_SIZE 1024*10
TansControl::TansControl(CString sfilepath,CString dfilepath,CString scode,CString dcode){
	sFilePath=sfilepath;
	dFilePath=dfilepath;
	sCode=scode;
	dCode=dcode;
	state=0;
}

TansControl::~TansControl(void)
{
}


void TansControl::SetLastError(CString lastErrInfo){
	m_LastError=lastErrInfo;
}
CString TansControl::GetLastError(){
	return m_LastError;
}

DWORD WINAPI TansControl::TreadProcess(LPVOID lpParam) {
	TansControl *tansControl=(TansControl*)lpParam;
	int x=tansControl->TransformFile();
	return x;
}

bool TansControl::BulidFile(){
	m_read=m_createFac.CreateFile(sCode);
	m_write=m_createFac.CreateFile(dCode);
	m_TransCode=m_createFac.CreateFrans(sCode,dCode);
	if (!m_read || !m_write ||!m_TransCode){
		EnterCriticalSection(&cs);
		state=-1;
		LeaveCriticalSection(&cs);
		SetLastError(m_createFac.GetLastError());	
		return false;
	}
	return true;
}

int TansControl::TransformFile(){
	//bulid
	if (!BulidFile())
		return 0;
	//open
	string spath=sFilePath;
	if (! m_read->OpenFile(spath)){
		EnterCriticalSection(&cs);
		state=-1;
		LeaveCriticalSection(&cs);
		SetLastError(m_read->GetLastError());
		delete m_read;
		delete m_write;
		delete m_TransCode;	
		return 0;
	}

	string dpath=dFilePath;
	if (! m_write->OpenFile(dpath)){
		EnterCriticalSection(&cs);
		state=-1;
		LeaveCriticalSection(&cs);
		SetLastError(m_write->GetLastError());
		delete m_read;
		delete m_write;
		delete m_TransCode;
		return 0;
	}
	EnterCriticalSection(&cs);
	state=1;
	allWork=m_read->m_FileSize;
	LeaveCriticalSection(&cs);
	//transform
	byte* readByte = new byte[BUFFER_SIZE];
	byte* writeByte = new byte[BUFFER_SIZE];
	long  readLineSize=0;
	long  transformSize=0;
	while(m_read->m_FileSize != m_read->m_FileReadSize){
		EnterCriticalSection(&cs);
		nowWork=m_read->m_FileReadSize;
		LeaveCriticalSection(&cs);
		//read
		readLineSize=m_read->ReadFileLine(readByte,BUFFER_SIZE);
		if (readLineSize==-1){
			EnterCriticalSection(&cs);
			state=-1;
			LeaveCriticalSection(&cs);
			SetLastError(m_read->GetLastError());
			CloseFile();
			return 0;
		}
		//transform
		transformSize=m_TransCode->TransformCode(readByte,writeByte,readLineSize);
		if (transformSize==-1){
			EnterCriticalSection(&cs);
			state=-1;
			LeaveCriticalSection(&cs);
			SetLastError(m_TransCode->GetLastError());
			CloseFile();
			return 0;
		}
		//write
		if (!m_write->WriteFileline(writeByte,transformSize)){
			EnterCriticalSection(&cs);
			state=-1;
			LeaveCriticalSection(&cs);
			SetLastError(m_write->GetLastError());		
			CloseFile();	
			return 0;
		}
	}
	//close
	if(!CloseFile())
		return 0;
	EnterCriticalSection(&cs);
	state=2;
	LeaveCriticalSection(&cs);
	return 1;
}

bool TansControl::CloseFile(void){
	if (!m_write->CloseFile()){
		EnterCriticalSection(&cs);
		state=-1;
		LeaveCriticalSection(&cs);
		SetLastError(m_write->GetLastError());
		return false;
	}
	if (!m_read->CloseFile()){
		EnterCriticalSection(&cs);
		state=-1;
		LeaveCriticalSection(&cs);
		SetLastError(m_read->GetLastError());
		return false;
	}
	m_read=NULL;
	m_write=NULL;
	m_TransCode=NULL;
	delete m_read;
	delete m_write;
	delete m_TransCode;
	return true;
}