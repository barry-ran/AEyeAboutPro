/***********************************************************************************
*								main.cpp
*
* Copyright(C):	�ǻ��ۿƼ��ɷ����޹�˾
*
* Author:  YCL
*
* Date: 2019-06
*
* Description: �������
***********************************************************************************/

#include "AIOViewer.h"
#include <QtWidgets/QApplication>
#include <QTextCodec>
#include <QFont>
#include <windows.h>
#include "dump.h"
#include "AppEnvChecker.h"
#include "AppInitializer.h"
#include "AppCleaner.h"
#include "GlogManager.h"
#include "AppEventListener.h"

int main(int argc, char *argv[])
{
	//��ʼ��Dump
	EnableAutoDump();

	QApplication a(argc, argv);

	//��������
	QFont font;
	font.setFamily(QString::fromLocal8Bit("΢���ź�"));
	a.setFont(font);

	//���ñ����ʽ
	QTextCodec *codec = QTextCodec::codecForName("GB2312");
	QTextCodec::setCodecForLocale(codec);

	//��黷�������Ƿ����ȣ�
	AppEnvChecker envChecker;
	if(!envChecker.check()) {      
		return -1;
	}

	//��ʼ��
	AppInitializer  initializer;
	initializer.init(a.arguments());
	LOG(INFO)<<"App ����.";

	//�����¼�����
	AppEventListener* listener = new AppEventListener;
	a.installEventFilter(listener);

	AIOViewer w;
	w.show();

	int ret = a.exec();
	LOG(INFO)<<"App �˳�.";

	//����
	AppCleaner cleaner;
	cleaner.clean();

	return ret;
}
