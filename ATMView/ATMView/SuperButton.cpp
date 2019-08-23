/***********************************************************************************
*								SuperButton.cpp
*
* Copyright(C):	�ǻ��ۿƼ��ɷ����޹�˾
*
* Author:  YCL
*
* Date: 2019-06
*
* Description: ͨ�ð�ťʵ��
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
