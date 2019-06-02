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
