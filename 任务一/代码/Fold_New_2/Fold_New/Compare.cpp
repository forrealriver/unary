#include "stdafx.h"
#include "Compare.h"


Compare::Compare()
{
}


Compare::~Compare()
{
}
int Compare::TimMax(CString findflie, CString *new_filename) {
	int time_max = 0;
	CString name_max;
	int warning=0;
	if (SetCurrentDirectory(findflie) == TRUE)
	{
		CFileFind  finder;
		BOOL bWorking = finder.FindFile(_T("*.*"));
		while (bWorking)
		{
			bWorking = finder.FindNextFile();
			if (finder.IsDirectory() && finder.GetFileName() != "." &&  finder.GetFileName() != "..")
			{
				CString name = finder.GetFileName();
				if (name.GetLength() < 8)
					warning = 2;
				else {
					int j = 0;
					for (j = 7; j >= 0; j--)
						if (name.GetAt(j) < 0x30 || name.GetAt(j) > 0x39) break;
					if (j > 0)
						warning = 3;
					else {
						int time = _ttoi(finder.GetFileName().Mid(0, 8));
						if (time > time_max)
						{
							time_max = time;
							name_max = name;
						}
					}
				}
			}
		}
		new_filename[0] = name_max;
	}
	else warning=1;
	return warning;
}
void Compare::Warning(int warning, CString findflie) {
	switch (warning) {
	case 1:AfxMessageBox(_T("" + findflie + " 文件夹不存在！")); break;
	case 2:AfxMessageBox(_T("" + findflie + " 的子文件夹中有格式不正确的（没有8位字符）,请及时修改！")); break;
	case 3:AfxMessageBox(_T("" + findflie + " 的子文件夹中有格式不正确的（前8位不全是数字）,请及时修改！")); break;
	}
}