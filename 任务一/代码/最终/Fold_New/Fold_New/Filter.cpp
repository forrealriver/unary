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
