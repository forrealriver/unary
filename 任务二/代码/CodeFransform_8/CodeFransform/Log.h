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

	CString lastError;
	Browse browse;
};
