/***********************************************************************************
*								HttpGetBaseInfo.cpp
*
* Copyright(C):	智慧眼科技股份有限公司
*
* Author:  YCL
*
* Date: 2019-06
*
* Description: 获取人员信息网络请求实例
***********************************************************************************/

#include "HttpGetBaseInfo.h"
#include "HttpSignal.h"
#include "HttpInterface.h"
#include "EnumData.h"
#include "GlogManager.h"
#include "UserConfig.h"

HttpGetBaseInfo::HttpGetBaseInfo(UserBaseInfo userBaseInfo, InterfaceInputHead header)
{
	setReqUrlAddress(INSTANCE_USER_CONFIG->getServerDefaultUrl() + c_sHttpInterfaceParam);

	QString param = createJsonStr(userBaseInfo, header, c_sHttpActionGetBaseInfo, "0");
	QByteArray array;
	array.append(param);
	setReqParams(array);
}

HttpGetBaseInfo::~HttpGetBaseInfo()
{

}

void HttpGetBaseInfo::processResponse( QString strResult )
{
	QScriptEngine engine;
	QScriptValue sc = engine.evaluate("value=" + strResult);
	int nCode       = sc.property("data").property("respCode").toInt32();
	QString sMsg    = sc.property("data").property("respMsg").toString();
	if (!sc.property("data").property("respData").isValid())
	{
		LOG(INFO)<<"HttpGetBaseInfo 返回参数json格式错误";
		nCode = e_connectServerError;
		sMsg = c_sServerJsonError;
	}

	ModelStatus modelStatus;
	QString sysNo;
	if (sc.property("data").property("respData").isArray())
	{
		int index = 0;
		QScriptValueIterator it(sc.property("data").property("respData"));
		QStringList list = sc.property("data").property("respData").toVariant().toStringList();
		while (it.hasNext())
		{
			it.next();
			if (index)
			{
				break;
			}

			sysNo = it.value().property("sysNo").toString();
			if (it.value().property("modelStatus").isArray())
			{
				QScriptValueIterator statusIt(it.value().property("modelStatus"));
				while (statusIt.hasNext())
				{
					statusIt.next();
					int bioType   = statusIt.value().property("bioType").toInt32();
					int modelType = statusIt.value().property("modelType").toInt32();
					int status    = statusIt.value().property("status").toInt32();
					if (bioType == 0 && modelType == 0 && status == 0)
					{
						continue;
					}

					ModelPickerFunc(modelStatus, bioType, modelType, status);
				}
			}
			index++;
		}
	}

	HttpSignal::instance()->RespondOnGetBaseInfo(nCode, sMsg, modelStatus, sysNo);
	this->deleteLater();
}

void HttpGetBaseInfo::processError()
{
	ModelStatus modelStatus;
	HttpSignal::instance()->RespondOnGetBaseInfo(e_connectServerError, c_sNetError, modelStatus, "");
	this->deleteLater();
}

QString HttpGetBaseInfo::createJsonStr( UserBaseInfo userBaseInfo, InterfaceInputHead header, QString funId, QString sysCode )
{
	QJsonObject dataJson, infoJson, headJson;
	userBaseInfo.assemble(infoJson);
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

void HttpGetBaseInfo::ModelPickerFunc( ModelStatus& modelStatus, int bioType, int modelType, int status )
{
	switch(bioType) 
	{
	case BioType_Face:
		if (status > modelStatus.faceModelStatus) 
		{
			modelStatus.faceModelStatus = status;
		}
		if (ModelType_VIS == modelType) 
		{
			modelStatus.visModelStatus = status;
		}
		else if (ModelType_NIR == modelType) 
		{
			modelStatus.nirModelStatus = status;
		}
		break;
	case BioType_FVein:
		if (status > modelStatus.fveinModelStatus) 
		{
			modelStatus.fveinModelStatus = status;
		}
		break;
	case BioType_FPrint:
		if (status > modelStatus.fprintModelStatus) 
		{
			modelStatus.fprintModelStatus = status;
		}
		break;
	default:
		break;
	}			
}
