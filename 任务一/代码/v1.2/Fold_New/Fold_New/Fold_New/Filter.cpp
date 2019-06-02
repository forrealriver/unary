#include "StdAfx.h"
#include "Filter.h"

Filter::Filter(void)
{
}

Filter::~Filter(void)
{
}

/******************************************************************
函数名：filter
功能说明：把原文件夹下的目录和过滤文件中的目录进行筛选
输入：fileNames原文件夹目录指针，fileNum原文件夹目录数，
      filterNames过滤文件目录指针，filterNum过滤文件夹数
输出：过滤后的文件夹数
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
