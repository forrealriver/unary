#include "StdAfx.h"
#include "UnicodeToUTF8.h"

UnicodeToUTF8::UnicodeToUTF8(void){}
UnicodeToUTF8::~UnicodeToUTF8(void){}
/******************************************************************
��������TransformCode
����˵����UnicodeתUTF-8
���룺Unicode byteָ�룬utf8 byteָ�룬readLineSize Unicode����
�����ת����ĳ���
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
		SetLastError("ת��ʧ�ܣ�UnicodeToUTF8:: TransformCode");
		log.OutputLog(m_LastError);
		return -1;
	}
	return len;  
}