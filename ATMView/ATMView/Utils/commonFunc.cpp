/***********************************************************************************
*								commonFunc.cpp
*
* Copyright(C):	智慧眼科技股份有限公司
*
* Author:  YCL
*
* Date: 2019-06
*
* Description: 通用功能函数
***********************************************************************************/

#include <QApplication>
#include <QDesktopWidget>

#include "commonFunc.h"

QRect CommonFunc::getScreenInfo()
{
	QDesktopWidget *desktop = QApplication::desktop();
	return desktop->screenGeometry();
}

QString CommonFunc::handleIdCardInfo( QString idCard )
{
	QString newIdCard;
	if (idCard.length() == 18)
	{
		newIdCard = idCard.replace(6, 8, "********");
	}
	return newIdCard;
}
