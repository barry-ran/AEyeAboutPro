#ifndef HTTPAGENT_H
#define HTTPAGENT_H

#include <QObject>
#include "HttpStructData.h"

class HttpAgent : public QObject
{
	Q_OBJECT

public:
	static HttpAgent* instance();

	//�����˵�¼����
	void RequestOnOperatorLogin(OperatorInfo operatorInfo, InterfaceInputHead header);
	//��ȡ��Ա��Ϣ����
	void RequestOnGetBaseInfo(UserBaseInfo userBaseInfo, InterfaceInputHead header);
	//��ȡ��Ա���֤��Ƭ����
	void RequestOnGetIdCardPic(IdCardPicData idCardPicData, InterfaceInputHead header);
	//��ȡ��Ա�Ƿ������֤����
	void RequestOnIfCanIdentify(QString sysNo, InterfaceInputHead header);
	//��̨�ȶ�����
	void RequestOnBackendRecognize(BackendRecognizeData backendRecognizeData, InterfaceInputHead header);
	//�����֤����
	void RequestOnCompleteIdentify(CompleteIdentifyData completeIdentifyData, InterfaceInputHead header);
	//��������
	void RequestOnHeartbeat(HeartbeatData heartBeatData, InterfaceInputHead header);

signals:
	//�����˵�¼Ӧ��
	void RespondOnOperatorLogin(int nCode, QString sMsg, QString sessionId);
	//��ȡ��Ա��ϢӦ��
	void RespondOnGetBaseInfo(int nCode, QString sMsg, ModelStatus modelStatus, QString sysNo);
	//��ȡ��Ա���֤��ƬӦ��
	void RespondOnGetIdCardPic(int nCode, QString sMsg, QString picData);
	//��ȡ��Ա�Ƿ������֤Ӧ��
	void RespondOnIfCanIdentify(int nCode, QString sMsg, bool successed, QString batchId);
	//��̨�ȶ�Ӧ��
	void RespondOnBackendRecognize(int nCode, QString sMsg, int result);
	//�����֤Ӧ��
	void RespondOnCompleteIdentify(int nCode, QString sMsg, int result);
	//����Ӧ��
	void RespondOnHeartbeat(int nCode, QString sMsg);

private:
	explicit HttpAgent(QObject *parent = NULL);
	~HttpAgent();

	//��ʼ������
	void InitConnect();

private:
	static HttpAgent* m_pInstance;
};

#endif // HTTPAGENT_H
