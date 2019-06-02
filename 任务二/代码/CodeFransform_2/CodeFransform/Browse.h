#pragma once

class Browse
{
public:
	Browse(void);
	~Browse(void);
	void Browse::setLastError(CString lastErrInfo);
	CString Browse::getLastError(void);
	CString Browse::BrowseForFolder(void);
	CString Browse::BrowseForFile(HWND m_hWnd);
	CString Browse::BrowseFileFor(void);
	CString Browse::GetWorkFold(void);

	CString m_LastError;
};
