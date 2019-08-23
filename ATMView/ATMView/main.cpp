/***********************************************************************************
*								main.cpp
*
* Copyright(C):	智慧眼科技股份有限公司
*
* Author:  YCL
*
* Date: 2019-06
*
* Description: 程序入口
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
	//初始化Dump
	EnableAutoDump();

	QApplication a(argc, argv);

	//设置字体
	QFont font;
	font.setFamily(QString::fromLocal8Bit("微软雅黑"));
	a.setFont(font);

	//设置编码格式
	QTextCodec *codec = QTextCodec::codecForName("GB2312");
	QTextCodec::setCodecForLocale(codec);

	//检查环境（如是否单例等）
	AppEnvChecker envChecker;
	if(!envChecker.check()) {      
		return -1;
	}

	//初始化
	AppInitializer  initializer;
	initializer.init(a.arguments());
	LOG(INFO)<<"App 启动.";

	//设置事件监听
	AppEventListener* listener = new AppEventListener;
	a.installEventFilter(listener);

	AIOViewer w;
	w.show();

	int ret = a.exec();
	LOG(INFO)<<"App 退出.";

	//清理
	AppCleaner cleaner;
	cleaner.clean();

	return ret;
}
