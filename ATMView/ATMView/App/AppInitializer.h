#pragma once

#include <QStringList>
#include <QObject>

class AppInitializer : public QObject
{
	Q_OBJECT
public:
    AppInitializer(QObject *parent = 0);
    ~AppInitializer(void);

	/*应用程序初始化*/
    void init(QStringList appArgs);			

private:
	/*处理App命令行参数*/
    void handleAppArgs(QStringList args);

	/*单例初始化*/
	void initSingleObjects();

	/*初始化日志库*/
    void initLog();	

	/*配置文件初始化*/
    void initConfig();	

	/*初始化软键盘，现改成系统默认键盘*/
	void initSoftKeyboard();

	/*监测应用程序临时文件存放目录*/
    void checkDataDirs();

	/*清除过期日志*/
    void clearOutdatedLogs();

private slots:

	/*检查启动器进程*/
    void checkLauncherProcess();
};

