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
	//��ʼ����
	int readCard();
	//�߳�����
	virtual void run();

signals:
	//�����ɹ�
	void readSuccessed(AuthReadCardResult readCardResult);
    //����ʧ��
	void readFailed(int errCode);

private:
	AuthReadCardResult m_readCardResult;
	ReadCardType m_cardReader_type;
};

#endif // READIDCARDTHREAD_H
