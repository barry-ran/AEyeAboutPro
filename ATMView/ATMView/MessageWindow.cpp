/***********************************************************************************
*								MessageWindow.cpp
*
* Copyright(C):	北京智慧眼科技股份有限公司
*
* Author:  HJM,TZH
*
* Date: 2018-12
*
* Description: 消息提示窗口
***********************************************************************************/
#include "MessageWindow.h"
#include <QPainter>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QFont>
#include <QFrame>
#include <QTimer>
#include <QPixmap>

#include "GlogManager.h"
#include "UserConfig.h"

MessageWindow::MessageWindow(MessageType type, QWidget *parent) 
    : MaskWindow(parent)
    , m_messageType(type)
    , m_autoCoseTimeout(-1)
{
    setCentralWidget(createCentralWidget());
    setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint | Qt::Window);
	showFullScreen();
}

MessageWindow::~MessageWindow()
{
}

QWidget* MessageWindow::createCentralWidget()
{
    QFont labelFont;
    labelFont.setPixelSize(28);

    QLabel* titleLabel = new QLabel();
    titleLabel->setFont(labelFont);
    titleLabel->setStyleSheet("color: grey;");
    titleLabel->setText(QStringLiteral("消 息"));
    titleLabel->setAlignment(Qt::AlignCenter);

    QPixmap closePixmap(":/AIOViewer/Resources/btn_close.png");
    QPushButton* closeButton = new QPushButton();
    closeButton->setStyleSheet("border: none; border-image: url(:/AIOViewer/Resources/btn_close.png)");
    closeButton->setFixedSize(closePixmap.width(), closePixmap.height());
    connect(closeButton, SIGNAL(clicked()), this, SLOT(reject()));

    QHBoxLayout* topLayout = new QHBoxLayout;
    topLayout->setContentsMargins(0, 0, 0, 0);
    topLayout->addSpacing(closeButton->width());
    topLayout->addStretch();
    topLayout->addWidget(titleLabel);
    topLayout->addStretch();
    topLayout->addWidget(closeButton);

    QPixmap pixmap = getIconPixmap();
    QLabel* iconLabel = new QLabel;
    iconLabel->setPixmap(pixmap);
    iconLabel->setFixedSize(pixmap.size());

    m_textLabel = new QLabel();
    m_textLabel->setFont(labelFont);
    m_textLabel->setStyleSheet("color: grey;");
    m_textLabel->setAlignment(Qt::AlignCenter);
	m_textLabel->setFixedWidth(600 - 40);
	m_textLabel->adjustSize();
	m_textLabel->setWordWrap(true);

	QVBoxLayout* layout = new QVBoxLayout();
	layout->setSpacing(20);
    layout->setContentsMargins(20, 20, 20, 20);
	
    layout->addLayout(topLayout);
    layout->addStretch();
    layout->addWidget(iconLabel, 0, Qt::AlignCenter);
    layout->addSpacing(40);
    layout->addWidget(m_textLabel, 0, Qt::AlignCenter);
	layout->addStretch();

    QFrame* centralWidget = new QFrame;
    centralWidget->setLayout(layout);
    centralWidget->setObjectName("LoadingCentralWidget");
    centralWidget->setStyleSheet("QFrame#LoadingCentralWidget{border:none; border-radius:10px; background-color: white;}");
    centralWidget->setFixedSize(600, 400);
    return centralWidget;
}

void MessageWindow::setText( QString text )
{
    m_textLabel->setText(text);
    update();
}

void MessageWindow::finish()
{
    close();
}

void MessageWindow::showEvent( QShowEvent * e)
{
    MaskWindow::showEvent(e);
    QTimer::singleShot(m_autoCoseTimeout * 1000, this, SLOT(accept()));
}

void MessageWindow::setAutoCloseTimeout( int timeout )
{
    if (timeout > 0) {
        m_autoCoseTimeout = timeout;
    }
}

QPixmap MessageWindow::getIconPixmap()
{
    QString path;
    switch (m_messageType) {
    case Information:
        path = ":/AIOViewer/Resources/lbl_msg_info.png";
        break;
    case Question:
        path = ":/AIOViewer/Resources/lbl_msg_question.png";
        break;
    case Warning:
        path = ":/AIOViewer/Resources/lbl_msg_warning.png";
        break;
    case Error:
        path = ":/AIOViewer/Resources/lbl_msg_error.png";
        break;
    }

    return QPixmap(path);
}
