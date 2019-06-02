#include "StdAfx.h"
#include "NewTime.h"
NewTime::NewTime(void){}
NewTime::~NewTime(void){}

CString NewTime::newTime(CString filePath){
	CFileStatus status;
	CFile::GetStatus(filePath,status);
	CString m_strmodifytime;
	m_strmodifytime.Format(status.m_mtime.Format("%Y%m%d%H%M%S"));
	return m_strmodifytime; 
}
float NewTime::sizefile(CString filePath){
	CFileStatus status;
	CFile::GetStatus(filePath,status);
	return (float)status.m_size;
}
