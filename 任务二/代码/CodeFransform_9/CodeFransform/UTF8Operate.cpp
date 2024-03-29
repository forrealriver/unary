#include "StdAfx.h"
#include "UTF8Operate.h"

UTF8Operate::UTF8Operate(void){
	m_EenLen=1;
}
UTF8Operate::~UTF8Operate(void){}
/******************************************************************
函数名：LineEnd
功能说明：UTF-8判断是否换行
输入：当前byte指针，i，指针位置，ReadPosition读取位置
输出：是否成功
*******************************************************************/
bool UTF8Operate::LineEnd(byte* ReadByte,long i,long ReadPosition){
	if ((i+1<ReadPosition)&&(ReadByte[i] == 0x0D)&&(ReadByte[i+1] == 0x0A))
		return true;
	return false;
}