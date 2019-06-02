#include "stdafx.h"
#include "Compare.h"
#include "Log.h"

#define FILE_NAME_WRONGFUL_NOTENOUGH8 2
#define FILE_NAME_WRONGFUL_NOTALLNUM 3
#define FOLD_ALL_WRONGFUL 4
#define	NOT_FOUND_FILE 1
Compare::Compare()
{
}


Compare::~Compare()
{
}
void Compare::setLastError(CString lastErrInfo) {
	lastError = lastErrInfo;
}

CString Compare::getLastError() {
	return lastError;
}
/******************************************************************
函数名：TimMax
功能说明：查找出最新版本目录
输入：findflie 需要查找的目录，*new_filename查找到的最新目录
输出：错误警告1、2、3、4
*******************************************************************/
int Compare::TimMax(CString findflie, CString &new_filename)
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
                    warning = FILE_NAME_WRONGFUL_NOTENOUGH8;
                    CString fileNameWrongNO8 = _T("【警告】：“" + findflie + "\\" + name + "”文件名不合法（没有8位字符）");
					setLastError(fileNameWrongNO8);
                    log.OutputLog(fileNameWrongNO8);
                }
                else
                {
                    int j = 0;
                    for(j = 7; j >= 0; j--)
                        if(name.GetAt(j) < 0x30 || name.GetAt(j) > 0x39) break;
                    if(j > 0)
                    {
                        warning = FILE_NAME_WRONGFUL_NOTALLNUM;
                        CString fileNameNotNum = _T("【警告】：“" + findflie + "\\" + name + "”文件名不合法（前8位不全是数字）");
                        setLastError(fileNameNotNum);
						log.OutputLog(fileNameNotNum);
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
		finder.Close();
        new_filename = name_max;

        if(fullerror)
        {
            warning =FOLD_ALL_WRONGFUL;
            CString foldAllWrongful = _T("【警告】：“" + findflie + "”中全部的子文件夹格式都不正确");
            setLastError(foldAllWrongful);
			log.OutputLog(foldAllWrongful);
        }
    }
    else
    {
        warning = NOT_FOUND_FILE;
        CString notFoundFold = _T("【错误】：“" + findflie + "”文件夹不存在");
		setLastError(notFoundFold);
        log.OutputLog(notFoundFold);
    }
    return warning;
}