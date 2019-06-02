#pragma once

class Copy
{
public:
    Copy(void);
    ~Copy(void);
    int Copy::copyFold(CString source, CString target);
	void Copy::setLastError(CString lastErrInfo);
	CString Copy::getLastError();

	CString lastError;
};
