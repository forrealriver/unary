#include "StdAfx.h"
#include "AutoBoot.h"

AutoBoot::AutoBoot(void){}
AutoBoot::~AutoBoot(void){}

//���ó��򿪻�����  
BOOL AutoBoot::AutoBootSet(){  
    HKEY hKey;       
    //�ҵ�ϵͳ��������     
    CString lpRun = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");   
    //��������Key     
    long lRet = RegOpenKeyEx(HKEY_CURRENT_USER, lpRun, 0, KEY_ALL_ACCESS, &hKey);     
    if(lRet == ERROR_SUCCESS){   
        TCHAR pFileName[MAX_PATH] = {0};     
        //�õ����������ȫ·��     
        DWORD dwRet = GetModuleFileName(NULL, pFileName, MAX_PATH);   
        _tcscat(pFileName, _T(" -auto"));   
        //���һ����Key,������ֵ, ����Ӧ�ó������֣����Ӻ�׺.exe��    
        lRet = RegSetValueEx(hKey, _T("AppName"), 0, REG_SZ, (LPBYTE)pFileName,  (lstrlen(pFileName) + 1)*sizeof(TCHAR));    
        //�ر�ע���     
        RegCloseKey(hKey);        
        if(lRet != ERROR_SUCCESS){  
            return false;  
        }  
        return true;  
    }  
    return false;  
}  
  
  
//ȡ�����򿪻�����  
BOOL AutoBoot::AutoBootCancel(){  
    HKEY hKey;     
    //�ҵ�ϵͳ��������     
    CString lpRun = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");    
    long lRet = RegOpenKeyEx(HKEY_CURRENT_USER, lpRun, 0, KEY_ALL_ACCESS, &hKey);     
    if(lRet == ERROR_SUCCESS) {  
        RegDeleteValue(hKey, _T("AppName"));    
        //�ر�ע���     
        RegCloseKey(hKey);  
        return true;    
    }  
    return false;  
}  
  
  
//�жϳ����Ƿ񿪻��Զ�����  
BOOL AutoBoot::IsAutoBoot(){  
    LPWSTR *szArglist = NULL;  
    int nArgs = -1;  
    BOOL bRet = FALSE;  
    szArglist = CommandLineToArgvW(GetCommandLine(), &nArgs);  
    if((NULL == szArglist) || (nArgs == 2))  {  
        if (_tcsicmp(szArglist[1], _T("-auto")) == 0)
            bRet = TRUE;            //�������� 
        else bRet = FALSE;
    }  
    else bRet = FALSE; 
    LocalFree(szArglist);   
    return bRet;  
}  