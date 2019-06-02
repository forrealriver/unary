#include "StdAfx.h"
#include "Copy.h"
#include "Log.h"
Copy::Copy(void)
{
}

Copy::~Copy(void)
{
}

/******************************************************************
函数名：copyFold
功能说明：把源文件夹中的文件和文件夹复制到目标文件
输入：source原文件夹路径，target目标文件夹路径
输出：复制是否出现错误
*******************************************************************/
int Copy::copyFold(CString source,CString target)
{
	Log log;
	if (SetCurrentDirectory(source) == TRUE)
	{
		CreateDirectory(target,NULL);  
		CFileFind  finder;
		BOOL bWorking = finder.FindFile(_T("*.*"));
		while (bWorking)
		{
			bWorking = finder.FindNextFile();
			if (finder.IsDirectory() && !finder.IsDots())
			{
				copyFold(finder.GetFilePath(),target+"\\"+finder.GetFileName()); 
			}
			else if(!finder.IsDots())
			{
				CopyFile(finder.GetFilePath(),target+"\\"+finder.GetFileName(),FALSE); 
				CString CopyFileto=_T("文件“"+finder.GetFilePath()+"”复制到“"+target+"\\"+finder.GetFileName()+"”");
				log.OutputLog(CopyFileto);
			}
		}
	}
	else 
	{
		AfxMessageBox(_T("原路径“"+source+"”不存在，请重新输入！"));
		return 1;
	}
	return 0;
}
