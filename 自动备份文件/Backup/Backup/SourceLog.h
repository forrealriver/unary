#pragma once
#include "Browse.h"
class SourceLog
{
public:
	SourceLog(void);
	~SourceLog(void);
	void SourceLog::OutputLog(CString msg);
	CString SourceLog::ReadPath();
	Browse m_browse;
};
