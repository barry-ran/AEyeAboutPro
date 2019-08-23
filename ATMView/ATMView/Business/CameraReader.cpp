/***********************************************************************************
*								CameraReader.cpp
*
* Copyright(C):	智慧眼科技股份有限公司
*
* Author:  YCL
*
* Date: 2019-06
*
* Description: 用于摄像头初始化、打开、设置、采集
***********************************************************************************/

#include "CameraReader.h"
#include "GlogManager.h"
#include "ThreadManager.h"

CameraReader* CameraReader::m_pInstance = NULL;

CameraReader::CameraReader(QObject *parent)
	: QObject(parent)
{
 	moveToThread(ThreadManager::getAgentThread());
 	ThreadManager::getAgentThread()->start();
}

CameraReader::~CameraReader()
{

}

CameraReader* CameraReader::instance()
{
	if (m_pInstance == NULL)
	{
		m_pInstance = new CameraReader;
	}
	return m_pInstance;
}

void _stdcall CameraReader::faceCallback( int msgType, const char* msg, void* userData )
{
	CameraReader* pThis = (CameraReader*)userData;

	CameraData cameraData;
	QString msgData = QString::fromLocal8Bit(msg);
	ParserMsg(msgData, cameraData);

	switch (msgType) {
	case STATUS_CHANGED:
		pThis->emit onMsgReceived(cameraData.subId, cameraData.desMsg); 
		break;
	case COLLECT_FINISHED:
		if (cameraData.subId == 0)
		{
			pThis->emit onCollectFinished(cameraData);
		}
		else
		{
			pThis->emit onMsgReceived(cameraData.subId, cameraData.desMsg); 
		}
		break;
	}
}

bool CameraReader::InitSDK(WId winId)
{
	//初始化
	int ret = AEFaceColl_Init(&m_collHandle);
	if (ret != 0)
	{
		LOG(INFO)<<"初始化相机SDK失败！！！";
		return false;
	}
	LOG(INFO)<<"初始化相机SDK成功！！！";

	//设置回调
	AEFaceColl_SetCallback(m_collHandle, faceCallback, this);

	//设置预览窗口
	AEFaceColl_SetPreviewWindow(m_collHandle, (void*)winId);

	//设置参数
	char params[] = "{\"scenario\":10, \"capture.imageNumber\":1, \"capture.timeout\":30}";
	AEFaceColl_SetParameters(m_collHandle, params);
	return true;
}

bool CameraReader::openCamera()
{
	if (openCameraModule(0))
	{
		openCameraModule(1);
		return true;
	}
	return false;
}

bool CameraReader::openCameraModule( int cameraType )
{
	QString cameraText = (cameraType == 0) ? QStringLiteral("可见光") : QStringLiteral("近红外");
	int ret = AEFaceColl_OpenCamera(m_collHandle, cameraType);
	if (ret != 0)
	{
		LOG(INFO)<<"打开"<<cameraText.toLocal8Bit().data()<<"相机失败！！！";
		return false;
	}
	LOG(INFO)<<"打开"<<cameraText.toLocal8Bit().data()<<"相机成功！！！";
	return true;
}

void CameraReader::closeCamera()
{
	int ret = AEFaceColl_CloseCamera(m_collHandle);
	if (ret != 0)
	{
		emit onMsgReceived(-1, QStringLiteral("关闭摄像头失败"));
		return;
	}
}

void CameraReader::startCollect()
{
	int ret = AEFaceColl_StartCollect(m_collHandle);
	if (ret != 0)
	{
		emit onMsgReceived(-1, QStringLiteral("图像采集失败"));
		return; 
	}
}

void CameraReader::ParserMsg( QString msgJson, CameraData& cameraData )
{
	QScriptEngine engine;
	QScriptValue sc = engine.evaluate("value=" + msgJson);
	cameraData.subId = sc.property("subId").toInt32();
	cameraData.desMsg = sc.property("description").toString();

	if (sc.property("visImageDatas").isArray())
	{
		QScriptValueIterator it(sc.property("visImageDatas"));
		while (it.hasNext())
		{
			it.next();
			CameraData::ImageData imageData;
			imageData.imageData = it.value().property("image").toString();
			QFile file("d:\\test.jpeg");
			file.open(QIODevice::ReadWrite | QIODevice::Append);
			file.write(imageData.imageData.toLocal8Bit(), imageData.imageData.length());
			file.waitForBytesWritten(3000);
			file.flush();
			file.close();
			if (imageData.imageData.isEmpty())
			{
				continue;
			}
			imageData.faceRect = it.value().property("faceRect").toString();

			cameraData.imageInfoData.append(imageData);
		}
	}
}
