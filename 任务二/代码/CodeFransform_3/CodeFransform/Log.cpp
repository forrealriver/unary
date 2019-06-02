#include "StdAfx.h"
#include "Log.h"
#include "locale"
Log::Log(void)
{
}

Log::~Log(void)
{
}
void Log::setLastError(CString lastErrInfo) {
	lastError = lastErrInfo;
}

CString Log::getLastError() {
	return lastError;
}
/******************************************************************
��������OutputLog
����˵�����������־�ļ�
���룺��¼������
�����void
*******************************************************************/
void Log::OutputLog(CString msg)
{
    try
    {
        CString lg = browse.GetWorkFold();
        lg += "\\CodeFransform.log";

        CStdioFile outFile;
        CFileException pError;

        setlocale(LC_CTYPE, ("chs"));

        if(!outFile.Open(lg, CFile::modeNoTruncate | CFile::modeCreate
                         | CFile::modeWrite | CFile::typeText, &pError))
        {
			Log log;
			setLastError(_T("��־�ļ��򿪴���"));
			log.OutputLog(_T("��־�ļ��򿪴���"));
            return;
        }
        CString msLine;

        CTime tt = CTime::GetCurrentTime();
        msLine = tt.Format("[%Y-%m-%d %A, %H:%M:%S] ") + msg;
        msLine += "\n";

        outFile.SeekToEnd();
        outFile.WriteString(msLine);
        outFile.Close();
    }
    catch(CFileException *fx)
    {
        fx->Delete();
    }
}
