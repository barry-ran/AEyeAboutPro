/***********************************************************************************
*								AppCleaner.cpp
*
* Copyright(C):	北京智慧眼科技股份有限公司
*
* Author:  HJM,TZH
*
* Date: 2018-12
*
* Description: 用于进程退出时的一些清理操作
***********************************************************************************/
#include "AppCleaner.h"
#include "GlogManager.h"
#include "SystemChecker.h"

AppCleaner::AppCleaner(void)
{
}


AppCleaner::~AppCleaner(void)
{
}

void AppCleaner::clean()
{
    //系统退出时的一些清理操作
	shutdownLog();
	restoreSystemEnv();
}

void AppCleaner::shutdownLog()
{
    //关闭日志系统
	INSTANCE_GLOG_MANAGER->shutdownLog();
}

void AppCleaner::restoreSystemEnv()
{
	//恢复系统默认键盘进程
	if (SystemChecker::isSystemDefKeyBoardInstanceExisted())
	{
		SystemChecker::shutdownSystemDefKeyBoardInstance();
	}
}
