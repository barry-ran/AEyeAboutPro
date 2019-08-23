#pragma once

#include <QStringList>
#include <QObject>

class AppInitializer : public QObject
{
	Q_OBJECT
public:
    AppInitializer(QObject *parent = 0);
    ~AppInitializer(void);

	/*Ӧ�ó����ʼ��*/
    void init(QStringList appArgs);			

private:
	/*����App�����в���*/
    void handleAppArgs(QStringList args);

	/*������ʼ��*/
	void initSingleObjects();

	/*��ʼ����־��*/
    void initLog();	

	/*�����ļ���ʼ��*/
    void initConfig();	

	/*��ʼ������̣��ָĳ�ϵͳĬ�ϼ���*/
	void initSoftKeyboard();

	/*���Ӧ�ó�����ʱ�ļ����Ŀ¼*/
    void checkDataDirs();

	/*���������־*/
    void clearOutdatedLogs();

private slots:

	/*�������������*/
    void checkLauncherProcess();
};

