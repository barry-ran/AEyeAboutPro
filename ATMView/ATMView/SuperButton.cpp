/***********************************************************************************
*								SuperButton.cpp
*
* Copyright(C):	智慧眼科技股份有限公司
*
* Author:  YCL
*
* Date: 2019-06
*
* Description: 通用按钮实例
***********************************************************************************/

#include "SuperButton.h"

SuperButton::SuperButton(QWidget *parent)
	: QPushButton(parent)
{
	ui.setupUi(this);
}

SuperButton::~SuperButton()
{

}

void SuperButton::InitButton( QString buttonName, QString buttonIcon, QString stylesheet )
{
	ui.lbl_name->setText(buttonName);
	ui.lbl_icon->setPixmap(QPixmap::fromImage(QImage(buttonIcon)));
	setStyleSheet(stylesheet);
}

void SuperButton::setIconSize( int width, int height )
{
	ui.lbl_icon->setFixedSize(width, height);
}
