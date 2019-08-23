#ifndef HTTPBACKENDRECOGNIZE_H
#define HTTPBACKENDRECOGNIZE_H

#include <QObject>
#include "IHttpReqRes.h"
#include "HttpStructData.h"

class HttpBackendRecognize : public IHttpReqRes
{
	Q_OBJECT

public:
	HttpBackendRecognize(BackendRecognizeData backendRecognizeData, InterfaceInputHead header);
	~HttpBackendRecognize();

protected:
	void processResponse(QString strResult);
	void processError();

private:
	QString createJsonStr(BackendRecognizeData backendRecognizeData, InterfaceInputHead header, QString funId, QString sysCode);
};

#endif // HTTPBACKENDRECOGNIZE_H
