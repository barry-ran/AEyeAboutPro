#ifndef HTTPIFCANIDENTIFY_H
#define HTTPIFCANIDENTIFY_H

#include <QObject>
#include "IHttpReqRes.h"
#include "HttpStructData.h"

class HttpIfCanIdentify : public IHttpReqRes
{
	Q_OBJECT

public:
	explicit HttpIfCanIdentify(QString sysNo, InterfaceInputHead header);
	~HttpIfCanIdentify();

protected:
	void processResponse(QString strResult);
	void processError();

private:
	QString createJsonStr(QString sysNo, InterfaceInputHead header, QString funId, QString sysCode);
};

#endif // HTTPIFCANIDENTIFY_H
