#ifndef HTTPSIGNAL_H
#define HTTPSIGNAL_H

#include <QObject>
#include "HttpStructData.h"

class HttpSignal : public QObject
{
	Q_OBJECT

public:
	static HttpSignal* instance(); 

signals:
	void RespondOnOperatorLogin(int nCode, QString sMsg, QString sessionId);
	void RespondOnGetBaseInfo(int nCode, QString sMsg, ModelStatus modelStatus, QString sysNo);
	void RespondOnGetIdCardPic(int nCode, QString sMsg, QString picData);
	void RespondOnIfCanIdentify(int nCode, QString sMsg, bool successed, QString batchId);
	void RespondOnBackendRecognize(int nCode, QString sMsg, int result);
	void RespondOnCompleteIdentify(int nCode, QString sMsg, int result);
	void RespondOnHeartbeat(int nCode, QString sMsg);

private:
	explicit HttpSignal(QObject *parent = NULL);
	~HttpSignal();

private:
	static HttpSignal* m_pInstance;
};

#endif // HTTPSIGNAL_H
