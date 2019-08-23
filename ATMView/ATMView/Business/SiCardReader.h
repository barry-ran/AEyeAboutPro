#ifndef SICARDREADER_H
#define SICARDREADER_H

#include <QObject>
#include "HttpStructData.h"

class SiCardReader : public QObject
{
	Q_OBJECT

public:
	static SiCardReader* instance();

	//∂¡»°ø®–≈œ¢
	int read(AuthReadCardResult& readCardResult);
private:
	explicit SiCardReader(QObject *parent = 0);
	~SiCardReader();

private:
	static SiCardReader* m_pInstance;
};

#endif // SICARDREADER_H
