#pragma once

class Browse
{
public:
	Browse(void);
	~Browse(void);
	void Browse::SetLastError(CString lastErrInfo);
	CString Browse::GetLastError(void);
	CString Browse::BrowseForFolder(void);
	CString Browse::BrowseForFile(HWND m_hWnd);
	CString Browse::BrowseFileFor(void);
	CString Browse::GetWorkFold(void);

	CString m_LastError;
};
