#pragma once
#include "Log.h"
#include "NewTime.h"
class Find
{
public:
	Find(CString sourc, CString targe);
	~Find(void);
	int Find::findFile();
	static DWORD WINAPI Find::TreadProcess(LPVOID lpParam);
	NewTime newtime;
	bool flage;
	Log log;
	CStringArray name;
	CStringArray time;
	CString source;
	CString target;
	HANDLE m_ThreadHandle;
	CRITICAL_SECTION m_cs;
	int m_endflage;
};
