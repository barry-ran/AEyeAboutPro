/***********************************************************************************
*								HttpClient.cpp
*
* Copyright(C):	智慧眼科技股份有限公司
*
* Author:  YCL
*
* Date: 2019-06
*
* Description: 网络分发层实例
***********************************************************************************/

#include "HttpClient.h"
#include "HttpOperatorLogin.h"
#include "HttpGetBaseInfo.h"
#include "HttpGetIdCardPic.h"
#include "HttpIfCanIdentify.h"
#include "HttpBackendRecognize.h"
#include "HttpCompleteIdentify.h"
#include "HttpHeartbeat.h"

HttpClient* HttpClient::m_pInstance = NULL;

HttpClient::HttpClient(QObject *parent)
	: QObject(parent)
{
	m_pManager = new QNetworkAccessManager();
}

HttpClient::~HttpClient()
{

}

HttpClient* HttpClient::instance()
{
	if (m_pInstance == NULL)
	{
		m_pInstance = new HttpClient;
	}
	return m_pInstance;
}

void HttpClient::setToken( QString sToken )
{
	m_sToken = sToken;
}

void HttpClient::RepuestOnOperatorLogin( OperatorInfo operatorInfo, InterfaceInputHead header)
{
	HttpOperatorLogin *p = new HttpOperatorLogin(operatorInfo, header);
	p->setNetManager(m_pManager);
	p->postRequest();
}

void HttpClient::RequestOnGetBaseInfo( UserBaseInfo userBaseInfo, InterfaceInputHead header)
{
	HttpGetBaseInfo *p = new HttpGetBaseInfo(userBaseInfo, header);
	p->setNetManager(m_pManager);
	p->postRequest();
}

void HttpClient::RequestOnGetIdCardPic( IdCardPicData idCardPicData, InterfaceInputHead header )
{
	HttpGetIdCardPic *p = new HttpGetIdCardPic(idCardPicData, header);
	p->setNetManager(m_pManager);
	p->postRequest();
}

void HttpClient::RequestOnIfCanIdentify( QString sysNo, InterfaceInputHead header )
{
	HttpIfCanIdentify *p = new HttpIfCanIdentify(sysNo, header);
	p->setNetManager(m_pManager);
	p->postRequest();
}

void HttpClient::RequestOnBackendRecognize( BackendRecognizeData backendRecognizeData, InterfaceInputHead header )
{
	HttpBackendRecognize *p = new HttpBackendRecognize(backendRecognizeData, header);
	p->setNetManager(m_pManager);
	p->postRequest();
}

void HttpClient::RequestOnCompleteIdentify( CompleteIdentifyData completeIdentifyData, InterfaceInputHead header )
{
	HttpCompleteIdentify *p = new HttpCompleteIdentify(completeIdentifyData, header);
	p->setNetManager(m_pManager);
	p->postRequest();
}

void HttpClient::RequestOnHeartbeat( HeartbeatData heartBeatData, InterfaceInputHead header )
{
	HttpHeartbeat *p = new HttpHeartbeat(heartBeatData, header);
	p->setNetManager(m_pManager);
	p->postRequest();
}
