#include "StdAfx.h"
#include "Find.h"
#include "XmlRead.h"
Find::Find(CString sourc, CString targe){
	flage=FALSE;
	source=sourc;
	target=targe;
	m_endflage=0;
	m_ThreadHandle=NULL;
	InitializeCriticalSection(&m_cs);
}

Find::~Find(void){
	m_ThreadHandle=NULL;
}
DWORD WINAPI Find::TreadProcess(LPVOID lpParam) {
	Find *find = (Find*)lpParam;
	int x = find->findFile();
	return x;
}
int Find::findFile(){
	if(!SetCurrentDirectory(source))
		return 0;
	XmlRead xmlread;
	CStringArray filterNames;
	CString xm = xmlread.GetWorkDir();
	int xml_err = xmlread.Read(xm + "\\filter.xml", filterNames);
	if(xml_err == 0){
		log.OutputLog(_T("【错误】调用Xmlread.Read"));
		return 0;
	}
	while (TRUE)
	{
		EnterCriticalSection(&m_cs);
		if (m_endflage == 1)
			break;
		LeaveCriticalSection(&m_cs);
		CFileFind  finder;
		BOOL bWorking = finder.FindFile(_T("*.*"));
		while(bWorking){
			EnterCriticalSection(&m_cs);
			if (m_endflage == 1)
				break;
			LeaveCriticalSection(&m_cs);
			bWorking = finder.FindNextFile();
			if(!finder.IsDirectory() && !finder.IsDots()){
				CString x=finder.GetFilePath();
				CString suffix=x.Right(x.GetLength()-x.ReverseFind('.')-1);
				CString nna=finder.GetFileName();
				nna=nna.Left(nna.ReverseFind('.'));
				suffix.MakeLower();
				int j=0;
				for (j=0;j<filterNames.GetSize();j++){
					if(filterNames.GetAt(j) == suffix)
						break;
				}
				if (j != filterNames.GetSize())
					continue;

				if (!flage){
					name.Add(finder.GetFileName());
					time.Add(newtime.newTime(finder.GetFilePath()));
				}
				else{
					CString na=finder.GetFileName();
					int i=0;
					for (i=0;i<name.GetSize();i++){
						if (name.GetAt(i)==na){
							if(newtime.newTime(finder.GetFilePath()) != time.GetAt(i) && newtime.sizefile(finder.GetFilePath())>0){
								CString count;
								int xm=0;
								count.Format(_T("000%d"),xm);
								while(PathFileExists(target + "\\" + nna+"["+count+"]."+suffix)){
									xm++;
									if (xm<10)
										count.Format(_T("000%d"),xm);
									else if (xm<100)
										count.Format(_T("00%d"),xm);
									else if (xm<1000)
										count.Format(_T("0%d"),xm);
									else if (xm<10000)
										count.Format(_T("%d"),xm);
								}
								if(!CopyFile(finder.GetFilePath(), target + "\\" + nna+"["+count+"]."+suffix, FALSE)){
									CString CopyFileto = _T("【错误】：文件“" + finder.GetFilePath() + "”复制到“"+nna+"["+count+"]."+suffix+"”");
									log.OutputLog(CopyFileto);
								}
								else{
									CString CopyFileto = _T("文件“" + finder.GetFilePath() + "”复制到“"+nna+"["+count+"]."+suffix+"”");
									log.OutputLog(CopyFileto);
								}
								time.SetAt(i,newtime.newTime(finder.GetFilePath()));
							}
							break;
						}
					}
					if (i==name.GetSize() && newtime.sizefile(finder.GetFilePath())>0){
						name.Add(na);
						time.Add(newtime.newTime(finder.GetFilePath()));
						CString count;
						int xm=0;
						count.Format(_T("000%d"),xm);
						while(PathFileExists(target + "\\" + nna+"["+count+"]."+suffix)){
							xm++;
							if (xm<10)
								count.Format(_T("000%d"),xm);
							else if (xm<100)
								count.Format(_T("00%d"),xm);
							else if (xm<1000)
								count.Format(_T("0%d"),xm);
							else if (xm<10000)
								count.Format(_T("%d"),xm);
							else break;
						}
						if(!CopyFile(finder.GetFilePath(), target + "\\" + nna+"["+count+"]."+suffix, FALSE)){
							CString CopyFileto = _T("【错误】：文件“" + finder.GetFilePath() + "”复制到“"+nna+"["+count+"]."+suffix+"”");
							log.OutputLog(CopyFileto);
						}
						else{
							CString CopyFileto = _T("文件“" + finder.GetFilePath() + "”复制到“"+nna+"["+count+"]."+suffix+"”");
							log.OutputLog(CopyFileto);
						}
					}
				}
			}
		}
		flage=TRUE;
		Sleep(300);
	}
	return 1;
}