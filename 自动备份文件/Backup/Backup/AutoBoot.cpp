#include "StdAfx.h"
#include "AutoBoot.h"

AutoBoot::AutoBoot(void){}
AutoBoot::~AutoBoot(void){}

//设置程序开机启动  
BOOL AutoBoot::AutoBootSet(){  
    HKEY hKey;       
    //找到系统的启动项     
    CString lpRun = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");   
    //打开启动项Key     
    long lRet = RegOpenKeyEx(HKEY_CURRENT_USER, lpRun, 0, KEY_ALL_ACCESS, &hKey);     
    if(lRet == ERROR_SUCCESS){   
        TCHAR pFileName[MAX_PATH] = {0};     
        //得到程序自身的全路径     
        DWORD dwRet = GetModuleFileName(NULL, pFileName, MAX_PATH);   
        _tcscat(pFileName, _T(" -auto"));   
        //添加一个子Key,并设置值, 下面应用程序名字（不加后缀.exe）    
        lRet = RegSetValueEx(hKey, _T("AppName"), 0, REG_SZ, (LPBYTE)pFileName,  (lstrlen(pFileName) + 1)*sizeof(TCHAR));    
        //关闭注册表     
        RegCloseKey(hKey);        
        if(lRet != ERROR_SUCCESS){  
            return false;  
        }  
        return true;  
    }  
    return false;  
}  
  
  
//取消程序开机启动  
BOOL AutoBoot::AutoBootCancel(){  
    HKEY hKey;     
    //找到系统的启动项     
    CString lpRun = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");    
    long lRet = RegOpenKeyEx(HKEY_CURRENT_USER, lpRun, 0, KEY_ALL_ACCESS, &hKey);     
    if(lRet == ERROR_SUCCESS) {  
        RegDeleteValue(hKey, _T("AppName"));    
        //关闭注册表     
        RegCloseKey(hKey);  
        return true;    
    }  
    return false;  
}  
  
  
//判断程序是否开机自动启动  
BOOL AutoBoot::IsAutoBoot(){  
    LPWSTR *szArglist = NULL;  
    int nArgs = -1;  
    BOOL bRet = FALSE;  
    szArglist = CommandLineToArgvW(GetCommandLine(), &nArgs);  
    if((NULL == szArglist) || (nArgs == 2))  {  
        if (_tcsicmp(szArglist[1], _T("-auto")) == 0)
            bRet = TRUE;            //开机启动 
        else bRet = FALSE;
    }  
    else bRet = FALSE; 
    LocalFree(szArglist);   
    return bRet;  
}  