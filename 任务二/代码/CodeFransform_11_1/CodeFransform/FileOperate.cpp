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
}
FileOperate::~FileOperate(void){}
void FileOperate::SetLastError(CString lastErrInfo) {
	m_LastError = lastErrInfo;
}
CString FileOperate::GetLastError() {
	return m_LastError;
}
/******************************************************************
��������OpenFile
����˵�������ļ������ļ����
���룺�ļ�·��
������Ƿ�������
*******************************************************************/
bool FileOperate::OpenFile(string sFilePath) {
	m_Handle = CreateFile(sFilePath.c_str(),
		GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, 0, NULL);
	if (m_Handle == INVALID_HANDLE_VALUE) {
		SetLastError("�ļ���ʧ�ܣ�FileOperate::OpenFile");
		log.OutputLog(m_LastError);
		CloseHandle(m_Handle);
		return false;
	}
	m_FileSize = GetFileSize(m_Handle, NULL);
	return true;
}
/******************************************************************
��������ReadFileLine
����˵�������ж�ȡ�ļ�
���룺readLine  byteָ�����ڴ�Ŷ�ȡ���ݣ�readLineSize����ȡ����
���������ʵ�ʶ�ȡ����
*******************************************************************/
DWORD FileOperate::ReadFileLine(byte* readLine, DWORD readLineSize) {
	memset(readLine, 0, readLineSize);
	DWORD lineSize = 0;
	DWORD readByteSize = 0;
	DWORD bytePosition = 0;
	DWORD i = 0;
	while (m_FileReadSize != m_FileSize) {
		if (m_ReadPosition == BUFFER_SIZE - 1) {           //�ϴ�byte�Ѷ���
			i = 0;
			if (m_FileSize - m_bufferRead > BUFFER_SIZE)
				readByteSize = BUFFER_SIZE - bytePosition;
			else
				readByteSize = m_FileSize - m_bufferRead;
			if (!ReadFile(m_Handle, m_ReadByte + bytePosition,
				readByteSize, &m_bytesRead, NULL)) {
				SetLastError("�ļ���ȡʧ�ܣ�FileOperate::ReadFileLine");
				log.OutputLog(m_LastError);
				CloseHandle(m_Handle);
				return -1;
			}
			m_bufferRead += readByteSize;
			m_ReadLen = readByteSize + bytePosition;
		}
		else  //byteδ����
			i = m_ReadPosition + 1;

		for (; i < m_ReadLen; i++) {
			if (LineEnd(m_ReadByte, i, m_ReadLen)) {  //�л���
				i = i + m_EenLen;
				if (m_ReadPosition == BUFFER_SIZE - 1) {
					lineSize = i + 1;
					if (lineSize > readLineSize) {
						SetLastError("�г��ȹ�����FileOperate::ReadFileLine");
						log.OutputLog(m_LastError);
						return -1;
					}
					m_ReadPosition = 0;
					memcpy(readLine, m_ReadByte + m_ReadPosition, lineSize);
				}
				else {
					lineSize = i - m_ReadPosition;
					if (lineSize > readLineSize) {
						SetLastError("�г��ȹ�����FileOperate::ReadFileLine");
						log.OutputLog(m_LastError);
						return -1;
					}
					memcpy(readLine, m_ReadByte + m_ReadPosition + 1, lineSize);
				}
				m_ReadPosition = i;
				m_FileReadSize += lineSize;
				return lineSize;
			}
		}
		if (BUFFER_SIZE + m_bytesRead == m_FileSize || m_bytesRead == m_FileSize) {
			if (m_ReadPosition == BUFFER_SIZE - 1) {
				lineSize = m_FileSize - m_FileReadSize;
				if (lineSize > readLineSize) {
					SetLastError("�г��ȹ�����FileOperate::ReadFileLine");
					log.OutputLog(m_LastError);
					return -1;
				}
				memcpy(readLine, m_ReadByte, lineSize);
			}
			else {
				lineSize = m_FileSize - m_FileReadSize;
				if (lineSize > readLineSize) {
					SetLastError("�г��ȹ�����FileOperate::ReadFileLine");
					log.OutputLog(m_LastError);
					return -1;
				}
				memcpy(readLine, m_ReadByte + m_ReadPosition + 1, lineSize);
			}
			m_ReadPosition = i;
			m_FileReadSize += lineSize;
			return lineSize;
		}
		//����byteû�л��У��ƶ�+���
		bytePosition = BUFFER_SIZE - m_ReadPosition - 1;
		memmove(m_ReadByte, m_ReadByte + m_ReadPosition + 1, bytePosition);
		m_ReadPosition = BUFFER_SIZE - 1;
	}
	return -1;
}
/******************************************************************
��������WriteFileline
����˵����д������
���룺writeLine  byteָ�����ڴ��д�����ݣ�writeSizeд�볤��
������Ƿ�д��ɹ�
*******************************************************************/
bool FileOperate::WriteFileline(byte* writeLine, DWORD writeSize) {
	if (!WriteFile(m_Handle, writeLine, writeSize, &m_bytesWrite, NULL)) {
		SetLastError("д�ļ�ʧ�ܣ�FileOperate::WriteFileline");
		log.OutputLog(m_LastError);
		CloseHandle(m_Handle);
		return false;
	}
	return true;
}
/******************************************************************
��������CloseFile
����˵�����ر��ļ�
���룺void
������Ƿ�رճɹ�
*******************************************************************/
bool FileOperate::CloseFile() {
	if (m_Handle != NULL) {
		if (!CloseHandle(m_Handle)) {
			SetLastError("�ļ��ر�ʧ�ܣ�FileOperate::CloseFile()");
			log.OutputLog(m_LastError);
			return false;
		}
	}
	return true;
}