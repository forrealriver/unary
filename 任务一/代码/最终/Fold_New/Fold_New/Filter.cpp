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
int Filter::filter(CStringArray *fileNames, int fileNum, CStringArray *filterNames, int filterNum)
{
    int filternum = 0;
    int filenum = fileNum;
    while(filterNum > filternum)
    {
		CString filterName = filterNames[0].GetAt(filternum);
        filternum ++;

        for(int i = 0; i < filenum; i++) {
			if(filterName == fileNames[0].GetAt(i)) {

                filenum--;

                for(int j = i; j < filenum; j++)
					fileNames[0].SetAt(j,fileNames[0].GetAt(j + 1));

                break;
            }
        }
    }
    return filenum;
}
