#pragma once
#include <QString>
#include <QStringList>
#include "HttpStructData.h"

class CommonFunc
{
public:
	//��ȡ��Ļ�ֱ���
	static QRect getScreenInfo();
	//���֤��Ϣ����
	static QString handleIdCardInfo(QString idCard);
};

