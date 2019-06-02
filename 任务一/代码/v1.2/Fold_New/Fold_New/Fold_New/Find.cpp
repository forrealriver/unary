#include "StdAfx.h"
#include "Find.h"
#include "stdafx.h"
#include "Fold_New.h"
#include "Fold_NewDlg.h"
#include "Log.h"

#define	NOT_FOUND_FILE 1
#define NO_FOLD 2
#define SUCESS 0;

Find::Find(void)
{
}

Find::~Find(void)
{
}
void Find::setLastError(CString lastErrInfo) {
	lastError = lastErrInfo;
}

CString Find::getLastError() {
	return lastError;
}
/******************************************************************
��������FindFold
����˵�������ҳ�ԭ�ļ����е�ȫ��Ŀ¼
���룺sFolderPathԭ�ļ���Ŀ¼��ַ��FileNamesԭ�ļ����е�Ŀ¼ָ��
�����ԭ�ļ����е�Ŀ¼��
*******************************************************************/
int Find::FindFold(CString sFolderPath, CStringArray &FileNames)
{
	 Log log;
    int i = 0;
    if(PathIsDirectory(sFolderPath) == FALSE)
    {
		CString notfound = _T("�����󡿣�ԭ·����" + sFolderPath + "��������");
		setLastError(notfound);
		log.OutputLog(notfound);
		return NOT_FOUND_FILE;
    }

	CFileFind  finder;
	BOOL bWorking = finder.FindFile(sFolderPath+_T("\\*.*"));

	while(bWorking)
	{
		bWorking = finder.FindNextFile();
		if(finder.IsDirectory() && ! finder.IsDots())
		{
			FileNames.Add(finder.GetFileName());
			i++;
		}
	}
	finder.Close();

    if(i == 0)
    {
        CString null = _T("�����桿��ԭ·����" + sFolderPath + "��Ϊ���ļ��У�");
		setLastError(null);
        log.OutputLog(null);
		return NO_FOLD;
    }

    return SUCESS;
}

