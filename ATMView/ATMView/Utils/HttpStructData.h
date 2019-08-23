/***********************************************************************************
*								HttpStructData.h
*
* Copyright(C):	智慧眼科技股份有限公司
*
* Author:  YCL
*
* Date: 2019-06
*
* Description: 通用结构体数据
***********************************************************************************/

#pragma once

#include <QString>
#include <QVariant>
#include <QDateTime>
#include <QScriptEngine>
#include <QScriptValue>
#include <QScriptValueIterator>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QVector>

#include "EnumData.h"

//经办人登录信息
typedef struct OperatorInfo
{
   QString userId;     //用户ID
   QString passwd;     //密码

   QString userName;    //姓名
   QString idCard;      //证件号

   QString type;        //登录类型
   bool assemble(QJsonObject& obj) const
   {
	   obj.insert("type", type);
	   obj.insert("name", userName);
	   obj.insert("idCard", idCard);
	   obj.insert("userId", userId);
	   obj.insert("password", passwd);
	   return true;
   }
}OperatorInfo_t;
Q_DECLARE_METATYPE(OperatorInfo)

//接口头数据
typedef struct InterfaceInputHead
{
	QString sessionId;
	QString terminalId;
	QString terminalType;
	QString terminalVersion;
	QString sysType;
	QString sysVersion;
	QString userId;
	QString portalVersion;
	QString invokeTime;

	InterfaceInputHead()
	{
		terminalType = "20010";
		sysType = "windows";
		sysVersion = "windows8";
		portalVersion = "1.0";
	}

	bool assemble(QJsonObject& obj) const
	{
	   obj.insert("sessionId", sessionId);
	   obj.insert("terminalId", terminalId);
	   obj.insert("terminalType", terminalType);
	   obj.insert("terminalVersion", terminalVersion);
	   obj.insert("sysType", sysType);
	   obj.insert("sysVersion", sysVersion);
	   obj.insert("userId", userId);
	   obj.insert("portalVersion", portalVersion);
	   obj.insert("invokeTime", QDateTime::currentDateTime().toString("yyyyMMdd"));
       return true;
	}

	InterfaceInputHead& operator =(const InterfaceInputHead& pkg)//赋值运算符
	{
		if (this != &pkg)
		{
			this->sessionId = pkg.sessionId;
			this->terminalId   = pkg.terminalId;
			this->terminalType = pkg.terminalType;
			this->terminalVersion = pkg.terminalVersion;
			this->sysType = pkg.sysType;
			this->sysVersion     = pkg.sysVersion;
			this->userId = pkg.userId;
			this->portalVersion     = pkg.portalVersion;
			this->invokeTime = pkg.invokeTime;
		}
		return *this;
	}
}InterfaceInputHead_t;
Q_DECLARE_METATYPE(InterfaceInputHead)

//用户基本信息
typedef struct UserBaseInfo
{
	QString name;
	QString idCard;
	QString sysNo;
	QString cardType;

	bool assemble(QJsonObject& obj) const
	{
		obj.insert("name", name);
		obj.insert("idCard", idCard);
		obj.insert("sysNo", sysNo);
		obj.insert("cardType", cardType);
		return true;
	}
}UserBaseInfo_t;
Q_DECLARE_METATYPE(UserBaseInfo)


//模型数据
struct ModelStatus
{
	int visModelStatus; 
	int nirModelStatus;

	int faceModelStatus;
	int fveinModelStatus;
	int fprintModelStatus;

	ModelStatus()
	{
		visModelStatus = 1;
		nirModelStatus = 1;
		faceModelStatus = -1;
		fveinModelStatus = -1;
		fprintModelStatus = -1;
	}
};
Q_DECLARE_METATYPE(ModelStatus)

//读卡器认证结果数据
struct AuthReadCardResult
{
	QString name;
	int cardType;
	QString certificateNumber;

	AuthReadCardResult(){
		cardType = TYPE_IDCARD;
	}

	void clear() {
		name.clear();
		cardType = TYPE_IDCARD;
		certificateNumber.clear();
	}
};
Q_DECLARE_METATYPE(AuthReadCardResult)

