/***********************************************************************************
*								HttpAgent.cpp
*
* Copyright(C):	智慧眼科技股份有限公司
*
* Author:  YCL
*
* Date: 2019-06
*
* Description: Http代理层，起线程发起网络请求
***********************************************************************************/

#include "HttpAgent.h"
#include "ThreadManager.h"
#include "HttpClient.h"
#include "HttpSignal.h"

HttpAgent* HttpAgent::m_pInstance = NULL;

HttpAgent::HttpAgent(QObject *parent)
	: QObject(parent)
{
	InitConnect();
	moveToThread(ThreadManager::getAgentThread());
	ThreadManager::getAgentThread()->start();
}

HttpAgent::~HttpAgent()
{

}

HttpAgent* HttpAgent::instance()
{
	if (m_pInstance == NULL)
	{
		m_pInstance = new HttpAgent;
	}
	return m_pInstance;
}

void HttpAgent::InitConnect()
{
	connect(HttpSignal::instance(), SIGNAL(RespondOnOperatorLogin(int, QString, QString)),
		this, SIGNAL(RespondOnOperatorLogin(int, QString, QString)));
	connect(HttpSignal::instance(), SIGNAL(RespondOnGetIdCardPic(int, QString, QString)), 
		this, SIGNAL(RespondOnGetIdCardPic(int, QString, QString)));
	connect(HttpSignal::instance(), SIGNAL(RespondOnIfCanIdentify(int, QString, bool, QString)), 
		this, SIGNAL(RespondOnIfCanIdentify(int, QString, bool, QString)));
	connect(HttpSignal::instance(), SIGNAL(RespondOnBackendRecognize(int, QString, int)), 
		this, SIGNAL(RespondOnBackendRecognize(int, QString, int)));
	connect(HttpSignal::instance(), SIGNAL(RespondOnCompleteIdentify(int, QString, int)), 
		this, SIGNAL(RespondOnCompleteIdentify(int, QString, int)));
	connect(HttpSignal::instance(), SIGNAL(RespondOnHeartbeat(int, QString)), 
		this, SIGNAL(RespondOnHeartbeat(int, QString)));

	qRegisterMetaType<ModelStatus>("ModelStatus");
	connect(HttpSignal::instance(), SIGNAL(RespondOnGetBaseInfo(int, QString, ModelStatus, QString)),
		this, SIGNAL(RespondOnGetBaseInfo(int, QString, ModelStatus, QString)));
}

void HttpAgent::RequestOnOperatorLogin(OperatorInfo operatorInfo, InterfaceInputHead header)
{
	HttpClient::instance()->RepuestOnOperatorLogin(operatorInfo, header);
}

void HttpAgent::RequestOnGetBaseInfo( UserBaseInfo userBaseInfo, InterfaceInputHead header )
{
	HttpClient::instance()->RequestOnGetBaseInfo(userBaseInfo, header);
}

void HttpAgent::RequestOnGetIdCardPic( IdCardPicData idCardPicData, InterfaceInputHead header )
{
	HttpClient::instance()->RequestOnGetIdCardPic(idCardPicData, header);
}

void HttpAgent::RequestOnIfCanIdentify( QString sysNo, InterfaceInputHead header )
{
	HttpClient::instance()->RequestOnIfCanIdentify(sysNo, header);
}

void HttpAgent::RequestOnBackendRecognize( BackendRecognizeData backendRecognizeData, InterfaceInputHead header )
{
	HttpClient::instance()->RequestOnBackendRecognize(backendRecognizeData, header);
}

void HttpAgent::RequestOnCompleteIdentify( CompleteIdentifyData completeIdentifyData, InterfaceInputHead header )
{
	HttpClient::instance()->RequestOnCompleteIdentify(completeIdentifyData, header);
}

void HttpAgent::RequestOnHeartbeat( HeartbeatData heartBeatData, InterfaceInputHead header )
{
	HttpClient::instance()->RequestOnHeartbeat(heartBeatData, header);
}
