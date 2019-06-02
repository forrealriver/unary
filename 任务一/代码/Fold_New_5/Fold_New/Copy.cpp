#include "StdAfx.h"
#include "Copy.h"
#include "Log.h"
Copy::Copy(void)
{
}

Copy::~Copy(void)
{
}
int Copy::copyFold(CString source,CString target){
	Log log;
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
			else if(!finder.IsDots())
			{
				CopyFile(finder.GetFilePath(),target+"\\"+finder.GetFileName(),FALSE); 
				CString CopyFileto=_T("文件“"+finder.GetFilePath()+"”复制到“"+target+"\\"+finder.GetFileName()+"”");
				log.OutputLog(CopyFileto);
			}
		}
	}
	else AfxMessageBox(_T("原路径“"+source+"”不存在，请重新输入！"));
	return 0;
}