//读卡器数据
struct IdCardPicData
{
	QString sysCode;
	QString sysNo;
	QString name;
	QString idCard;

	bool assemble(QJsonObject& obj) const
	{
		obj.insert("sysCode", sysCode);
		if (!sysNo.isEmpty() && sysNo.toInt() > 0)
		{
			obj.insert("sysNo", sysNo);
		}
		else
		{
			obj.insert("name", name);
			obj.insert("idCard", idCard);
		}
		return true;
	}
};

//后台比对数据
struct BackendRecognizeData
{
	struct CompareDataItem
	{
		QString bioType;
		QString modelType;
		QString deviceType;
		QString picImage;
		QVector<QString> pics;
		QVector<QString> faces;
	};

	QString sysNo;
	QString batchId;
	QVector<CompareDataItem> compareData;
	QString name;
	QString idCard;

	bool assemble(QJsonObject& obj) const
	{
		QJsonArray jsonCompareData;
		for (int i = 0; i < compareData.size(); ++i)
		{
			QJsonObject jsonCompareDataItem;
			jsonCompareDataItem.insert("bioType", compareData.at(i).bioType);
			jsonCompareDataItem.insert("modelType", compareData.at(i).modelType);
			jsonCompareDataItem.insert("deviceType", compareData.at(i).deviceType);
			jsonCompareDataItem.insert("picImage", compareData.at(i).picImage);

			QJsonArray jsonPics;
			for (int j = 0; j < compareData.at(i).pics.size(); ++j)
			{
				jsonPics.insert(j, compareData.at(i).pics.at(j));
			}
			jsonCompareDataItem.insert("pics", jsonPics);

			QJsonArray jsonFaces;
			for (int k = 0; k < compareData.at(i).faces.size(); ++k)
			{
				jsonFaces.insert(k, compareData.at(i).faces.at(k));
			}
			jsonCompareDataItem.insert("faces", jsonFaces);

			jsonCompareData.insert(i, jsonCompareDataItem);
		}

		if (!sysNo.isEmpty() && sysNo.toInt() > 0)
		{
			obj.insert("sysNo", sysNo);
		}
		else
		{
			obj.insert("name", name);
			obj.insert("idCard", idCard);
		}
		obj.insert("batchId", batchId);
		obj.insert("compareData", jsonCompareData);
		return true;
	}
};

//摄像头数据
struct CameraData
{
	struct ImageData{
		QString imageData;
		QString faceRect;
	};

	int subId;
	QString desMsg;
	QVector<ImageData> imageInfoData;

	CameraData() {
		subId = 0;
	}
};
Q_DECLARE_METATYPE(CameraData)

//完成认证接口数据
struct CompleteIdentifyData
{
	struct RecognizeDataItem
	{
		QString bioType;
		QString result;
	};

	QString sysNo;
	QString batchId;
	QString autoAppeal;
	QString name;
	QString idCard;
	QVector<RecognizeDataItem> recognizeData;

	CompleteIdentifyData() {
		autoAppeal = "0";
	}

	bool assemble(QJsonObject& obj) const
	{
		QJsonArray jsonRecognzieData;
		for (int i = 0; i < recognizeData.size(); ++i)
		{
			QJsonObject jsonRecognizeDataItem;
			jsonRecognizeDataItem.insert("bioType", recognizeData.at(i).bioType);
			jsonRecognizeDataItem.insert("result", recognizeData.at(i).result);

			jsonRecognzieData.insert(i, jsonRecognizeDataItem);
		}

		if (!sysNo.isEmpty() && sysNo.toInt() > 0)
		{
			obj.insert("sysNo", sysNo);
		}
		else
		{
			obj.insert("name", name);
			obj.insert("idCard", idCard);
		}
		obj.insert("batchId", batchId);
		obj.insert("autoAppeal", autoAppeal);
		obj.insert("aliveData", jsonRecognzieData);

		return true;
	}
};

//心跳包数据
struct HeartbeatData
{
	QString offlineCount;

	bool assemble(QJsonObject& obj) const
	{
		obj.insert("offlineCount", offlineCount);
		return true;
	}
};