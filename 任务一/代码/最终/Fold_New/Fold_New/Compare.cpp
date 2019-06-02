#include "stdafx.h"
#include "Compare.h"
#include "Log.h"

Compare::Compare()
{
}


Compare::~Compare()
{
}

/******************************************************************
函数名：TimMax
功能说明：查找出最新版本目录
输入：findflie 需要查找的目录，*new_filename查找到的最新目录
输出：错误警告1、2、3、4
*******************************************************************/
int Compare::TimMax(CString findflie, CString *new_filename)
{
    Log log ;
    int time_max = 0;
    CString name_max;

    int warning = 0;
    bool fullerror = true;
    if(SetCurrentDirectory(findflie) == TRUE)
    {
        CFileFind  finder;
        BOOL bWorking = finder.FindFile(_T("*.*"));

        while(bWorking)
        {
            bWorking = finder.FindNextFile();

            if(finder.IsDirectory() && !finder.IsDots())
            {
                CString name = finder.GetFileName();
                if(name.GetLength() < 8)
                {
                    warning = 2;

                    CString warning2 = _T("【警告】：“" + findflie + "\\" + name + "”文件名不合法（没有8位字符）");
                    log.OutputLog(warning2);
                }
                else
                {
                    int j = 0;
                    for(j = 7; j >= 0; j--)
                        if(name.GetAt(j) < 0x30 || name.GetAt(j) > 0x39) break;
                    if(j > 0)
                    {
                        warning = 3;

                        CString warning3 = _T("【警告】：“" + findflie + "\\" + name + "”文件名不合法（前8位不全是数字）");
                        log.OutputLog(warning3);
                    }
                    else {
                        int time = _ttoi(finder.GetFileName().Mid(0, 8));
                        fullerror = false;
                        if(time > time_max)
                        {
                            time_max = time;
                            name_max = name;
                        }
                    }
                }
            }
        }

        new_filename[0] = name_max;

        if(fullerror)
        {
            warning = 4;

            CString warning4 = _T("【警告】：“" + findflie + "”中全部的子文件夹格式都不正确");
            log.OutputLog(warning4);
        }
    }
    else
    {
        warning = 1;

        CString warning1 = _T("【错误】：“" + findflie + "”文件夹不存在");
        log.OutputLog(warning1);
    }
    return warning;
}

/******************************************************************
函数名：Warning
功能说明：显示记录查找出最新版本时出现的错误
输入：warning 错误序号，findflie 查找的目录
输出：void
*******************************************************************/
void Compare::Warning(int warning, CString findflie)
{
    switch(warning)
    {
    case 1:
        AfxMessageBox(_T("“" + findflie + "”文件夹不存在！"));
        break;
    case 2:
        AfxMessageBox(_T("“" + findflie + "” 中存在格式不正确的子文件夹（没有8位字符）,请及时修改！"));
        break;
    case 3:
        AfxMessageBox(_T("“" + findflie + "” 中存在格式不正确的子文件夹（前8位不全是数字）,请及时修改！"));
        break;
    case 4:
        AfxMessageBox(_T("“" + findflie + "” 中全部的子文件夹格式都不正确,请及时修改！"));
        break;
    }
}
