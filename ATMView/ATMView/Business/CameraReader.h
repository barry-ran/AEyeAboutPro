#ifndef CAMERAREADER_H
#define CAMERAREADER_H

#include <QObject>
#include <QtGui>
#include "AEyeFaceColl.h"
#include "HttpStructData.h"

//�ص�ö��
enum TypeOfCallback
{
	STATUS_CHANGED = 0,   //״̬�ı�
	COLLECT_FINISHED = 1, //�ɼ����
};

class CameraReader : public QObject
{
	Q_OBJECT

public:
	static CameraReader* instance();

	//��ʼ��SDK
	bool InitSDK(WId winId);
	//������ͷ
	bool openCamera();
	//�ر�����ͷ
	void closeCamera();
	//��ʼ�ɼ�
	void startCollect();
private:
	explicit CameraReader(QObject *parent = 0);
	~CameraReader();

	//��Ϣ�ص�����
	static void _stdcall faceCallback(int msgType, const char* msg, void* userData);
	//����JSON����
	static void ParserMsg(QString msgJson, CameraData& cameraData);
	//������豸
	bool openCameraModule(int cameraType);

signals:
	//�����쳣��Ϣ
	void onMsgReceived(int errCode, QString msg);
	//�ɼ����
	void onCollectFinished(CameraData cameraData);

private:
	static CameraReader* m_pInstance;
	HAEFaceColl m_collHandle;
};

#endif // CAMERAREADER_H
