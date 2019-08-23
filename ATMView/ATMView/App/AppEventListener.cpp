/***********************************************************************************
*								AppEventListener.cpp
*
* Copyright(C):	北京智慧眼科技股份有限公司
*
* Author:  HJM,TZH
*
* Date: 2018-12
*
* Description: 用于整个App事件监测，如用户输入等
***********************************************************************************/
#include "AppEventListener.h"
#include <QCoreApplication>
#include <QLineEdit>
#include <QMouseEvent>
#include <QCursor>
#include <QTimer>
#include <QDesktopWidget>
#include <QApplication>
#include <Windows.h>

#include "UserConfig.h"
#include "SystemChecker.h"
#include "GlobalSignal.h"

AppEventListener::AppEventListener(QObject *parent)
	: QObject(parent)
{
   
}

AppEventListener::~AppEventListener()
{

}

bool AppEventListener::eventFilter(QObject *obj, QEvent *event)
{	
	if(event->type() == QEvent::MouseButtonPress) {      //App事件过滤器，检测用户是否需要输入，并调用系统默认输入法
		if(obj->inherits("QLineEdit")) {
			QLineEdit* edit = qobject_cast<QLineEdit *>(obj);
			if(1 != edit->property("softKeybdDisabled")) {
				if (SystemChecker::isSystemDefKeyBoardInstanceExisted)
				{
					SystemChecker::shutdownSystemDefKeyBoardInstance();
				}
				SystemChecker::restartSystemDefKeyBoardInstance();
			}
		}
		else if (obj->inherits("QPushButton"))
		{
			GlobalSignal::instance()->onButtonActivateOn();
		}
	}	

	return false;
}