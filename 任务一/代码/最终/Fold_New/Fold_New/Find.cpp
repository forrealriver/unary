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
��������FindFold
����˵�������ҳ�ԭ�ļ����е�ȫ��Ŀ¼
���룺sFolderPathԭ�ļ���Ŀ¼��ַ��FileNamesԭ�ļ����е�Ŀ¼ָ��
�����ԭ�ļ����е�Ŀ¼��
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
        AfxMessageBox(_T("ԭ·����" + sFolderPath + "�������ڣ����������룡"));
        Log log;
        CString notfound = _T("�����󡿣�ԭ·����" + sFolderPath + "��������");
        log.OutputLog(notfound);
        return i;
    }
    if(i == 0)
    {
        AfxMessageBox(_T("ԭ·����" + sFolderPath + "�������ļ��У�"));
        Log log;
        CString null = _T("�����桿��ԭ·����" + sFolderPath + "��Ϊ���ļ��У�");
        log.OutputLog(null);
    }
    return i;
}

