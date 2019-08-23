/***********************************************************************************
*								AuthorizateDlg.cpp
*
* Copyright(C):	智慧眼科技股份有限公司
*
* Author:  YCL
*
* Date: 2019-06
*
* Description: 授权窗口实例
***********************************************************************************/

#include "AuthorizateDlg.h"
#include "CameraReader.h"
#include "UserConfig.h"
#include "GlogManager.h"
#include "SystemChecker.h"

AuthorizateDlg::AuthorizateDlg(QWidget *parent)
	: MaskWindow(parent)
{
	ui.setupUi(this);
	setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint | Qt::Window);
	showFullScreen();

	InitUI();
	InitConnect();
}

AuthorizateDlg::~AuthorizateDlg()
{

}

void AuthorizateDlg::InitUI()
{
	ui.lineEdit->setEchoMode(QLineEdit::Password);
	ui.lineEdit->setFocus();
}

void AuthorizateDlg::InitConnect()
{
	connect(ui.btn_back, SIGNAL(clicked()), this, SLOT(close()));
	connect(ui.btn_login, SIGNAL(clicked()), this, SLOT(onAuthorizate()));
}

void AuthorizateDlg::onAuthorizate()
{
	if (SystemChecker::isSystemDefKeyBoardInstanceExisted())
	{
		SystemChecker::shutdownSystemDefKeyBoardInstance();
	}

	if (ui.lineEdit->text().isEmpty())
	{
		LOG(INFO)<<"授权码输入为空！";
	}

	if (ui.lineEdit->text() == INSTANCE_USER_CONFIG->getAuthCode())
	{
		emit sigOnAuthorizateFinished();
	}
	else
	{
		ui.lineEdit->clear();
	}
}

void AuthorizateDlg::load()
{
	ui.lineEdit->clear();
}