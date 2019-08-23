/***********************************************************************************
*								AppCleaner.cpp
*
* Copyright(C):	�����ǻ��ۿƼ��ɷ����޹�˾
*
* Author:  HJM,TZH
*
* Date: 2018-12
*
* Description: ���ڽ����˳�ʱ��һЩ�������
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
    //ϵͳ�˳�ʱ��һЩ�������
	shutdownLog();
	restoreSystemEnv();
}

void AppCleaner::shutdownLog()
{
    //�ر���־ϵͳ
	INSTANCE_GLOG_MANAGER->shutdownLog();
}

void AppCleaner::restoreSystemEnv()
{
	//�ָ�ϵͳĬ�ϼ��̽���
	if (SystemChecker::isSystemDefKeyBoardInstanceExisted())
	{
		SystemChecker::shutdownSystemDefKeyBoardInstance();
	}
}
