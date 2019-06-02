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
				CString CopyFileto=_T("�ļ���"+finder.GetFilePath()+"�����Ƶ���"+target+"\\"+finder.GetFileName()+"��");
				log.OutputLog(CopyFileto);
			}
		}
	}
	else AfxMessageBox(_T("ԭ·����"+source+"�������ڣ����������룡"));
	return 0;
}
