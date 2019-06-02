#include "StdAfx.h"
#include "Find.h"
#include "stdafx.h"
#include "Fold_New.h"
#include "Fold_NewDlg.h"
Find::Find(void)
{
}

Find::~Find(void)
{
}
 int Find::FindFold(CString sFolderPath,CString* FileNames){
	int i=0;
	if (SetCurrentDirectory(sFolderPath) == TRUE)
	{
		CFileFind  finder;
		BOOL bWorking = finder.FindFile(_T("*.*"));
		
		while (bWorking)
		{
			bWorking = finder.FindNextFile();
			if (finder.IsDirectory() && finder.GetFileName() != "." &&  finder.GetFileName() != "..")
			{
				FileNames[i]=finder.GetFileName();
				i++;
			}
		}			
	}
	else AfxMessageBox(_T("原路径不存在，请重新输入！"));
	return i;
}