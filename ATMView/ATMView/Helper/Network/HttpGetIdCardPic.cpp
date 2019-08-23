/***********************************************************************************
*								HttpGetIdCardPic.cpp
*
* Copyright(C):	智慧眼科技股份有限公司
*
* Author:  YCL
*
* Date: 2019-06
*
* Description: 获取身份证照片网络请求实例
***********************************************************************************/

#include "HttpGetIdCardPic.h"
#include "HttpSignal.h"
#include "HttpInterface.h"
#include "EnumData.h"
#include "GlogManager.h"
#include "UserConfig.h"

HttpGetIdCardPic::HttpGetIdCardPic( IdCardPicData idCardPicData, InterfaceInputHead header )
{
	setReqUrlAddress(INSTANCE_USER_CONFIG->getServerDefaultUrl() + c_sHttpInterfaceParam);

	QString param = createJsonStr(idCardPicData, header, c_sHttpActionGetIdCardPic, "0");
	QByteArray array;
	array.append(param);
	setReqParams(array);
}

HttpGetIdCardPic::~HttpGetIdCardPic()
{

}

void HttpGetIdCardPic::processResponse( QString strResult )
{
	QScriptEngine engine;
	QScriptValue sc = engine.evaluate("value=" + strResult);
	int nCode       = sc.property("data").property("respCode").toInt32();
	QString sMsg    = sc.property("data").property("respMsg").toString();
	if (!sc.property("data").property("respData").isValid())
	{
		LOG(INFO)<<"HttpGetIdCardPic 返回参数json格式错误";
		nCode = e_connectServerError;
		sMsg = c_sServerJsonError;
	}

	QString picData = sc.property("data").property("respData").property("picData").toString();
	HttpSignal::instance()->RespondOnGetIdCardPic(nCode, sMsg, picData);
	this->deleteLater();
}

void HttpGetIdCardPic::processError()
{
	HttpSignal::instance()->RespondOnGetIdCardPic(e_connectServerError, c_sNetError, "");
	this->deleteLater();
}

QString HttpGetIdCardPic::createJsonStr( IdCardPicData idCardPicData, InterfaceInputHead header, QString funId, QString sysCode )
{
	QJsonObject dataJson, infoJson, headJson;
	idCardPicData.assemble(infoJson);
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
