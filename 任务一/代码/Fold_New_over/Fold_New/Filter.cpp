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
int Filter::filter(CString* fileNames, int fileNum, CString* filterNames, int filterNum) 
{
	int filternum = 0;
	int filenum = fileNum;
	while (filterNum > filternum) 
	{
		CString filterName = filterNames[filternum];
		filternum++;
		for (int i = 0; i < filenum; i++) {
			if (filterName == fileNames[i]) {
				filenum--;
				for (int j = i; j < filenum; j++)
					fileNames[j] = fileNames[j + 1];
				break;
			}
		}
	}
	return filenum;
}
