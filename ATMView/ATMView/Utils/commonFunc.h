#pragma once
#include <QString>
#include <QStringList>
#include "HttpStructData.h"

class CommonFunc
{
public:
	//获取屏幕分辨率
	static QRect getScreenInfo();
	//身份证信息处理
	static QString handleIdCardInfo(QString idCard);
};

