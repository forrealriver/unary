#include "StdAfx.h"
#include "UnicodeOperate.h"

UnicodeOperate::UnicodeOperate(void){
	m_EenLen=3;
}
UnicodeOperate::~UnicodeOperate(void){}
/******************************************************************
��������LineEnd
����˵����Unicode�ж��Ƿ���
���룺��ǰbyteָ�룬i��ָ��λ�ã�ReadPosition��ȡλ��
������Ƿ�ɹ�
*******************************************************************/
bool UnicodeOperate::LineEnd(byte* ReadByte,long i,long ReadPosition){
	if ((i+3<ReadPosition)&&(ReadByte[i] == 0x0D)&&(ReadByte[i+1] == 0x00)&&(ReadByte[i+2] == 0x0A)&&(ReadByte[i+3] == 0x00))
		return true;
	return false;
}