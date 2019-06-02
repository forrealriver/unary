#include "StdAfx.h"
#include "Find.h"
#include "stdafx.h"
#include "Fold_New.h"
#include "Fold_NewDlg.h"
#include "Log.h"

Find::Find(void)
{
}

Find::~Find(void)
{
}
 int Find::FindFold(CString sFolderPath,CString* FileNames)
 {
	int i=0;
	if (SetCurrentDirectory(sFolderPath) == TRUE)
	{
		CFileFind  finder;
		BOOL bWorking = finder.FindFile(_T("*.*"));
		
		while (bWorking)
		{
			bWorking = finder.FindNextFile();
			if (finder.IsDirectory() && !finder.IsDots())
			{
				FileNames[i]=finder.GetFileName();
				i++;
			}
		}			
	}
	else 
	{
		AfxMessageBox(_T("原路径“"+sFolderPath+"”不存在，请重新输入！"));
		Log log;
		CString notfound=_T("【错误】：原路径“"+sFolderPath+"”不存在");
		log.OutputLog(notfound);
		return i;
	}
	if(i==0)
	{
		AfxMessageBox(_T("原路径“"+sFolderPath+"”为空目录！"));
		Log log;
		CString null=_T("【警告】：原路径“"+sFolderPath+"”为空目录！");
		log.OutputLog(null);
	}
	return i;
}