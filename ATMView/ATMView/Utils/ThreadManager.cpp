/***********************************************************************************
*								ThreadManager.cpp
*
* Copyright(C):	智慧眼科技股份有限公司
*
* Author:  YCL
*
* Date: 2019-06
*
* Description: 通用线程启动实例
***********************************************************************************/

#include "ThreadManager.h"

QThread* ThreadManager::m_pAgentThread = NULL;

QThread* ThreadManager::getAgentThread()
{
	if (m_pAgentThread == NULL)
	{
		m_pAgentThread = new QThread;
	}
	return m_pAgentThread;
}
