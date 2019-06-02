#include "StdAfx.h"
#include "UTF8ToUnicode.h"

UTF8ToUnicode::UTF8ToUnicode(void)
{
}

UTF8ToUnicode::~UTF8ToUnicode(void)
{
}
long UTF8ToUnicode:: TransformCode(byte *utf8,byte *unicode,long readLineSize){
	char *UTF8=(char*)utf8;
	WCHAR *Unicode=(WCHAR*)unicode;
	DWORD len = 0;
	len = MultiByteToWideChar(CP_UTF8,NULL,UTF8,readLineSize,NULL,0);
	memset(Unicode,0,len);
	len = MultiByteToWideChar(CP_UTF8,NULL,UTF8,readLineSize,Unicode,len); 
	if(!len)  {
		SetLastError("×ªÂëÊ§°Ü");
		log.OutputLog(m_LastError);
		return -1;
	}
	Unicode[len] = '\0';
	return 2*len;  
}