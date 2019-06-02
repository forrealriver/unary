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
��������copyFold
����˵������Դ�ļ����е��ļ����ļ��и��Ƶ�Ŀ���ļ�
���룺sourceԭ�ļ���·����targetĿ���ļ���·��
����������Ƿ���ִ���
*******************************************************************/
int Copy::copyFold(CString source, CString target)
{
    Log log;
    if(PathIsDirectory(source) == FALSE)
    {
		CString notfound=_T("ԭ·����" + source + "�������ڣ����������룡");
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
				CString CopyFileto = _T("�����󡿸����ļ���" + finder.GetFilePath() + "�����Ƶ���" + target + "\\" + finder.GetFileName() + "��");
				setLastError(CopyFileto);
				log.OutputLog(CopyFileto);
				return COPY_FAIL;
			}
			CString CopyFileto = _T("�ļ���" + finder.GetFilePath() + "�����Ƶ���" + target + "\\" + finder.GetFileName() + "��");
			log.OutputLog(CopyFileto);
		}
	}
	finder.Close();

    return COPY_SUCESS;
}
