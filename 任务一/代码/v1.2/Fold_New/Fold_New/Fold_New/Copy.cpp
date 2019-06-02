#include "StdAfx.h"
#include "Copy.h"
#include "Log.h"
#include "shlwapi.h"

#define	NOT_FOUND_FILE 1
#define COPY_FAIL 2
#define COPY_SUCESS 0
Copy::Copy(void)
{
}

Copy::~Copy(void)
{
}
void Copy::setLastError(CString lastErrInfo) {
	lastError = lastErrInfo;
}

CString Copy::getLastError() {
	return lastError;
}
/******************************************************************
函数名：copyFold
功能说明：把源文件夹中的文件和文件夹复制到目标文件
输入：source原文件夹路径，target目标文件夹路径
输出：复制是否出现错误
*******************************************************************/
int Copy::copyFold(CString source, CString target)
{
    Log log;
    if(PathIsDirectory(source) == FALSE)
    {
		CString notfound=_T("原路径“" + source + "”不存在，请重新输入！");
		setLastError(notfound);
		return NOT_FOUND_FILE;
    }
	if(!CreateDirectory(target, NULL))
	{
		DWORD dwError=GetLastError();
	}

	CFileFind  finder;
	BOOL bWorking = finder.FindFile(source+_T("\\*.*"));
	while(bWorking)
	{
		bWorking = finder.FindNextFile();
		if(finder.IsDirectory() && !finder.IsDots())
		{
			int copyerr=copyFold(finder.GetFilePath(), target + "\\" + finder.GetFileName());
			if(copyerr!=COPY_SUCESS)
				return copyerr;
		}
		else if(!finder.IsDots())
		{
			if( !PathFileExists(target + "\\" + finder.GetFileName()) &&!CopyFile(finder.GetFilePath(), target + "\\" + finder.GetFileName(), TRUE))
			{
				CString CopyFileto = _T("【错误】复制文件“" + finder.GetFilePath() + "”复制到“" + target + "\\" + finder.GetFileName() + "”");
				setLastError(CopyFileto);
				log.OutputLog(CopyFileto);
				return COPY_FAIL;
			}
			CString CopyFileto = _T("文件“" + finder.GetFilePath() + "”复制到“" + target + "\\" + finder.GetFileName() + "”");
			log.OutputLog(CopyFileto);
		}
	}
	finder.Close();

    return COPY_SUCESS;
}
