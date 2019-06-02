#include "StdAfx.h"
#include "Function.h"

Function::Function(void)
{
}

Function::~Function(void)
{
}
void Function::setLastError(CString lastErrInfo)
{
	lastError=lastErrInfo;
}
CString Function::getLastError()
{
	return lastError;
}

int Function::TransformBegin(CString sFilePath,CString dFilePath,CString sCode,CString dCode)
{
	return 1;
}