#include "StdAfx.h"
#include "UnicodeToUTF8.h"

UnicodeToUTF8::UnicodeToUTF8(void){}
UnicodeToUTF8::~UnicodeToUTF8(void){}
/******************************************************************
函数名：TransformCode
功能说明：Unicode转UTF-8
输入：Unicode byte指针，utf8 byte指针，readLineSize Unicode长度
输出：转换后的长度
*******************************************************************/
DWORD UnicodeToUTF8:: TransformCode(byte *unicode,byte *utf8,DWORD readLineSize){
	char *UTF8=(char*)utf8;
	wchar_t *Unicode=(wchar_t*)unicode;
	DWORD len = 0;
	readLineSize=readLineSize/sizeof(wchar_t);
	len = WideCharToMultiByte(CP_UTF8,0,Unicode,readLineSize,NULL,0,NULL,NULL); 
	memset(UTF8,0,len);
	len = WideCharToMultiByte(CP_UTF8,0,Unicode,readLineSize,UTF8,len,NULL,NULL);
	if(!len){
		SetLastError("转码失败：UnicodeToUTF8:: TransformCode");
		log.OutputLog(m_LastError);
		return -1;
	}
	return len;  
}