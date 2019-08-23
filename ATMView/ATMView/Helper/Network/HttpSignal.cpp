/***********************************************************************************
*								HttpSignal.cpp
*
* Copyright(C):	智慧眼科技股份有限公司
*
* Author:  YCL
*
* Date: 2019-06
*
* Description: 网络层应答信号
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
