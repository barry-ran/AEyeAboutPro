/***********************************************************************************
*								ThreadManager.cpp
*
* Copyright(C):	�ǻ��ۿƼ��ɷ����޹�˾
*
* Author:  YCL
*
* Date: 2019-06
*
* Description: ͨ���߳�����ʵ��
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
