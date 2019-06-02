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
