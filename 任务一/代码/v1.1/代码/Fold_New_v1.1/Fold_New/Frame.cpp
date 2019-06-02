#include "StdAfx.h"
#include "Frame.h"

Frame::Frame(void)
{
}

Frame::~Frame(void)
{
}

/******************************************************************
函数名：BrowseForFolder
功能说明：浏览文件夹目录框
输入：void
输出：文件夹路径
*******************************************************************/
CString Frame::BrowseForFolder(void)
{
    BROWSEINFO sInfo;
    ::ZeroMemory(&sInfo, sizeof(BROWSEINFO));

    sInfo.pidlRoot = 0;
    sInfo.lpszTitle = _T("请选择一个文件夹：");
    sInfo.ulFlags = BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE | BIF_EDITBOX;
    sInfo.lpfn = NULL;

    LPITEMIDLIST lpidlBrowse = ::SHBrowseForFolder(&sInfo);
    TCHAR FolderPath[MAX_PATH] = {0};

    ::SHGetPathFromIDList(lpidlBrowse, FolderPath);

    return FolderPath;
}
