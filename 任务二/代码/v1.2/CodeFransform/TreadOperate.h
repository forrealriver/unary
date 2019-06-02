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
	int TreadOperate::getState(TreadState &state);
	void TreadOperate::killTread(void);
	CString m_LastError;
	Log log;
	TreadState m_treadstate;
	TansControl * m_tansControl;
};
