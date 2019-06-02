#include "StdAfx.h"
#include "UTF8ToUnicode.h"

UTF8ToUnicode::UTF8ToUnicode(void){}
UTF8ToUnicode::~UTF8ToUnicode(void){}
/******************************************************************
函数名：TransformCode
功能说明：UTF-8转Unicode
输入：utf8 byte指针，Unicode byte指针，readLineSize Unicode长度
输出：转换后的长度
*******************************************************************/
DWORD UTF8ToUnicode::TransformCode(byte *utf8, byte *unicode, DWORD readLineSize) {
	char *UTF8 = (char*)utf8;
	WCHAR *Unicode = (WCHAR*)unicode;
	DWORD len = 0;
	len = MultiByteToWideChar(CP_UTF8, NULL, UTF8, readLineSize, NULL, 0);
	memset(Unicode, 0, len);
	len = MultiByteToWideChar(CP_UTF8, NULL, UTF8, readLineSize, Unicode, len);
	if (!len) {
		SetLastError("转码失败：UTF8ToUnicode:: TransformCode");
		log.OutputLog(m_LastError);
		return -1;
	}
	Unicode[len] = '\0';
	return 2 * len;
}