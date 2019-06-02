#include "StdAfx.h"
#include "Function.h"

Function::Function(void)
{
}

Function::~Function(void)
{
}
void Function::setLastError(CString lastErrInfo) {
	lastError = lastErrInfo;
}

CString Function::getLastError() {
	return lastError;
}

int Function::function(CString sFolderPath,CString dFolderPath)
{
	//Ŀ¼����
    Find finder;
    CStringArray fileNames;
    int find_err = finder.FindFold(sFolderPath, fileNames);
	setLastError(finder.getLastError());
    if(find_err == NO_FOLD) return 0;
	int fileNum=fileNames.GetSize();

	 //��ȡXml�ļ�
    XmlRead xmlread;
	CStringArray filterNames;
    CString xm = xmlread.GetWorkDir();
    int xml_err = xmlread.Read(xm + "\\filter.xml", filterNames);
	setLastError(xmlread.getLastError());
    if(xml_err == 0) return 0;

    //����
    Filter filter;
    int filenum = filter.filter(fileNames, filterNames);
	filenum=fileNames.GetSize();
	

    //���°汾
    int f_num = 0;
    int resultwarning1 = 0;
    int resultwarning2 = 0;

	while(filenum > f_num)
    {
		CString findfile = sFolderPath + "\\" + fileNames.GetAt(f_num);
        f_num++;
        Compare compare;
        CString new_filename;
		new_filename="";

        int compare_warning = compare.TimMax(findfile, new_filename);
		setLastError(compare.getLastError());
        if(compare_warning != SUCESS)
        {
            resultwarning1 = 1;
        }

		if(new_filename != "")
        {
            resultwarning2 = 1;
            CString newFullPath = findfile + "\\" + new_filename;
            //���� newFullPath �� dFolderPath
            Copy copy;
            CreateDirectory(dFolderPath + "\\" + fileNames.GetAt(f_num - 1), NULL);
            CString copyfoldto = _T("���ļ��С�" + newFullPath + "�����Ƶ��ˡ�"
                                    + dFolderPath + "\\" + fileNames.GetAt(f_num - 1) + "\\" + new_filename + "��");
            log.OutputLog(copyfoldto);
            int copy_err= copy.copyFold(newFullPath, dFolderPath + "\\" + fileNames.GetAt(f_num - 1) + "\\" + new_filename);
			setLastError(copy.getLastError());
			if(copy_err!=SUCESS)
				return 0;
        }
    }
	return 1;
}

