/***********************************************************************************
*								MaskWindow.cpp
*
* Copyright(C):	北京智慧眼科技股份有限公司
*
* Author:  HJM,TZH
*
* Date: 2018-12
*
* Description: 可用来被其它窗口继承的通用类的实现
***********************************************************************************/
#include "MaskWindow.h"
#include <QPainter>
#include <QPaintEvent>
#include <QVBoxLayout>
#include "commonFunc.h"

MaskWindow::MaskWindow(QWidget *parent)
    : QDialog(parent)
{
	QRect rect = CommonFunc::getScreenInfo();
    setFixedSize(rect.width(), rect.height());
    setWindowFlags(Qt::FramelessWindowHint);
    setAutoFillBackground(true);
    setStyleSheet("background:transparent;");
    setAttribute(Qt::WA_TranslucentBackground);
}

void MaskWindow::setCentralWidget( QWidget* centralWidget )
{
    QVBoxLayout* layout = new QVBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(centralWidget, 0, Qt::AlignCenter);
    setLayout(layout);
}

MaskWindow::~MaskWindow()
{

}

void MaskWindow::paintEvent(QPaintEvent *p)
{
    QPainter painter(this);
    painter.fillRect(0, 0, width(), height(), QColor(0, 0, 0, 180));
}
