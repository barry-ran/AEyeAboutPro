/***********************************************************************************
*								DataPathManager.cpp
*
* Copyright(C):	�����ǻ��ۿƼ��ɷ����޹�˾
*
* Author:  HJM,TZH
*
* Date: 2018-12
*
* Description: ����Ŀ¼������ʵ��
***********************************************************************************/
#include <Windows.h>
#include <ShlObj.h>
#include "DataPathManager.h"

string DataPathManager::getUserDir()
{
    //��ȡӦ�ó��������ļ����Ŀ¼
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
    //��ȡdevice�ļ�Ŀ¼
	return getUserDir() + "\\device";
}

string DataPathManager::getLogDirPath()
{
    //��ȡ��־�ļ�Ŀ¼
	return getUserDir() + "\\Log";
}

string DataPathManager::getImagesDirPath()
{
    //��ȡimages�ļ���Ŀ¼
	return getUserDir() + "\\Images";
}

string DataPathManager::getPdfDirPath()
{
    //��ȡpdf�ļ����·��
	return getUserDir() + "\\Pdf";
}

string DataPathManager::getAEyeDir()
{
	//��ȡAthenaEyeĿ¼
	char personalPath[MAX_PATH] = {0};
	setlocale(LC_ALL, "chs");
	bool bRet = SHGetSpecialFolderPathA(NULL, personalPath, CSIDL_PERSONAL, FALSE);

	string dir = personalPath;
	string aeyeDir = dir + "\\AthenaEye";

	return aeyeDir;
}

string DataPathManager::getDumpDirPath()
{
	//��ȡDump�ļ����Ŀ¼
    return getUserDir() + "\\Dump";
}
