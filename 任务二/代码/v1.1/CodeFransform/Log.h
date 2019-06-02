#pragma once
#include "Browse.h"
class Log
{
public:
	Log(void);
	~Log(void);
	void Log::OutputLog(CString msg);
	void Log::setLastError(CString lastErrInfo);
	CString Log::getLastError();

	CString m_lastError;
	Browse m_browse;
};
