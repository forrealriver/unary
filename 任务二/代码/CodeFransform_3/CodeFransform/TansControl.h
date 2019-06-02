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
	TansControl(void);
	~TansControl(void);
	void TansControl::SetLastError(CString lastErrInfo);
	CString TansControl::GetLastError();
	bool TansControl::BulidFile(CString sCode,CString dCode);
	int TansControl::TransformFile(CString sFilePath,CString dFilePath,CString sCode,CString dCode);
	bool TansControl::CloseFile(void);

	CString m_SFilePath;
	CString m_DFildPath;
	CString m_SCode;
	CString m_DCode;
	CString m_LastError;
	Browse browse;
	CreateFactory m_createFac;
	FileOperate *m_read;
	FileOperate *m_write;
	TransformOperate *m_TransCode;
};
