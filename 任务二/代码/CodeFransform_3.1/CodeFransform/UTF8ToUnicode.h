#pragma once
#include "Log.h"
#include "TransformOperate.h"
class UTF8ToUnicode:public TransformOperate
{
public:
	UTF8ToUnicode(void);
	~UTF8ToUnicode(void);
	long UTF8ToUnicode:: TransformCode(byte *utf8,byte *unicode,long readLineSize);

	Log log;
	CString m_LastError;
};
