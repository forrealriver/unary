#include "StdAfx.h"
#include "Frame.h"

Frame::Frame(void)
{
}

Frame::~Frame(void)
{
}
//�ļ��������
CString Frame::BrowseForFolder(void){
	BROWSEINFO sInfo;  
    ::ZeroMemory(&sInfo, sizeof(BROWSEINFO));  
    sInfo.pidlRoot   = 0;  
    sInfo.lpszTitle   = _T("��ѡ��һ���ļ��У�");  
    sInfo.ulFlags   = BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE | BIF_EDITBOX;  
    sInfo.lpfn     = NULL;  
	LPITEMIDLIST lpidlBrowse = ::SHBrowseForFolder(&sInfo);  
	TCHAR FolderPath[MAX_PATH] = {0}; 
	::SHGetPathFromIDList(lpidlBrowse,FolderPath);
	return FolderPath;
}