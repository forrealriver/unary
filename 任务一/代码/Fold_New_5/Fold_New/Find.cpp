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
		AfxMessageBox(_T("ԭ·����"+sFolderPath+"�������ڣ����������룡"));
		Log log;
		CString notfound=_T("�����󡿣�ԭ·����"+sFolderPath+"��������");
		log.OutputLog(notfound);
		return i;
	}
	if(i==0)
	{
		AfxMessageBox(_T("ԭ·����"+sFolderPath+"��Ϊ��Ŀ¼��"));
		Log log;
		CString null=_T("�����桿��ԭ·����"+sFolderPath+"��Ϊ��Ŀ¼��");
		log.OutputLog(null);
	}
	return i;
}