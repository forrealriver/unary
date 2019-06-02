#include "StdAfx.h"
#include "Log.h"
#include "XmlRead.h"
#include "locale"
Log::Log(void)
{
}

Log::~Log(void)
{
}
void Log::OutputLog(CString msg)
{
	try
    {
		XmlRead xmlread;
		CString xm=xmlread.GetWorkDir();
		int logLength=xm.GetLength();
		xm=xm.Mid(0,logLength-6);
		xm+="\\Fold_New\\Log\\Fold_New.log";
        CStdioFile outFile;
		CFileException pError;
		setlocale( LC_CTYPE, ("chs")); 
		if(!outFile.Open(xm, CFile::modeNoTruncate | CFile::modeCreate 
			| CFile::modeWrite | CFile::typeText,&pError))
		{
			AfxMessageBox(_T("日志文件打开错误！"));
			return;
		}
        CString msLine;
        CTime tt = CTime::GetCurrentTime();
        msLine = tt.Format("[%Y-%B-%d %A, %H:%M:%S] ") + msg;
        msLine += "\n";
        outFile.SeekToEnd();
        outFile.WriteString( msLine );
        outFile.Close();
    }
    catch(CFileException *fx)
    {
        fx->Delete();
    }
}
