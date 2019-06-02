#pragma once
#include "FileOperate.h"
#include "string"
#include "iostream"
using namespace std;

class UTF8Operate : public FileOperate
{
public:
	UTF8Operate(void);
	~UTF8Operate(void);
	bool UTF8Operate::OpenFile(string sFilePath);
	DWORD UTF8Operate::ReadFileLine(byte* readLine,DWORD readLineSize);
	DWORD UTF8Operate::ReadFileByte(DWORD bytePosition);
	bool UTF8Operate::CloseFile(void);
	bool UTF8Operate::LineEnd(byte* ReadByte,DWORD i,DWORD ReadPosition);
};
