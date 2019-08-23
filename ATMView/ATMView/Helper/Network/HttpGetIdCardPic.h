#ifndef HTTPGETIDCARDPIC_H
#define HTTPGETIDCARDPIC_H

#include <QObject>
#include "IHttpReqRes.h"
#include "HttpStructData.h"

class HttpGetIdCardPic : public IHttpReqRes
{
	Q_OBJECT

public:
	explicit HttpGetIdCardPic(IdCardPicData idCardPicData, InterfaceInputHead header);
	~HttpGetIdCardPic();

protected:
	void processResponse(QString strResult);
	void processError();

private:
	QString createJsonStr(IdCardPicData idCardPicData, InterfaceInputHead header, QString funId, QString sysCode);
};

#endif // HTTPGETIDCARDPIC_H
