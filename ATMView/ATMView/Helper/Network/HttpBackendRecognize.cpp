/***********************************************************************************
*								HttpBackendRecognize.cpp
*
* Copyright(C):	�ǻ��ۿƼ��ɷ����޹�˾
*
* Author:  YCL
*
* Date: 2019-06
*
* Description: ��̨�ȶ���������ʵ��
***********************************************************************************/

#include "HttpBackendRecognize.h"
#include "HttpSignal.h"
#include "HttpInterface.h"
#include "EnumData.h"
#include "GlogManager.h"
#include "UserConfig.h"

HttpBackendRecognize::HttpBackendRecognize(BackendRecognizeData backendRecognizeData, InterfaceInputHead header)
{
	setReqUrlAddress(INSTANCE_USER_CONFIG->getServerDefaultUrl() + c_sHttpInterfaceParam);

	QString param = createJsonStr(backendRecognizeData, header, c_sHttpActionBackendRecognize, "0");
	QByteArray array;
	array.append(param);
	setReqParams(array);
}

HttpBackendRecognize::~HttpBackendRecognize()
{

}

void HttpBackendRecognize::processResponse( QString strResult )
{
	QScriptEngine engine;
	QScriptValue sc = engine.evaluate("value=" + strResult);
	int nCode       = sc.property("data").property("respCode").toInt32();
	QString sMsg    = sc.property("data").property("respMsg").toString();
	if (!sc.property("data").property("respData").isValid())
	{
		LOG(INFO)<<"HttpBackendRecognize ���ز���json��ʽ����";
		nCode = e_connectServerError;
		sMsg = c_sServerJsonError;
	}

	int result = sc.property("data").property("respData").property("result").toInt32();
	HttpSignal::instance()->RespondOnBackendRecognize(nCode, sMsg, result);
	this->deleteLater();
}

void HttpBackendRecognize::processError()
{
	HttpSignal::instance()->RespondOnBackendRecognize(e_connectServerError, c_sNetError, -1);
	this->deleteLater();
}

QString HttpBackendRecognize::createJsonStr( BackendRecognizeData backendRecognizeData, InterfaceInputHead header, QString funId, QString sysCode )
{
	QJsonObject dataJson, infoJson, headJson;
	backendRecognizeData.assemble(infoJson);
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
