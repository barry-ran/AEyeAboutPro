#ifndef HTTPGETBASEINFO_H
#define HTTPGETBASEINFO_H

#include <QObject>
#include "IHttpReqRes.h"
#include "HttpStructData.h"

class HttpGetBaseInfo : public IHttpReqRes
{
	Q_OBJECT

public:
	explicit HttpGetBaseInfo(UserBaseInfo userBaseInfo, InterfaceInputHead header);
	~HttpGetBaseInfo();

protected:
	void processResponse(QString strResult);
	void processError();

private:
	QString createJsonStr(UserBaseInfo userBaseInfo, InterfaceInputHead header, QString funId, QString sysCode);
	void ModelPickerFunc(ModelStatus& modelStatus, int bioType, int modelType, int status);
};

#endif // HTTPGETBASEINFO_H
