#ifndef HTTPAGENT_H
#define HTTPAGENT_H

#include <QObject>
#include "HttpStructData.h"

class HttpAgent : public QObject
{
	Q_OBJECT

public:
	static HttpAgent* instance();

	//经办人登录请求
	void RequestOnOperatorLogin(OperatorInfo operatorInfo, InterfaceInputHead header);
	//获取人员信息请求
	void RequestOnGetBaseInfo(UserBaseInfo userBaseInfo, InterfaceInputHead header);
	//获取人员身份证照片请求
	void RequestOnGetIdCardPic(IdCardPicData idCardPicData, InterfaceInputHead header);
	//获取人员是否可以认证请求
	void RequestOnIfCanIdentify(QString sysNo, InterfaceInputHead header);
	//后台比对请求
	void RequestOnBackendRecognize(BackendRecognizeData backendRecognizeData, InterfaceInputHead header);
	//完成认证请求
	void RequestOnCompleteIdentify(CompleteIdentifyData completeIdentifyData, InterfaceInputHead header);
	//心跳请求
	void RequestOnHeartbeat(HeartbeatData heartBeatData, InterfaceInputHead header);

signals:
	//经办人登录应答
	void RespondOnOperatorLogin(int nCode, QString sMsg, QString sessionId);
	//获取人员信息应答
	void RespondOnGetBaseInfo(int nCode, QString sMsg, ModelStatus modelStatus, QString sysNo);
	//获取人员身份证照片应答
	void RespondOnGetIdCardPic(int nCode, QString sMsg, QString picData);
	//获取人员是否可以认证应答
	void RespondOnIfCanIdentify(int nCode, QString sMsg, bool successed, QString batchId);
	//后台比对应答
	void RespondOnBackendRecognize(int nCode, QString sMsg, int result);
	//完成认证应答
	void RespondOnCompleteIdentify(int nCode, QString sMsg, int result);
	//心跳应答
	void RespondOnHeartbeat(int nCode, QString sMsg);

private:
	explicit HttpAgent(QObject *parent = NULL);
	~HttpAgent();

	//初始化连接
	void InitConnect();

private:
	static HttpAgent* m_pInstance;
};

#endif // HTTPAGENT_H
