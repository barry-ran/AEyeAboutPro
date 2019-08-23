/***********************************************************************************
*								HttpIfCanIdentify.cpp
*
* Copyright(C):	智慧眼科技股份有限公司
*
* Author:  YCL
*
* Date: 2019-06
*
* Description: 是否能够认证网络请求实例
***********************************************************************************/

#include "HttpIfCanIdentify.h"
#include "HttpSignal.h"
#include "HttpInterface.h"
#include "EnumData.h"
#include "GlogManager.h"
#include "UserConfig.h"

HttpIfCanIdentify::HttpIfCanIdentify(QString sysNo, InterfaceInputHead header)
{
	setReqUrlAddress(INSTANCE_USER_CONFIG->getServerDefaultUrl() + c_sHttpInterfaceParam);

	QString param = createJsonStr(sysNo, header, c_sHttpActionIfCanIdentify, "0");
	QByteArray array;
	array.append(param);
	setReqParams(array);
}

HttpIfCanIdentify::~HttpIfCanIdentify()
{

}

void HttpIfCanIdentify::processResponse( QString strResult )
{
	QScriptEngine engine;
	QScriptValue sc = engine.evaluate("value=" + strResult);
	int nCode       = sc.property("data").property("respCode").toInt32();
	QString sMsg    = sc.property("data").property("respMsg").toString();
	bool successed    = sc.property("data").property("success").toBool();
	QString batchId;
	if (successed)
	{
       batchId = sc.property("data").property("respData").property("batchId").toString();
	}

	HttpSignal::instance()->RespondOnIfCanIdentify(nCode, sMsg, successed, batchId);
	this->deleteLater();
}

void HttpIfCanIdentify::processError()
{
	HttpSignal::instance()->RespondOnIfCanIdentify(e_connectServerError, c_sNetError, false, "");
	this->deleteLater();
}

QString HttpIfCanIdentify::createJsonStr( QString sysNo, InterfaceInputHead header, QString funId, QString sysCode )
{
	QJsonObject dataJson, infoJson, headJson;
	infoJson.insert("sysNo", sysNo);
	infoJson.insert("busiType", "DYLQ");
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
