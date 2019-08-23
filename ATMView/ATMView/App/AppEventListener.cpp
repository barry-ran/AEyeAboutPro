/***********************************************************************************
*								AppEventListener.cpp
*
* Copyright(C):	�����ǻ��ۿƼ��ɷ����޹�˾
*
* Author:  HJM,TZH
*
* Date: 2018-12
*
* Description: ��������App�¼���⣬���û������
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
	if(event->type() == QEvent::MouseButtonPress) {      //App�¼�������������û��Ƿ���Ҫ���룬������ϵͳĬ�����뷨
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