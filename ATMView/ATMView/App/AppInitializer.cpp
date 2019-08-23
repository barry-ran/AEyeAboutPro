/***********************************************************************************
*								AppInitializer.cpp
*
* Copyright(C):	北京智慧眼科技股份有限公司
*
* Author:  HJM,TZH
*
* Date: 2018-12
*
* Description: 用于进程启动时的一些初始化操作
***********************************************************************************/
#include "AppInitializer.h"
#include <QMetaType>
#include <string>
#include <QDateTime>
#include <QDir>
#include <QTimer>
#include "UserConfig.h"
#include "GlogManager.h"
#include "DataPathManager.h"
#include "FileManager.h"
#include "SystemChecker.h"

AppInitializer::AppInitializer(QObject *parent) : QObject(parent)
{
}


AppInitializer::~AppInitializer(void)
{
}

void AppInitializer::handleAppArgs( QStringList args )
{
    if (args.count() > 1) {  //从命令行获取新的版本
        QString strAppVer = args.at(1);
        QString strTemp = strAppVer;
        strTemp.remove('.');
        if (strAppVer.length() - 2 == strTemp.length()) {
            INSTANCE_USER_CONFIG->setVersion(strAppVer);
        }
    }
}

void AppInitializer::initLog()
{
    //清除过期日志
	clearOutdatedLogs();

    //日志系统初始化
	INSTANCE_GLOG_MANAGER->init();
    INSTANCE_GLOG_MANAGER->setLogFileDir(DataPathManager::getLogDirPath().c_str());
    INSTANCE_GLOG_MANAGER->setInfoLogPrefix("Info");
    INSTANCE_GLOG_MANAGER->setWarningLogPrefix("Warnig");
    INSTANCE_GLOG_MANAGER->setErrorLogPrefix("Error");
    INSTANCE_GLOG_MANAGER->setMaxLogSize(5);
    INSTANCE_GLOG_MANAGER->setStopLoggingIfFullDisk(true);
    INSTANCE_GLOG_MANAGER->setLogbufCacheTime(0);
}

void AppInitializer::initConfig()
{
    //加载配置信息
	INSTANCE_USER_CONFIG->load();
}

void AppInitializer::init(QStringList appArgs)
{
    //初始化
	handleAppArgs(appArgs);
	initSingleObjects();
    initLog();
    initConfig();
	initSoftKeyboard();
    checkDataDirs();
    clearOutdatedLogs();

	QTimer::singleShot(5000,this,SLOT(checkLauncherProcess()));
}

void AppInitializer::checkDataDirs()
{
    //创建相应的文件夹
	QString logsDirPath = QString::fromLocal8Bit(DataPathManager::getLogDirPath().c_str()); 
	QString dumpDirPath = QString::fromLocal8Bit(DataPathManager::getDumpDirPath().c_str());
    FileManager::createDir(logsDirPath);
	FileManager::createDir(dumpDirPath);
}

void AppInitializer::clearOutdatedLogs()
{
    //清除过期的日志信息
	QString logsDir = QString::fromLocal8Bit(DataPathManager::getLogDirPath().c_str()); 
    QDir dir(logsDir);
    if (dir.exists()) {
        dir.setFilter(QDir::Files); 
        int currentDate = QDateTime::currentDateTime().toString("yyyyMMdd").toInt(); 
        foreach (QFileInfo mfi ,dir.entryInfoList()) {
            int logDate = mfi.fileName().mid(4, 8).toInt(); 
            if (currentDate - logDate > 7) { //删除1个星期前的日志
                if (!QFile::remove(logsDir + "\\" + mfi.fileName())){
					LOG(ERROR)<<"移除日志文件失败!";
				}
            }
        }
    }
	else{
		LOG(ERROR)<<"应用日志目录不存在!";
	}
}

void AppInitializer::checkLauncherProcess()
{
    //检测启动器进程
	if (!SystemChecker::isLauncherInstanceExisted()) {
        LOG(WARNING) << "未检测到ATMLaunch进程";
        if (!SystemChecker::restartLauncherInstance()) {
            LOG(ERROR) << "ATMLaunch启动失败";
        } else {

        }
    }
}

void AppInitializer::initSingleObjects()
{
	//实例化单例
	INSTANCE_USER_CONFIG;
	INSTANCE_GLOG_MANAGER;
}

void AppInitializer::initSoftKeyboard()
{

}
