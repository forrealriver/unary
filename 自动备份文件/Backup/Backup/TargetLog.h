#pragma once
#include "Browse.h"
class TargetLog
{
public:
	TargetLog(void);
	~TargetLog(void);
	void TargetLog::OutputLog(CString msg);
	CString TargetLog::ReadPath();
	Browse m_browse;
};
