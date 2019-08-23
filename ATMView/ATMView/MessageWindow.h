#pragma once

#include "MaskWindow.h"

class QPushButton;
class QLabel;
class QShowEvent;
class QLineEdit;
class MessageWindow : public MaskWindow
{
	Q_OBJECT
public:
    enum MessageType
    {
        Information,
        Question,
        Warning,
        Error
    };

	MessageWindow(MessageType type = Information, QWidget *parent = 0);
	virtual ~MessageWindow();

    void setText(QString text);
    void setAutoCloseTimeout(int timeout);

public slots:
    void finish();

protected:
    void showEvent(QShowEvent *);

private:
    QWidget* createCentralWidget();
    QPixmap getIconPixmap();

private:
	QLabel* m_textLabel;      //授权码提示标签
    int m_autoCoseTimeout;
    MessageType m_messageType;
};