/***********************************************************************************
*								SystemSettingsDlg.cpp
*
* Copyright(C):	智慧眼科技股份有限公司
*
* Author:  YCL
*
* Date: 2019-06
*
* Description: 用户配置窗口实例
***********************************************************************************/

#include "SystemSettingsDlg.h"
#include "SuperButton.h"
#include "UserConfig.h"
#include "MessageWindow.h"
#include "SystemChecker.h"

#include <QDateTime>

SystemSettingsDlg::SystemSettingsDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Window);
	showFullScreen();

	InitUI();
	InitConnect();
}

SystemSettingsDlg::~SystemSettingsDlg()
{

}

void SystemSettingsDlg::InitUI()
{
	QString commonStyle = "QLabel{font-size:14px;color:white;} QPushButton{background:rgb(0, 144, 216);border-radius:4px;}";
	m_exitBtn = new SuperButton(this);
	m_exitBtn->InitButton(QStringLiteral("退出程序"), ":/AIOViewer/Resources/exit.png", commonStyle);
	m_exitBtn->setFixedSize(100, 100);
	m_exitBtn->move(width() - 100, ui.wgt_title->height() + 60);
	m_exitBtn->show();

	m_minBtn = new SuperButton(this);
	m_minBtn->InitButton(QStringLiteral("返回桌面"), ":/AIOViewer/Resources/min.png", commonStyle);
	m_minBtn->setFixedSize(100, 100);
	m_minBtn->move(m_exitBtn->x(), m_exitBtn->y() + m_exitBtn->height() + 12);
	m_minBtn->show();

	m_rebootBtn = new SuperButton(this);
	m_rebootBtn->InitButton(QStringLiteral("重新启动"), ":/AIOViewer/Resources/reboot.png", commonStyle);
	m_rebootBtn->setFixedSize(100, 100);
	m_rebootBtn->move(m_minBtn->x(), m_minBtn->y() + m_minBtn->height() + 12);
	m_rebootBtn->show();

	commonStyle = "QLabel{font-size:14px;color:white;} QPushButton{background:rgb(254, 84, 0);border-radius:4px;}";
	m_shutdownBtn = new SuperButton(this);
	m_shutdownBtn->InitButton(QStringLiteral("关闭终端"), ":/AIOViewer/Resources/shutdown.png", commonStyle);
	m_shutdownBtn->setFixedSize(100, 100);
	m_shutdownBtn->move(m_rebootBtn->x(), m_rebootBtn->y() + m_rebootBtn->height() + 12);
	m_shutdownBtn->show();
}

void SystemSettingsDlg::InitConnect()
{
	connect(ui.btn_cancel, SIGNAL(clicked()), this, SLOT(close()));
	connect(ui.btn_commit, SIGNAL(clicked()), this, SLOT(onCommit()));
	connect(m_exitBtn, SIGNAL(clicked()), this, SLOT(onExitApp()));
	connect(m_minBtn, SIGNAL(clicked()), this, SLOT(onToDesktop()));
	connect(m_rebootBtn, SIGNAL(clicked()), this, SLOT(onReboot()));
	connect(m_shutdownBtn, SIGNAL(clicked()), this, SLOT(onShutdown()));
	connect(ui.lineEdit_ser, SIGNAL(returnPressed()), this, SLOT(onEditingFinished()));
}

void SystemSettingsDlg::load()
{
	ui.lbl_devNo->setText(INSTANCE_USER_CONFIG->getDeviceCode());
	ui.lbl_verNo->setText(INSTANCE_USER_CONFIG->getVersion());
	ui.lbl_timeNo->setText(QDateTime::currentDateTime().toString("hh:mm:ss"));
	ui.lbl_ser->setText(INSTANCE_USER_CONFIG->getServerDefaultUrl());
	ui.lineEdit_ser->setText(INSTANCE_USER_CONFIG->getServerDefaultUrl());
	ui.lineEdit_devIn->setText(INSTANCE_USER_CONFIG->getDeviceCode());
}

void SystemSettingsDlg::onCommit()
{
	if (SystemChecker::isSystemDefKeyBoardInstanceExisted)
	{
		SystemChecker::shutdownSystemDefKeyBoardInstance();
	}

	INSTANCE_USER_CONFIG->setServerDefaultUrl(ui.lineEdit_ser->text());
	ui.lbl_ser->setText(INSTANCE_USER_CONFIG->getServerDefaultUrl());
	INSTANCE_USER_CONFIG->setDeviceCode(ui.lineEdit_devIn->text());
	ui.lbl_devNo->setText(INSTANCE_USER_CONFIG->getDeviceCode());

	MessageWindow msgWindow(MessageWindow::Information, this);
	msgWindow.setText(QStringLiteral("提交成功！"));
	msgWindow.exec();
	this->close();
}

void SystemSettingsDlg::onReboot()
{
	system("shutdown -r -f -t 0");
}

void SystemSettingsDlg::onShutdown()
{
	system("shutdown -s -f -t 0");
}

void SystemSettingsDlg::onExitApp()
{
	SystemChecker::shutdownLauncherInstance();
	QCoreApplication::exit(0);
}

void SystemSettingsDlg::onToDesktop()
{
	emit sigOnToDesktop();
	close();
}