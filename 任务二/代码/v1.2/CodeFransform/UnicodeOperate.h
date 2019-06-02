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
	DWORD UnicodeOperate::ReadFileLine(byte* readLine,DWORD readLineSize);
	DWORD UnicodeOperate::ReadFileByte(DWORD bytePosition);
	bool UnicodeOperate::CloseFile(void);
	bool UnicodeOperate::LineEnd(byte* ReadByte,DWORD &i,DWORD ReadPosition);
};
