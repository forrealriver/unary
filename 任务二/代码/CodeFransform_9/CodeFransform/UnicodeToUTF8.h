#pragma once
#include "Log.h"
#include "TransformOperate.h"
class UnicodeToUTF8:public TransformOperate
{
public:
	UnicodeToUTF8(void);
	~UnicodeToUTF8(void);
	long UnicodeToUTF8:: TransformCode(byte *unicode,byte *utf8,long readLineSize);

	Log log;
	CString m_LastError;
};
