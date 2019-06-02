#include "StdAfx.h"
#include "Copy.h"

Copy::Copy(void)
{
}

Copy::~Copy(void)
{
}
int Copy::copyFold(CString source,CString target){
	if (SetCurrentDirectory(source) == TRUE){
		CreateDirectory(target,NULL);  
		CFileFind  finder;
		BOOL bWorking = finder.FindFile(_T("*.*"));
		while (bWorking)
		{
			bWorking = finder.FindNextFile();
			if (finder.IsDirectory() && !finder.IsDots())
			{
				copyFold(finder.GetFilePath(),target+"\\"+finder.GetFileName()); 
			}
			else CopyFile(finder.GetFilePath(),target+"\\"+finder.GetFileName(),FALSE);  
		}
	}
	else AfxMessageBox(_T("原路径“"+source+"”不存在，请重新输入！"));
	return 0;
}
