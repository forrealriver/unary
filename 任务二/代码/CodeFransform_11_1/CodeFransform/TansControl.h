#pragma once
#include "Browse.h"
#include "FileOperate.h"
#include "CreateFactory.h"
#include "TransformOperate.h"
#include "Log.h"
#include "string"
#include "iostream"
using namespace std;

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
	bool TansControl::CloseFile(void);

	CString sFilePath;
	CString dFilePath;
	CString sCode;
	CString dCode;
	CString m_LastError;

	DWORD allWork;
	DWORD nowWork;
	int state; //0δ��ʼ��1��ʼ��-1����2���

	Browse browse;
	CreateFactory m_createFac;
	FileOperate *m_read;
	FileOperate *m_write;
	TransformOperate *m_TransCode;

	HANDLE m_ThreadHandle;
	CRITICAL_SECTION cs;
};
