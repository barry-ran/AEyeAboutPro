#ifndef CAMERAREADER_H
#define CAMERAREADER_H

#include <QObject>
#include <QtGui>
#include "AEyeFaceColl.h"
#include "HttpStructData.h"

//回调枚举
enum TypeOfCallback
{
	STATUS_CHANGED = 0,   //状态改变
	COLLECT_FINISHED = 1, //采集完成
};

class CameraReader : public QObject
{
	Q_OBJECT

public:
	static CameraReader* instance();

	//初始化SDK
	bool InitSDK(WId winId);
	//打开摄像头
	bool openCamera();
	//关闭摄像头
	void closeCamera();
	//开始采集
	void startCollect();
private:
	explicit CameraReader(QObject *parent = 0);
	~CameraReader();

	//消息回调函数
	static void _stdcall faceCallback(int msgType, const char* msg, void* userData);
	//解析JSON函数
	static void ParserMsg(QString msgJson, CameraData& cameraData);
	//打开相机设备
	bool openCameraModule(int cameraType);

signals:
	//接收异常消息
	void onMsgReceived(int errCode, QString msg);
	//采集完成
	void onCollectFinished(CameraData cameraData);

private:
	static CameraReader* m_pInstance;
	HAEFaceColl m_collHandle;
};

#endif // CAMERAREADER_H
