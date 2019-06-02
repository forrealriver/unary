#include "StdAfx.h"
#include "UnicodeOperate.h"

UnicodeOperate::UnicodeOperate(void)
{
	m_EenLen=3;
}

UnicodeOperate::~UnicodeOperate(void)
{
}
bool UnicodeOperate::LineEnd(byte* ReadByte,long i,long ReadLen)
{
	if ((i+3<ReadLen)&&(ReadByte[i] == 0x0D)&&(ReadByte[i+1] == 0x00)&&(ReadByte[i+2] == 0x0A)&&(ReadByte[i+3] == 0x00))
		return true;
	return false;
}