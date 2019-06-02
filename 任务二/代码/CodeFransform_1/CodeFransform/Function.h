#pragma once
#include "Browse.h"
class Function
{
public:
	Function(void);
	~Function(void);
	void Function::setLastError(CString lastErrInfo);
	CString Function::getLastError();
	int Function::TransformBegin(CString sFilePath,CString dFilePath,CString sCode,CString dCode);

	CString sFilePath;
	CString dFildPath;
	CString sCode;
	CString dCode;
	CString lastError;
	Browse browse;
};
