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

    //////////////////////// config�����ļ� ////////////////////////
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

	/*����ͨ�õ��ֶ���Ϣ����汾�ţ���Ȩ��*/
    void loadSectionbasic();

	/*���ط�������ַ�����Ϣ*/
    void loadSectionUrl();

	/*�����豸����Ϣ*/
    void loadDeviceInfo();
	
private:
	QString m_configPath;
	QSettings* m_ConfigIni;
	
    //////////////////////// config�����ļ� ////////////////////////
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