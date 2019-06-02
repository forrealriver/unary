#pragma once
#include "FileOperate.h"
#include <string>
#include <iostream>
using namespace std;
class UTF8Operate : public FileOperate
{
public:
	UTF8Operate(void);
	~UTF8Operate(void);
	bool UTF8Operate::OpenFile(string sFilePath);
	long UTF8Operate::ReadFileLine(byte* readLine,long readLineSize);
	long UTF8Operate::ReadFileByte(long bytePosition);
	bool UTF8Operate::CloseFile(void);
	bool UTF8Operate::LineEnd(byte* ReadByte,long i,long ReadLen);
};
