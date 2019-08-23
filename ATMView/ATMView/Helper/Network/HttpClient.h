#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include "HttpStructData.h"

class HttpClient : public QObject
{
	Q_OBJECT

public:
	static HttpClient* instance();
	void setToken(QString sToken);

	void RepuestOnOperatorLogin(OperatorInfo operatorInfo, InterfaceInputHead header);
	void RequestOnGetBaseInfo(UserBaseInfo userBaseInfo, InterfaceInputHead header);
	void RequestOnGetIdCardPic(IdCardPicData idCardPicData, InterfaceInputHead header);
	void RequestOnIfCanIdentify(QString sysNo, InterfaceInputHead header);
	void RequestOnBackendRecognize(BackendRecognizeData backendRecognizeData, InterfaceInputHead header);
	void RequestOnCompleteIdentify(CompleteIdentifyData completeIdentifyData, InterfaceInputHead header);
	void RequestOnHeartbeat(HeartbeatData heartBeatData, InterfaceInputHead header);

private:
	explicit HttpClient(QObject *parent = NULL);
	~HttpClient();

private:
	static HttpClient* m_pInstance;
	QString m_sToken;
	QNetworkAccessManager* m_pManager;
};

#endif // HTTPCLIENT_H
