#pragma once
#include "Log.h"
#include "TransformOperate.h"
class UTF8ToUnicode:public TransformOperate
{
public:
	UTF8ToUnicode(void);
	~UTF8ToUnicode(void);
	DWORD UTF8ToUnicode:: TransformCode(byte *utf8,byte *unicode,DWORD readLineSize);

	Log log;
	CString m_LastError;
};
