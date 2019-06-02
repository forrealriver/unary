#include "StdAfx.h"
#include "UnicodeOperate.h"

UnicodeOperate::UnicodeOperate(void){
	m_EenLen=3;
}
UnicodeOperate::~UnicodeOperate(void){}
/******************************************************************
函数名：LineEnd
功能说明：Unicode判断是否换行
输入：当前byte指针，i，指针位置，ReadPosition读取位置
输出：是否成功
*******************************************************************/
bool UnicodeOperate::LineEnd(byte* ReadByte,long i,long ReadPosition){
	if ((i+3<ReadPosition)&&(ReadByte[i] == 0x0D)&&(ReadByte[i+1] == 0x00)&&(ReadByte[i+2] == 0x0A)&&(ReadByte[i+3] == 0x00))
		return true;
	return false;
}