#pragma once
#include "Browse.h"
#include "FileOperate.h"
#include "CreateFactory.h"
#include "TransformOperate.h"
#include "Log.h"
#include "string"
#include "iostream"
using namespace std;

struct TreadState{
	DWORD m_allWork;
	DWORD m_nowWork;
	int m_state; //0未开始，1开始，-1出错，2完成
};
class TansControl
{
public:
	TansControl(CString sfilepath,CString dfilepath,CString scode,CString dcode);
	~TansControl(void);
	void TansControl::SetLastError(CString lastErrInfo);
	CString TansControl::GetLastError();
	static DWORD WINAPI TansControl::TreadProcess(LPVOID lpParam);
	bool TansControl::BulidFile(void);
	int TansControl::TransformFile(void);
	void TansControl::GetState(TreadState &state);
	CString m_sFilePath;
	CString m_dFilePath;
	CString m_sCode;
	CString m_dCode;
	CString m_LastError;

	Browse m_browse;
	CreateFactory m_createFac;
	FileOperate *m_read;
	FileOperate *m_write;
	TransformOperate *m_TransCode;
	Log log;
	
	TreadState m_treadstate;
	DWORD m_endflage;

	HANDLE m_ThreadHandle;
	CRITICAL_SECTION m_cs;
};
