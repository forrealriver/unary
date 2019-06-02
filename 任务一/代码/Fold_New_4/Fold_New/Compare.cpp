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
	bool fullerror=true;
	if (SetCurrentDirectory(findflie) == TRUE)
	{
		CFileFind  finder;
		BOOL bWorking = finder.FindFile(_T("*.*"));
		while (bWorking)
		{
			bWorking = finder.FindNextFile();
			if (finder.IsDirectory() && !finder.IsDots())
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
						fullerror=false;
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
		if(fullerror) 
			warning = 4;
	}
	else warning=1;
	return warning;
}
void Compare::Warning(int warning, CString findflie) {
	switch (warning) {
		case 1:AfxMessageBox(_T("��" + findflie + "���ļ��в����ڣ�")); break;
		case 2:AfxMessageBox(_T("��" + findflie + "�� �����ļ����д��ڸ�ʽ����ȷ�ģ�û��8λ�ַ���,�뼰ʱ�޸ģ�")); break;
		case 3:AfxMessageBox(_T("��" + findflie + "�� �����ļ����д��ڸ�ʽ����ȷ�ģ�ǰ8λ��ȫ�����֣�,�뼰ʱ�޸ģ�")); break;
		case 4:AfxMessageBox(_T("��" + findflie + "�� �����ļ�����ȫ���ĸ�ʽ������ȷ,�뼰ʱ�޸ģ�")); break;
	}
}