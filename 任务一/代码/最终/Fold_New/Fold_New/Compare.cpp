#include "stdafx.h"
#include "Compare.h"
#include "Log.h"

Compare::Compare()
{
}


Compare::~Compare()
{
}

/******************************************************************
��������TimMax
����˵�������ҳ����°汾Ŀ¼
���룺findflie ��Ҫ���ҵ�Ŀ¼��*new_filename���ҵ�������Ŀ¼
��������󾯸�1��2��3��4
*******************************************************************/
int Compare::TimMax(CString findflie, CString *new_filename)
{
    Log log ;
    int time_max = 0;
    CString name_max;

    int warning = 0;
    bool fullerror = true;
    if(SetCurrentDirectory(findflie) == TRUE)
    {
        CFileFind  finder;
        BOOL bWorking = finder.FindFile(_T("*.*"));

        while(bWorking)
        {
            bWorking = finder.FindNextFile();

            if(finder.IsDirectory() && !finder.IsDots())
            {
                CString name = finder.GetFileName();
                if(name.GetLength() < 8)
                {
                    warning = 2;

                    CString warning2 = _T("�����桿����" + findflie + "\\" + name + "���ļ������Ϸ���û��8λ�ַ���");
                    log.OutputLog(warning2);
                }
                else
                {
                    int j = 0;
                    for(j = 7; j >= 0; j--)
                        if(name.GetAt(j) < 0x30 || name.GetAt(j) > 0x39) break;
                    if(j > 0)
                    {
                        warning = 3;

                        CString warning3 = _T("�����桿����" + findflie + "\\" + name + "���ļ������Ϸ���ǰ8λ��ȫ�����֣�");
                        log.OutputLog(warning3);
                    }
                    else {
                        int time = _ttoi(finder.GetFileName().Mid(0, 8));
                        fullerror = false;
                        if(time > time_max)
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
        {
            warning = 4;

            CString warning4 = _T("�����桿����" + findflie + "����ȫ�������ļ��и�ʽ������ȷ");
            log.OutputLog(warning4);
        }
    }
    else
    {
        warning = 1;

        CString warning1 = _T("�����󡿣���" + findflie + "���ļ��в�����");
        log.OutputLog(warning1);
    }
    return warning;
}

/******************************************************************
��������Warning
����˵������ʾ��¼���ҳ����°汾ʱ���ֵĴ���
���룺warning ������ţ�findflie ���ҵ�Ŀ¼
�����void
*******************************************************************/
void Compare::Warning(int warning, CString findflie)
{
    switch(warning)
    {
    case 1:
        AfxMessageBox(_T("��" + findflie + "���ļ��в����ڣ�"));
        break;
    case 2:
        AfxMessageBox(_T("��" + findflie + "�� �д��ڸ�ʽ����ȷ�����ļ��У�û��8λ�ַ���,�뼰ʱ�޸ģ�"));
        break;
    case 3:
        AfxMessageBox(_T("��" + findflie + "�� �д��ڸ�ʽ����ȷ�����ļ��У�ǰ8λ��ȫ�����֣�,�뼰ʱ�޸ģ�"));
        break;
    case 4:
        AfxMessageBox(_T("��" + findflie + "�� ��ȫ�������ļ��и�ʽ������ȷ,�뼰ʱ�޸ģ�"));
        break;
    }
}
