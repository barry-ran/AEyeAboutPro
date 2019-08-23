/***********************************************************************************
*								AppEnvChecker.cpp
*
* Copyright(C):	北京智慧眼科技股份有限公司
*
* Author:  HJM,TZH
*
* Date: 2018-12
*
* Description: 用于应用程序环境检测，判断进程是否已经存在；
***********************************************************************************/
#include "AppEnvChecker.h"
#include "DataPathManager.h"
#include "SystemChecker.h"
#include <QtWidgets/QMessageBox>

AppEnvChecker::AppEnvChecker(void)
{
}


AppEnvChecker::~AppEnvChecker(void)
{
}

bool AppEnvChecker::check()
{
    return !isAppInstanceExisted();
}

bool AppEnvChecker::isAppInstanceExisted()
{
    //检测进程是否存在
	if (SystemChecker::isAppInstanceExisted()) {
        return true;
    }

    return false;
}
