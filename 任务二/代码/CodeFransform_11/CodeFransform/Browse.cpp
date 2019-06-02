#include "StdAfx.h"
#include "Browse.h"

Browse::Browse(void){}
Browse::~Browse(void){}
void Browse::SetLastError(CString lastErrInfo) {
	m_LastError=lastErrInfo;
}
CString Browse::GetLastError() {
	return m_LastError;
}
/******************************************************************
��������BrowseForFolder
����˵��������ļ���Ŀ¼��
���룺void
������ļ���·��
*******************************************************************/
CString Browse::BrowseForFolder(void) {
    BROWSEINFO sInfo;
    ::ZeroMemory(&sInfo, sizeof(BROWSEINFO));
    sInfo.pidlRoot = 0;
    sInfo.lpszTitle = _T("��ѡ��һ���ļ��У�");
    sInfo.ulFlags = BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE | BIF_EDITBOX;
    sInfo.lpfn = NULL;
    LPITEMIDLIST lpidlBrowse = ::SHBrowseForFolder(&sInfo);
    TCHAR FolderPath[MAX_PATH] = {0};
    ::SHGetPathFromIDList(lpidlBrowse, FolderPath);
    return FolderPath;
}
/******************************************************************
��������BrowseForFile
����˵��������ļ�Ŀ¼��
���룺void
������ļ�·��
*******************************************************************/
CString Browse::BrowseForFile(HWND m_hWnd) {
	TCHAR path[MAX_PATH] = {0};   
	CString str;
	OPENFILENAME of= {0};   
	of.lStructSize = sizeof(of);   
	of.hwndOwner = m_hWnd;   
	of.lpstrFilter = _T("txt�ļ�(*.txt)\0*.txt\0"); 
	of.lpstrFile = path; 
	of.nMaxFile = sizeof(path)/sizeof(*path);   
	of.nFilterIndex = 0;   
	of.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER ;
	BOOL bSel = GetOpenFileName(&of);   
	str.Format(path);
	return str;
}
/******************************************************************
��������BrowseFileFor
����˵�������ΪĿ¼��
���룺void
������ļ�·��
*******************************************************************/
CString Browse::BrowseFileFor() {
	CString filepath;  
	TCHAR szFilter[] = _T("�ı��ļ�(*.txt)|*.txt|�����ļ�(*.*)|*.*||");  
	CFileDialog fileDlg(FALSE, _T("txt"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);  
	if (IDOK == fileDlg.DoModal()) {
		filepath = fileDlg.GetPathName();
		return filepath;
	}
	else return CString("");
}
/******************************************************************
��������GetWorkDir
����˵������õ�ǰ��Ŀ��·��
���룺void
�������ǰ��Ŀ��·��
*******************************************************************/
CString Browse::GetWorkFold() {
    HMODULE module = GetModuleHandle(0);
    TCHAR pFileName[MAX_PATH];
    GetModuleFileName(module, pFileName, MAX_PATH);
    CString csFullPath(pFileName);
    int nPos = csFullPath.ReverseFind(_T('\\'));
    if(nPos < 0)
        return CString("");
    else
        return csFullPath.Left(nPos);
}
