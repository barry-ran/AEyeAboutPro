#ifndef HTTPCOMPLETEIDENTIFY_H
#define HTTPCOMPLETEIDENTIFY_H

#include <QObject>
#include "IHttpReqRes.h"
#include "HttpStructData.h"

class HttpCompleteIdentify : public IHttpReqRes
{
	Q_OBJECT

public:
	explicit HttpCompleteIdentify(CompleteIdentifyData completeIdentifyData, InterfaceInputHead header);
	~HttpCompleteIdentify();

protected:
	void processResponse(QString strResult);
	void processError();

private:
	QString createJsonStr(CompleteIdentifyData completeIdentifyData, InterfaceInputHead header, QString funId, QString sysCode);
};

#endif // HTTPCOMPLETEIDENTIFY_H
