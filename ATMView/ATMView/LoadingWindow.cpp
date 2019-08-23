/***********************************************************************************
*								LoadingWindow.cpp
*
* Copyright(C):	北京智慧眼科技股份有限公司
*
* Author:  HJM,TZH
*
* Date: 2018-12
*
* Description: 显示一个加载窗口，以提示用户
***********************************************************************************/
#include "LoadingWindow.h"
#include <QPainter>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QFont>
#include <QFrame>

#include "ProgressIndicator.h"

LoadingWindow::LoadingWindow(QWidget *parent) 
    : MaskWindow(parent)
{
    setCentralWidget(createCentralWidget());
    setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint |	Qt::Window);
	showFullScreen();
}

LoadingWindow::~LoadingWindow()
{
}

QWidget* LoadingWindow::createCentralWidget()
{
    ProgressIndicator* indicator = new ProgressIndicator();
    indicator->startAnimation();
    indicator->setAnimationDelay(80);

    QFont labelFont;
    labelFont.setPixelSize(28);

    m_textLabel = new QLabel();
    m_textLabel->setFont(labelFont);
    m_textLabel->setStyleSheet("color: grey;");
    m_textLabel->setAlignment(Qt::AlignCenter);

	QVBoxLayout* layout = new QVBoxLayout();
	layout->setSpacing(20);
    layout->setContentsMargins(20, 20, 20, 20);
	
    layout->addSpacing(50);
    layout->addWidget(indicator, 0, Qt::AlignCenter);
    layout->addStretch();
    layout->addWidget(m_textLabel, 0, Qt::AlignCenter);
	layout->addStretch();

    QFrame* centralWidget = new QFrame;
    centralWidget->setLayout(layout);
    centralWidget->setObjectName("LoadingCentralWidget");
    centralWidget->setStyleSheet("QFrame#LoadingCentralWidget{border:none; border-radius:10px; background-color: white;}");
    centralWidget->setFixedSize(500, 320);
    return centralWidget;
}

void LoadingWindow::setText( QString text )
{
    m_textLabel->setText(text);
    update();
}

void LoadingWindow::finish()
{
    close();
}
