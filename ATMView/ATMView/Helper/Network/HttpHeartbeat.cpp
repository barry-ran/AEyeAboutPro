/***********************************************************************************
*								HttpHeartbeat.cpp
*
* Copyright(C):	智慧眼科技股份有限公司
*
* Author:  YCL
*
* Date: 2019-06
*
* Description: 心跳包实例
***********************************************************************************/

#include "HttpHeartbeat.h"
#include "HttpSignal.h"
#include "HttpInterface.h"
#include "EnumData.h"
#include "GlogManager.h"
#include "UserConfig.h"

HttpHeartbeat::HttpHeartbeat(HeartbeatData heartBeatData, InterfaceInputHead header)
{
	setReqUrlAddress(INSTANCE_USER_CONFIG->getServerDefaultUrl() + c_sHttpInterfaceParam);

	QString param = createJsonStr(heartBeatData, header, c_sHttpActionHeartbeat, "0");
	QByteArray array;
	array.append(param);
	setReqParams(array);
}

HttpHeartbeat::~HttpHeartbeat()
{

}

void HttpHeartbeat::processResponse( QString strResult )
{
	QScriptEngine engine;
	QScriptValue sc = engine.evaluate("value=" + strResult);
	int nCode       = sc.property("data").property("respCode").toInt32();
	QString sMsg    = sc.property("data").property("respMsg").toString();
	if (!sc.property("data").property("respData").isValid())
	{
		LOG(INFO)<<"HttpHeartbeat 返回参数json格式错误";
		nCode = e_connectServerError;
		sMsg = c_sServerJsonError;
	}

	HttpSignal::instance()->RespondOnHeartbeat(nCode, sMsg);
	this->deleteLater();
}

void HttpHeartbeat::processError()
{
	HttpSignal::instance()->RespondOnHeartbeat(e_connectServerError, c_sNetError);
	this->deleteLater();
}

QString HttpHeartbeat::createJsonStr( HeartbeatData heartBeatData, InterfaceInputHead header, QString funId, QString sysCode )
{
	QJsonObject dataJson, infoJson, headJson;
	heartBeatData.assemble(infoJson);
	header.assemble(headJson);

	dataJson.insert("fnId", funId);
	dataJson.insert("sysCode", sysCode);
	dataJson.insert("sign", "Sign");
	dataJson.insert("head", headJson);
	dataJson.insert("data", infoJson);

	QJsonDocument document;
	document.setObject(dataJson);
	QByteArray byte_array = document.toJson(QJsonDocument::Compact);
	QString byte_str      = QString::fromUtf8(byte_array);
	return byte_str;
}
