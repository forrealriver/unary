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
	CStringArray fileList;
	for (int i=0;i<filterNames.GetSize();i++)
	{
		for (int j=0;j<fileNames.GetSize();j++)
		{
			if (fileNames.GetAt(j)==filterNames.GetAt(i))
				fileNames.RemoveAt(j);
		}
	}
    return 1;
}
