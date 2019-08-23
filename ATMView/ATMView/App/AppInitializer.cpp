/***********************************************************************************
*								AppInitializer.cpp
*
* Copyright(C):	�����ǻ��ۿƼ��ɷ����޹�˾
*
* Author:  HJM,TZH
*
* Date: 2018-12
*
* Description: ���ڽ�������ʱ��һЩ��ʼ������
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
    if (args.count() > 1) {  //�������л�ȡ�µİ汾
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
    //���������־
	clearOutdatedLogs();

    //��־ϵͳ��ʼ��
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
    //����������Ϣ
	INSTANCE_USER_CONFIG->load();
}

void AppInitializer::init(QStringList appArgs)
{
    //��ʼ��
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
    //������Ӧ���ļ���
	QString logsDirPath = QString::fromLocal8Bit(DataPathManager::getLogDirPath().c_str()); 
	QString dumpDirPath = QString::fromLocal8Bit(DataPathManager::getDumpDirPath().c_str());
    FileManager::createDir(logsDirPath);
	FileManager::createDir(dumpDirPath);
}

void AppInitializer::clearOutdatedLogs()
{
    //������ڵ���־��Ϣ
	QString logsDir = QString::fromLocal8Bit(DataPathManager::getLogDirPath().c_str()); 
    QDir dir(logsDir);
    if (dir.exists()) {
        dir.setFilter(QDir::Files); 
        int currentDate = QDateTime::currentDateTime().toString("yyyyMMdd").toInt(); 
        foreach (QFileInfo mfi ,dir.entryInfoList()) {
            int logDate = mfi.fileName().mid(4, 8).toInt(); 
            if (currentDate - logDate > 7) { //ɾ��1������ǰ����־
                if (!QFile::remove(logsDir + "\\" + mfi.fileName())){
					LOG(ERROR)<<"�Ƴ���־�ļ�ʧ��!";
				}
            }
        }
    }
	else{
		LOG(ERROR)<<"Ӧ����־Ŀ¼������!";
	}
}

void AppInitializer::checkLauncherProcess()
{
    //�������������
	if (!SystemChecker::isLauncherInstanceExisted()) {
        LOG(WARNING) << "δ��⵽ATMLaunch����";
        if (!SystemChecker::restartLauncherInstance()) {
            LOG(ERROR) << "ATMLaunch����ʧ��";
        } else {

        }
    }
}

void AppInitializer::initSingleObjects()
{
	//ʵ��������
	INSTANCE_USER_CONFIG;
	INSTANCE_GLOG_MANAGER;
}

void AppInitializer::initSoftKeyboard()
{

}
