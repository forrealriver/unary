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
	DWORD FileOperate::ReadFileLine(byte* readLine,DWORD readLineSize);
	bool FileOperate::WriteFileline(byte* buf, DWORD bufSize);
	bool FileOperate::CloseFile(void);
	virtual bool FileOperate::LineEnd(byte* ReadByte,DWORD &i,DWORD ReadPosition)=0;

	Log log;

	CString m_LastError;
	HANDLE m_Handle;
	DWORD m_bytesRead;
	DWORD m_bytesWrite;
	DWORD m_ReadPosition;
	DWORD m_FileSize;
	DWORD m_FileReadSize;
	DWORD m_bufferRead;
	DWORD m_ReadLen;
	DWORD m_endFlag;
	DWORD m_firstLen;
	byte * m_ReadByte;
};
