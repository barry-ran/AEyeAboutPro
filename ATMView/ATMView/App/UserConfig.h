#ifndef  __USERCONFIG_H__
#define  __USERCONFIG_H__

#include <QString>
#include <QSettings>

#define INSTANCE_USER_CONFIG UserConfig::getInstance()

class UserConfig
{
public:
	static UserConfig* getInstance();
	void load();

    //////////////////////// config配置文件 ////////////////////////
    //general 
    QString getVersion();
    QString getAuthCode();

    void setVersion(QString version);
    void setAuthCode(QString authCode);

	void getOperatorInfo(QString& userId, QString& passwd);
	void setOperatorInfo(QString userId, QString passwd);
    
    //url
    QString getServerDefaultUrl();
    void setServerDefaultUrl(QString serverUrl);

	//device
	QString getDeviceCode();
	QString getMac();

	void setDeviceCode(QString deviceCode);

private:
	UserConfig();
	virtual ~UserConfig();

	/*加载通用的字段信息，如版本号，授权码*/
    void loadSectionbasic();

	/*加载服务器地址相关信息*/
    void loadSectionUrl();

	/*加载设备码信息*/
    void loadDeviceInfo();
	
private:
	QString m_configPath;
	QSettings* m_ConfigIni;
	
    //////////////////////// config配置文件 ////////////////////////
    //general 
    QString m_version;
    QString m_authCode;
	QString m_operatorUserId;
	QString m_operatorPasswd;

    //url
    QString m_defaultUrl;

	//device
	QString m_deviceCode;
	QString m_mac;
};

#endif