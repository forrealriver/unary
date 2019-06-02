#include "StdAfx.h"
#include "FileOperate.h"

#define BUFFER_SIZE 1024*1024

FileOperate::FileOperate(void) {
	m_ReadByte = new byte[BUFFER_SIZE];
	memset(m_ReadByte, 0, BUFFER_SIZE);
	m_bufferRead = 0;
	m_FileSize = 0;
	m_FileReadSize = 0;
	m_ReadPosition = BUFFER_SIZE - 1;
	m_bytesWrite = 0;
	m_endFlag = 0;
}
FileOperate::~FileOperate(void){}
void FileOperate::SetLastError(CString lastErrInfo) {
	m_LastError = lastErrInfo;
}
CString FileOperate::GetLastError() {
	return m_LastError;
}
/******************************************************************
函数名：OpenFile
功能说明：打开文件，文件句柄
输入：文件路径
输出：是否正常打开
*******************************************************************/
bool FileOperate::OpenFile(string sFilePath) {
	m_Handle = CreateFile(sFilePath.c_str(),
		GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, 0, NULL);
	if (m_Handle == INVALID_HANDLE_VALUE) {
		CloseHandle(m_Handle);
		return false;
	}
	m_FileSize = GetFileSize(m_Handle, NULL);
	return true;
}
/******************************************************************
函数名：ReadFileLine
功能说明：按行读取文件
输入：readLine  byte指针用于存放读取内容，readLineSize最大读取长度
输出：返回实际读取长度
*******************************************************************/
DWORD FileOperate::ReadFileLine(byte* readLine, DWORD readLineSize) {
	memset(readLine, 0, readLineSize);
	DWORD lineSize = 0;
	DWORD readByteSize = 0;
	DWORD bytePosition = 0;
	DWORD i = 0;
	while (m_FileReadSize != m_FileSize) {
		//读取
		if (m_ReadPosition == BUFFER_SIZE - 1) {          
			i = 0;
			if (m_FileSize - m_bufferRead > BUFFER_SIZE)
				readByteSize = BUFFER_SIZE - bytePosition;
			else
				readByteSize = m_FileSize - m_bufferRead;
			if (!ReadFile(m_Handle, m_ReadByte + bytePosition,
				readByteSize, &m_bytesRead, NULL)) {
				SetLastError("文件读取失败：FileOperate::ReadFileLine");
				log.OutputLog(m_LastError);
				CloseHandle(m_Handle);
				return -1;
			}
			m_endFlag += m_bytesRead;
			m_bufferRead += readByteSize;
			m_ReadLen = readByteSize + bytePosition;
		}
		else  
			i = m_ReadPosition + 1;
		//查找换行
		for (; i < m_ReadLen; i++) {
			if (LineEnd(m_ReadByte, i, m_ReadLen)) { 
				if (m_ReadPosition == BUFFER_SIZE - 1){
					lineSize = i + 1;
					m_firstLen = 0;
				}
				else {
					lineSize = i - m_ReadPosition;
					m_firstLen = m_ReadPosition+1;
				}
				if (lineSize > readLineSize) {
					SetLastError("行长度过长：FileOperate::ReadFileLine");
					log.OutputLog(m_LastError);
					return -1;
				}
				memcpy(readLine, m_ReadByte + m_firstLen, lineSize);
				m_FileReadSize += lineSize;
				m_ReadPosition = i;
				return lineSize;
			}
		}
		//最后一行没有换行符时直接返回
		if (m_endFlag == m_FileSize) {
			if (m_ReadPosition == BUFFER_SIZE - 1)
				m_firstLen = 0;
			else 
				m_firstLen = m_ReadPosition+1;
			lineSize = m_FileSize - m_FileReadSize;
			if (lineSize > readLineSize) {
				SetLastError("行长度过长或转码类型错误");
				log.OutputLog(m_LastError);
				return -1;
			}
			memcpy(readLine, m_ReadByte + m_firstLen, lineSize);
			m_FileReadSize += lineSize;
			m_ReadPosition = i;	
			return lineSize;
		}
		//后面byte没有换行，移动+标记
		bytePosition = BUFFER_SIZE - m_ReadPosition - 1;
		memmove(m_ReadByte, m_ReadByte + m_ReadPosition + 1, bytePosition);
		m_ReadPosition = BUFFER_SIZE - 1;
	}
	return -1;
}
/******************************************************************
函数名：WriteFileline
功能说明：写入内容
输入：writeLine  byte指针用于存放写入内容，writeSize写入长度
输出：是否写入成功
*******************************************************************/
bool FileOperate::WriteFileline(byte* writeLine, DWORD writeSize) {
	if (!WriteFile(m_Handle, writeLine, writeSize, &m_bytesWrite, NULL)) {
		SetLastError("写文件失败：FileOperate::WriteFileline");
		log.OutputLog(m_LastError);
		CloseHandle(m_Handle);
		return false;
	}
	return true;
}
/******************************************************************
函数名：CloseFile
功能说明：关闭文件
输入：void
输出：是否关闭成功
*******************************************************************/
bool FileOperate::CloseFile() {
	if (m_Handle != NULL) {
		if (!CloseHandle(m_Handle)) {
			SetLastError("文件关闭失败：FileOperate::CloseFile()");
			log.OutputLog(m_LastError);
			return false;
		}
	}
	return true;
}