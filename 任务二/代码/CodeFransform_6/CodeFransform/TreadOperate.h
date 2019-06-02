#pragma once
#include "TansControl.h"
#include "Log.h"

class TreadOperate
{
public:
	TreadOperate(void);
	~TreadOperate(void);
	void TreadOperate::SetLastError(CString lastErrInfo);
	CString TreadOperate::GetLastError();
	bool TreadOperate::creadTread(CString sfilepath,CString dfilepath,CString scode,CString dcode);
	int TreadOperate::getState(void);
	void TreadOperate::stopTread(void);
	CString m_LastError;
	Log log;
	TansControl * tansControl;
};
