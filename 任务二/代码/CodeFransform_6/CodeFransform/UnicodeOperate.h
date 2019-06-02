#pragma once
#include "FileOperate.h"
#include "string"
#include "iostream"
using namespace std;

class UnicodeOperate :public FileOperate
{
public:
	UnicodeOperate(void);
	~UnicodeOperate(void);
	bool UnicodeOperate::OpenFile(string sFilePath);
	long UnicodeOperate::ReadFileLine(byte* readLine,long readLineSize);
	long UnicodeOperate::ReadFileByte(long bytePosition);
	bool UnicodeOperate::CloseFile(void);
	bool UnicodeOperate::LineEnd(byte* ReadByte,long i,long ReadLen);
};
