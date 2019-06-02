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
函数名：FindFold
功能说明：查找出原文件夹中的全部目录
输入：sFolderPath原文件夹目录地址，FileNames原文件夹中的目录指针
输出：原文件夹中的目录数
*******************************************************************/
int Find::FindFold(CString sFolderPath, CStringArray &FileNames)
{
	 Log log;
    int i = 0;
    if(PathIsDirectory(sFolderPath) == FALSE)
    {
		CString notfound = _T("【错误】：原路径“" + sFolderPath + "”不存在");
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
        CString null = _T("【警告】：原路径“" + sFolderPath + "”为无文件夹！");
		setLastError(null);
        log.OutputLog(null);
		return NO_FOLD;
    }

    return SUCESS;
}

