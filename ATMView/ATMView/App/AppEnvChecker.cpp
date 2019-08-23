/***********************************************************************************
*								AppEnvChecker.cpp
*
* Copyright(C):	�����ǻ��ۿƼ��ɷ����޹�˾
*
* Author:  HJM,TZH
*
* Date: 2018-12
*
* Description: ����Ӧ�ó��򻷾���⣬�жϽ����Ƿ��Ѿ����ڣ�
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
    //�������Ƿ����
	if (SystemChecker::isAppInstanceExisted()) {
        return true;
    }

    return false;
}
