#pragma once
class Compare
{
public:
    Compare();
    ~Compare();
    int Compare::TimMax(CString findflie, CString &new_filename);
    void Compare::Warning(int warning, CString findflie);
	void Compare::setLastError(CString lastErrInfo);
	CString Compare::getLastError();

	CString lastError;
};

