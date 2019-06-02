#include "StdAfx.h"
#include "UTF8Operate.h"

UTF8Operate::UTF8Operate(void)
{
	m_EenLen=1;
}

UTF8Operate::~UTF8Operate(void)
{
}
bool UTF8Operate::LineEnd(byte* ReadByte,long i,long ReadLen){
	if ((i+1<ReadLen)&&(ReadByte[i] == 0x0D)&&(ReadByte[i+1] == 0x0A))
		return true;
	return false;
}