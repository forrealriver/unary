#include "StdAfx.h"
#include "UTF8Operate.h"

UTF8Operate::UTF8Operate(void){}
UTF8Operate::~UTF8Operate(void){}
/******************************************************************
��������LineEnd
����˵����UTF-8�ж��Ƿ���
���룺��ǰbyteָ�룬i��ָ��λ�ã�ReadPosition��ȡλ��
������Ƿ�ɹ�
*******************************************************************/
bool UTF8Operate::LineEnd(byte* ReadByte, DWORD &i, DWORD ReadPosition) {
	if ((i + 1 < ReadPosition) && (ReadByte[i] == 0x0D) && (ReadByte[i + 1] == 0x0A)){
		i=i+1;
		return true;
	}
	return false;
}