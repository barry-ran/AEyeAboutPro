#ifndef IDCARDREADER_H
#define IDCARDREADER_H

#include <QObject>
#include "HttpStructData.h"

#define MAX_HD900_IDCARD_USBPORT  8

class IdCardReader : public QObject
{
	Q_OBJECT

public:
	static IdCardReader* instance();
	
	//∂¡»°ø®–≈œ¢
	int read(AuthReadCardResult& readCardResult);
private:
	explicit IdCardReader(QObject *parent = 0);
	~IdCardReader();

private:
	static IdCardReader* m_pInstance;
};

#endif // IDCARDREADER_H
