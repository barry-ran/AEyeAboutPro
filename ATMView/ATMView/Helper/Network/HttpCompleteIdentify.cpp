/***********************************************************************************
*								HttpCompleteIdentify.cpp
*
* Copyright(C):	智慧眼科技股份有限公司
*
* Author:  YCL
*
* Date: 2019-06
*
* Description: 完成认证网络请求实例
***********************************************************************************/

#include "HttpCompleteIdentify.h"
#include "HttpSignal.h"
#include "HttpInterface.h"
#include "EnumData.h"
#include "GlogManager.h"
#include "UserConfig.h"

HttpCompleteIdentify::HttpCompleteIdentify(CompleteIdentifyData completeIdentifyData, InterfaceInputHead header)
{
	setReqUrlAddress(INSTANCE_USER_CONFIG->getServerDefaultUrl() + c_sHttpInterfaceParam);

	QString param = createJsonStr(completeIdentifyData, header, c_sHttpActionCompleteIdentify, "0");
	QByteArray array;
	array.append(param);
	setReqParams(array);
}

HttpCompleteIdentify::~HttpCompleteIdentify()
{

}

void HttpCompleteIdentify::processResponse( QString strResult )
{
	QScriptEngine engine;
	QScriptValue sc = engine.evaluate("value=" + strResult);
	int nCode       = sc.property("data").property("respCode").toInt32();
	QString sMsg    = sc.property("data").property("respMsg").toString();
	if (!sc.property("data").property("respData").isValid())
	{
		LOG(INFO)<<"HttpCompleteIdentify 返回参数json格式错误";
		nCode = e_connectServerError;
		sMsg = c_sServerJsonError;
	}

	int identifyResult = sc.property("data").property("respData").property("identifyResult").toInt32();
	HttpSignal::instance()->RespondOnCompleteIdentify(nCode, sMsg, identifyResult);
	this->deleteLater();
}

void HttpCompleteIdentify::processError()
{
	HttpSignal::instance()->RespondOnCompleteIdentify(e_connectServerError, c_sNetError, -1);
	this->deleteLater();
}

QString HttpCompleteIdentify::createJsonStr( CompleteIdentifyData completeIdentifyData, InterfaceInputHead header, QString funId, QString sysCode )
{
	QJsonObject dataJson, infoJson, headJson;
	completeIdentifyData.assemble(infoJson);
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
