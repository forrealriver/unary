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

/******************************************************************
函数名：FindFold
功能说明：查找出原文件夹中的全部目录
输入：sFolderPath原文件夹目录地址，FileNames原文件夹中的目录指针
输出：原文件夹中的目录数
*******************************************************************/
int Find::FindFold(CString sFolderPath, CStringArray *FileNames)
{
    int i = 0;
    if(SetCurrentDirectory(sFolderPath) == TRUE)
    {
        CFileFind  finder;
        BOOL bWorking = finder.FindFile(_T("*.*"));

        while(bWorking)
        {
            bWorking = finder.FindNextFile();
            if(finder.IsDirectory() && ! finder.IsDots())
            {
                FileNames[0].Add(finder.GetFileName());
                i++;
            }
        }
    }
    else
    {
        AfxMessageBox(_T("原路径“" + sFolderPath + "”不存在，请重新输入！"));
        Log log;
        CString notfound = _T("【错误】：原路径“" + sFolderPath + "”不存在");
        log.OutputLog(notfound);
        return i;
    }
    if(i == 0)
    {
        AfxMessageBox(_T("原路径“" + sFolderPath + "”中无文件夹！"));
        Log log;
        CString null = _T("【警告】：原路径“" + sFolderPath + "”为无文件夹！");
        log.OutputLog(null);
    }
    return i;
}

