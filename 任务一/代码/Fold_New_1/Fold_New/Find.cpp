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
				//����ɸѡ
				FileNames[i]=finder.GetFileName();
				//AfxMessageBox(FileNames[i]);
				i++;
			}
		}			
	}
	else AfxMessageBox(_T("Ŀ��·�������ڣ����������룡"));
	CString s=_T("");
	s.Format(_T("%d"), i);
	AfxMessageBox(s);
	return i;
}