#ifndef READIDCARDTHREAD_H
#define READIDCARDTHREAD_H

#include <QObject>
#include <QThread>
#include "HttpStructData.h"
#include "EnumData.h"

class ReadCardThread : public QThread
{
	Q_OBJECT

public:
	ReadCardThread(ReadCardType type, QObject *parent);
	~ReadCardThread();

protected:
	//开始读卡
	int readCard();
	//线程启动
	virtual void run();

signals:
	//读卡成功
	void readSuccessed(AuthReadCardResult readCardResult);
    //读卡失败
	void readFailed(int errCode);

private:
	AuthReadCardResult m_readCardResult;
	ReadCardType m_cardReader_type;
};

#endif // READIDCARDTHREAD_H
