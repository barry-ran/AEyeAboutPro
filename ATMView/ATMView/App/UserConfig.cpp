/***********************************************************************************
*								UserConfig.cpp
*
* Copyright(C):	智慧眼科技股份有限公司
*
* Author:  YCL
*
* Date: 2019-06
*
* Description: 用户配置文件管理器实现
***********************************************************************************/

#include <Windows.h>
#include <QSettings>
#include <QTextCodec>

#include "UserConfig.h"
#include "FileManager.h"
#include "DataPathManager.h"
#include "SystemChecker.h"

UserConfig::UserConfig()
{
	m_configPath = QString::fromStdString(DataPathManager::getUserDir()) + "\\config.ini";
	m_ConfigIni = new QSettings(m_configPath, QSettings::IniFormat);
	m_ConfigIni->setIniCodec(QTextCodec::codecForName("GB2312"));
}

UserConfig::~UserConfig()
{

}

UserConfig* UserConfig::getInstance()
{
	static UserConfig instance;
	return &instance;
}

void UserConfig::loadSectionbasic()
{
	m_version = m_ConfigIni->value("basic/version").toString();     //版本号
	m_authCode = m_ConfigIni->value("basic/authCode").toString();   //授权码
	m_operatorUserId = m_ConfigIni->value("basic/userId").toString();
	m_operatorPasswd = m_ConfigIni->value("basic/passwd").toString();
}

void UserConfig::loadSectionUrl()
{
	m_defaultUrl = m_ConfigIni->value("url/defaultUrl").toString();    //服务器地址
}

void UserConfig::loadDeviceInfo()
{
	m_deviceCode = m_ConfigIni->value("device/devicecode").toString();    //设备编码

	QString currentMac = m_ConfigIni->value("device/mac").toString();     //mac地址
	if (currentMac.isEmpty())
	{
		currentMac = SystemChecker::getCurrentMacAddr();
		m_ConfigIni->setValue("device/mac", currentMac);
	}
	m_mac = currentMac;
}

void UserConfig::load()
{
    loadSectionbasic();
    loadSectionUrl();
    loadDeviceInfo();
}

QString UserConfig::getMac()
{
	return m_mac;
}

QString UserConfig::getServerDefaultUrl()
{
	return m_defaultUrl; 
}

QString UserConfig::getDeviceCode() 
{
	return m_deviceCode; 
}

QString UserConfig::getVersion() 
{ 
	return m_version; 
}

QString UserConfig::getAuthCode() 
{ 
	return m_authCode; 
}

void UserConfig::setVersion(QString version)
{
	if (!version.isEmpty()) {
		m_ConfigIni->setValue("basic/version", version);
		m_version = version;
	}
}

void UserConfig::setServerDefaultUrl(QString serverUrl)
{
	m_ConfigIni->setValue("url/defaultUrl", serverUrl);
    m_defaultUrl = serverUrl;
}

void UserConfig::setAuthCode(QString authCode)
{
	if (!authCode.isEmpty()) {
		m_ConfigIni->setValue("basic/authCode", authCode);
		m_authCode = authCode;
	}
}

void UserConfig::setDeviceCode(QString deviceCode)
{
	if (!deviceCode.isEmpty()) {
		m_ConfigIni->setValue("device/devicecode", deviceCode);
		m_deviceCode = deviceCode;
	}
}

void UserConfig::setOperatorInfo( QString userId, QString passwd )
{
	m_ConfigIni->setValue("basic/userId", userId);
	m_ConfigIni->setValue("basic/passwd", passwd);
	m_operatorUserId = userId;
	m_operatorPasswd = passwd;
}

void UserConfig::getOperatorInfo( QString& userId, QString& passwd )
{
	userId = m_operatorUserId;
	passwd = m_operatorPasswd;
}
