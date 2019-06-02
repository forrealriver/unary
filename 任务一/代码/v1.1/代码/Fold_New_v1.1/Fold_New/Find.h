#pragma once

class Find
{
public:
    Find(void);
    ~Find(void);
    int Find::FindFold(CString sFolderPath,  CStringArray  &FileNames);
	void Find::setLastError(CString lastErrInfo);
	CString Find::getLastError();

	CString lastError;
};
