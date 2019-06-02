#include "StdAfx.h"
#include "SourceLog.h"
#include "Log.h"
#include "locale"
SourceLog::SourceLog(void)
{
}

SourceLog::~SourceLog(void)
{
}
void SourceLog::OutputLog(CString msg) {
	try {
		CString lg = m_browse.GetWorkFold();
		lg += "\\SourceLog.txt";
		DeleteFile(lg);	
		CStdioFile outFile;
		CFileException pError;

		setlocale(LC_CTYPE, ("chs"));

		if (!outFile.Open(lg, CFile::modeNoTruncate | CFile::modeCreate
			| CFile::modeWrite | CFile::typeText, &pError)) {
				Log log;
				log.OutputLog(_T("TargetLog日志文件打开错误"));
				return;
		}
		outFile.SeekToEnd();
		outFile.WriteString(msg);
		outFile.Close();
	}
	catch (CFileException *fx) {
		fx->Delete();
	}
}
CString SourceLog::ReadPath(){
	CString lg = m_browse.GetWorkFold();
	lg += "\\SourceLog.txt";
	CStdioFile m_file;  
	CString contents; 
	if (m_file.Open(lg, CFile::typeText | CFile::modeRead)){
		char * pOldLocale = _strdup(setlocale(LC_CTYPE, NULL));
		setlocale(LC_CTYPE, "chs");
		m_file.ReadString(contents);
		setlocale(LC_CTYPE, pOldLocale);
		free(pOldLocale);
	}
	return contents;
}


