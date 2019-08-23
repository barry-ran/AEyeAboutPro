/***********************************************************************************
*								DataPathManager.cpp
*
* Copyright(C):	北京智慧眼科技股份有限公司
*
* Author:  HJM,TZH
*
* Date: 2018-12
*
* Description: 进程目录管理器实现
***********************************************************************************/
#include <Windows.h>
#include <ShlObj.h>
#include "DataPathManager.h"

string DataPathManager::getUserDir()
{
    //获取应用程序数据文件存放目录
	char personalPath[MAX_PATH] = {0};
    setlocale(LC_ALL, "chs");
    bool bRet = SHGetSpecialFolderPathA(NULL, personalPath, CSIDL_PERSONAL, FALSE);

    string dir = personalPath;
    string userDir = dir + "\\AthenaEye\\ATMView";
    ::CreateDirectoryA(userDir.c_str(),NULL);

    return userDir;
}

string DataPathManager::getDevicePath()
{
    //获取device文件目录
	return getUserDir() + "\\device";
}

string DataPathManager::getLogDirPath()
{
    //获取日志文件目录
	return getUserDir() + "\\Log";
}

string DataPathManager::getImagesDirPath()
{
    //获取images文件夹目录
	return getUserDir() + "\\Images";
}

string DataPathManager::getPdfDirPath()
{
    //获取pdf文件存放路径
	return getUserDir() + "\\Pdf";
}

string DataPathManager::getAEyeDir()
{
	//获取AthenaEye目录
	char personalPath[MAX_PATH] = {0};
	setlocale(LC_ALL, "chs");
	bool bRet = SHGetSpecialFolderPathA(NULL, personalPath, CSIDL_PERSONAL, FALSE);

	string dir = personalPath;
	string aeyeDir = dir + "\\AthenaEye";

	return aeyeDir;
}

string DataPathManager::getDumpDirPath()
{
	//获取Dump文件存放目录
    return getUserDir() + "\\Dump";
}
