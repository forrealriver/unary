#include "StdAfx.h"
#include "Filter.h"

Filter::Filter(void)
{
}

Filter::~Filter(void)
{
}

/******************************************************************
��������filter
����˵������ԭ�ļ����µ�Ŀ¼�͹����ļ��е�Ŀ¼����ɸѡ
���룺fileNamesԭ�ļ���Ŀ¼ָ�룬fileNumԭ�ļ���Ŀ¼����
      filterNames�����ļ�Ŀ¼ָ�룬filterNum�����ļ�����
��������˺���ļ�����
*******************************************************************/
int Filter::filter(CStringArray &fileNames, CStringArray &filterNames)
{
	int filterNum=filterNames.GetSize();
    int filternum = 0;
    while(filterNum > filternum)
    {
		CString filterName = filterNames.GetAt(filternum);
		filternum++;
        for(int i = 0; i < fileNames.GetSize(); i++) {
			if(filterName == fileNames.GetAt(i)) {
				int j=0;
                for(j = i; j < fileNames.GetSize()-1; j++)
					fileNames.SetAt(j,fileNames.GetAt(j + 1));
				fileNames.RemoveAt(j);
				int f=fileNames.GetSize();
                break;
            }
        }
    }
    return 1;
}
