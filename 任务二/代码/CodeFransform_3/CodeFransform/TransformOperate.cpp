#include "StdAfx.h"
#include "TransformOperate.h"

TransformOperate::TransformOperate(void)
{
}

TransformOperate::~TransformOperate(void)
{
}

void TransformOperate::SetLastError(CString lastErrInfo)
{
	m_LastError=lastErrInfo;
}
CString TransformOperate::GetLastError()
{
	return m_LastError;
}