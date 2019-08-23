#ifndef HTTPOPERATORLOGIN_H
#define HTTPOPERATORLOGIN_H

#include <QObject>
#include "IHttpReqRes.h"
#include "HttpStructData.h"

class HttpOperatorLogin : public IHttpReqRes
{
	Q_OBJECT

public:
	explicit HttpOperatorLogin(OperatorInfo operatorInfo, InterfaceInputHead header);
	~HttpOperatorLogin();

protected:
	void processResponse(QString strResult);
	void processError();

private:
	QString createJsonStr(OperatorInfo operatorInfo, InterfaceInputHead header, QString funId, QString sysCode);
};

#endif // HTTPOPERATORLOGIN_H
