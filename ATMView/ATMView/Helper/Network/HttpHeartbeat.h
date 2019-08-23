#ifndef HTTPHEARTBEAT_H
#define HTTPHEARTBEAT_H

#include <QObject>
#include "IHttpReqRes.h"
#include "HttpStructData.h"

class HttpHeartbeat : public IHttpReqRes
{
	Q_OBJECT

public:
	explicit HttpHeartbeat(HeartbeatData heartBeatData, InterfaceInputHead header);
	~HttpHeartbeat();

protected:
	void processResponse(QString strResult);
	void processError();

private:
	QString createJsonStr(HeartbeatData heartBeatData, InterfaceInputHead header, QString funId, QString sysCode);
};

#endif // HTTPHEARTBEAT_H
