/***********************************************************************************
*								IHttpReqRes.cpp
*
* Copyright(C):	智慧眼科技股份有限公司
*
* Author:  YCL
*
* Date: 2019-06
*
* Description: 网络层底层实例
***********************************************************************************/

#include "IHttpReqRes.h"
#include <QHttpMultiPart>
#include "GlogManager.h"

IHttpReqRes::IHttpReqRes(QObject *parent)
	: QObject(parent)
	, m_nReconnectTimes(0)
	, m_nOverTimeLen(10)
	, m_bOverTime(false)
{
	initConnect();
}

IHttpReqRes::~IHttpReqRes()
{

}

void IHttpReqRes::setNetManager(QNetworkAccessManager* pManager)
{
	pManager->setNetworkAccessible(QNetworkAccessManager::Accessible);
	m_pManager = pManager;
}

void IHttpReqRes::setReqParams(QByteArray byArr)
{
// 	byArr.replace("+", "%2B");
// 	byArr.replace("#", "%23");
	m_reqParams = byArr;

}

void IHttpReqRes::postRequest()
{
	QNetworkRequest request;
	QSslConfiguration config;
	config.setPeerVerifyMode(QSslSocket::VerifyNone);
	config.setProtocol(QSsl::TlsV1SslV3);
	request.setSslConfiguration(config);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

	request.setUrl(QUrl(m_sUrlAddress));
	m_pReply = m_pManager->post(request, m_reqParams);
	connect(m_pReply, SIGNAL(finished()), this, SLOT(slot_ReplyFinished()));
	m_sTestUrl = request.url().toString().append(m_reqParams); // 测试用
	if (!m_sTestUrl.isEmpty())
	{
		//LOG(INFO)<<m_sTestUrl.toStdString();
	}

	m_bOverTime = false;
	if (!m_overTimer.isActive())
	{
		m_overTimer.start(m_nOverTimeLen * 1000);
	}
}

QString IHttpReqRes::getTestUrl()
{
	return m_sTestUrl;
}

void IHttpReqRes::setOverTimeLengh(int nOverTimeLengh)
{
	m_nOverTimeLen = nOverTimeLengh;
}

bool IHttpReqRes::isOverTime()
{
	return m_bOverTime;
}

void IHttpReqRes::setReqUrlAddress(QString urlAddress)
{
	m_sUrlAddress = urlAddress;
}

void IHttpReqRes::slot_ReplyFinished()
{
	m_bOverTime = false;
	m_overTimer.stop();

	QTextCodec *codec = QTextCodec::codecForName("utf8");

	QNetworkReply::NetworkError err = m_pReply->error();

	if (err != QNetworkReply::NoError)
	{
		LOG(INFO)<<"网络异常："<<m_sTestUrl.toStdString()<<"; errCod: "<<err<<"; errorMsg: "<<m_pReply->errorString().toLocal8Bit().data();
		processError();
	}
	else
	{
		m_nReconnectTimes = 0;
		QString strResult = codec->toUnicode(m_pReply->readAll());
		m_pReply->deleteLater();
		m_pReply = NULL;
		processResponse(strResult);
	}
}

void IHttpReqRes::slot_overTimeout()
{
	m_bOverTime = true;
	LOG(INFO)<<"网络超时："<<m_sTestUrl.toStdString();
	processError();
}

void IHttpReqRes::initConnect()
{
	connect(&m_overTimer, SIGNAL(timeout()), this, SLOT(slot_overTimeout()));
}
