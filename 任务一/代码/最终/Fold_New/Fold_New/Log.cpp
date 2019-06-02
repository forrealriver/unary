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
        XmlRead xmlread;
        CString xm = xmlread.GetWorkDir();
        int xmLength = xm.GetLength();
		int find=xm.Find(_T("Debug"));
		int find2=xm.Find(_T("Release"));

		if(find>0)
			xm = xm.Mid(0, xmLength - 6);
		else if(find2>0)
			xm = xm.Mid(0, xmLength - 8);
        xm += "\\Log\\Fold_New.log";

        CStdioFile outFile;
        CFileException pError;

        setlocale(LC_CTYPE, ("chs"));

        if(!outFile.Open(xm, CFile::modeNoTruncate | CFile::modeCreate
                         | CFile::modeWrite | CFile::typeText, &pError))
        {
            AfxMessageBox(_T("��־�ļ��򿪴���"));
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
