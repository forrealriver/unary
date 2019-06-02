#include "StdAfx.h"
#include "FileOperate.h"

#define BUFFER_SIZE 1024*1024

FileOperate::FileOperate(void) {
	m_ReadByte =  new byte[BUFFER_SIZE];
	memset(m_ReadByte,0,BUFFER_SIZE);
	m_bufferRead=0;
	m_FileSize=0;
	m_FileReadSize=0;
	m_ReadPosition = BUFFER_SIZE-1;
	m_bytesWrite=0;
}

FileOperate::~FileOperate(void) {
	delete m_ReadByte;
}

void FileOperate::SetLastError(CString lastErrInfo) {
	m_LastError = lastErrInfo;
}

CString FileOperate::GetLastError() {
	return m_LastError;
}

bool FileOperate::OpenFile(string sFilePath) {
	m_Handle = CreateFile(sFilePath.c_str(),
		GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, 0, NULL);
	if(m_Handle==INVALID_HANDLE_VALUE){
		SetLastError("文件打开失败");
		log.OutputLog(m_LastError);
		CloseHandle(m_Handle);
		return false;
	}
	m_FileSize = GetFileSize(m_Handle ,NULL);
	return true;
}

long FileOperate::ReadFileByte(long bytePosition) {
	long readByteSize;
	if (m_FileSize - m_bufferRead > BUFFER_SIZE)
		readByteSize = BUFFER_SIZE - bytePosition;
	else
		readByteSize = m_FileSize - m_bufferRead;
	if(!ReadFile(m_Handle, m_ReadByte + bytePosition , 
		readByteSize, &m_bytesRead, NULL)){
		SetLastError("读文件失败");
		log.OutputLog(m_LastError);
		CloseHandle(m_Handle);
		return -1;
	}
	m_bufferRead += readByteSize;
	return readByteSize;
}

long FileOperate::ReadFileLine(byte* readLine,long readLineSize) {
	memset(readLine,0,readLineSize);
	long lineSize=0;
	long readByteSize=0;
	long bytePosition=0;
	long i=0;
	while (m_FileReadSize != m_FileSize){
		if (m_ReadPosition == BUFFER_SIZE-1){           //上次byte已读完
			i=0;
			readByteSize=ReadFileByte(bytePosition);
			if(readByteSize==-1)
				return -1;
			m_ReadLen=readByteSize+bytePosition;
		}
		else  //byte未读完
			i=m_ReadPosition+1;

		for (;i<m_ReadLen;i++){
			if(LineEnd(m_ReadByte,i,m_ReadLen)){  //有换行
				i=i+m_EenLen;
				if(m_ReadPosition == BUFFER_SIZE-1){
					lineSize=i+1;
					if (lineSize>readLineSize){
						SetLastError("行长度过长");
						log.OutputLog(m_LastError);
						return -1;
					}
					m_ReadPosition=0;
					memcpy(readLine, m_ReadByte + m_ReadPosition, lineSize);
				}
				else{
					lineSize=i-m_ReadPosition;
					if (lineSize>readLineSize){
						SetLastError("行长度过长");
						log.OutputLog(m_LastError);
						return -1;
					}
					memcpy(readLine, m_ReadByte + m_ReadPosition+1, lineSize);
				}
				m_ReadPosition=i;
				m_FileReadSize+=lineSize;
				return lineSize;
			}
		}
		if (m_bytesRead == m_FileSize||BUFFER_SIZE+m_bytesRead == m_FileSize){
			if (m_ReadPosition == BUFFER_SIZE-1){
				lineSize = m_FileSize - m_FileReadSize;
				if (lineSize>readLineSize){
					SetLastError("行长度过长");
					log.OutputLog(m_LastError);
					return -1;
				}
				memcpy(readLine, m_ReadByte , lineSize);
			}
			else{
				lineSize = m_FileSize - m_FileReadSize;
				if (lineSize>readLineSize){
					SetLastError("行长度过长");
					log.OutputLog(m_LastError);
					return -1;
				}
				memcpy(readLine, m_ReadByte + m_ReadPosition+1 , lineSize);
			}
			m_ReadPosition = i;
			m_FileReadSize += lineSize;
			return lineSize;
		}
		//后面byte没有换行
		bytePosition=BUFFER_SIZE-m_ReadPosition-1;
		memmove(m_ReadByte,m_ReadByte+m_ReadPosition+1,bytePosition);
		m_ReadPosition = BUFFER_SIZE-1;
	}
	return -1;
}

bool FileOperate::WriteFileline(byte* buf, long bufSize) {
	if(!WriteFile(m_Handle,buf,bufSize,&m_bytesWrite,NULL)){
		SetLastError("写文件失败");
		log.OutputLog(m_LastError);
		CloseHandle(m_Handle);
		return false;
	}
	return true;
}

bool FileOperate::CloseFile() {
	if(m_Handle!=NULL){
		if(!CloseHandle(m_Handle)){
			SetLastError("文件关闭失败");
			log.OutputLog(m_LastError);
			return false;
		}
	}
	else{
		SetLastError("文件句柄为空");
		log.OutputLog(m_LastError);
		return false;
	}
	return true;
}