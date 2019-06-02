#pragma once
#include "Log.h"
#include "string"
#include "iostream"
using namespace std;

class FileOperate
{
public:
	FileOperate(void);
	~FileOperate(void);
	void FileOperate::SetLastError(CString lastErrInfo) ;
	CString FileOperate::GetLastError(void) ;
	bool FileOperate::OpenFile(string sFilePath);
	long FileOperate::ReadFileLine(byte* readLine,long readLineSize);
	bool FileOperate::WriteFileline(byte* buf, long bufSize);
	bool FileOperate::CloseFile(void);
	virtual bool FileOperate::LineEnd(byte* ReadByte,long i,long ReadPosition)=0;

	Log log;

	CString m_LastError;
	HANDLE m_Handle;
	DWORD m_bytesRead;
	DWORD m_bytesWrite;
	long m_ReadPosition;
	long m_FileSize;
	long m_FileReadSize;
	long m_bufferRead;
	long m_ReadLen;
	int m_EenLen;
	byte * m_ReadByte;
};
