/***********************************************************************************
*								HttpSignal.cpp
*
* Copyright(C):	�ǻ��ۿƼ��ɷ����޹�˾
*
* Author:  YCL
*
* Date: 2019-06
*
* Description: �����Ӧ���ź�
***********************************************************************************/

#include "HttpSignal.h"

HttpSignal* HttpSignal::m_pInstance = NULL;

HttpSignal::HttpSignal(QObject *parent)
	: QObject(parent)
{

}

HttpSignal::~HttpSignal()
{

}

HttpSignal* HttpSignal::instance()
{
	if (m_pInstance == NULL)
	{
		m_pInstance = new HttpSignal;
	}
	return m_pInstance;
}
