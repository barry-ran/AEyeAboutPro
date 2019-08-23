#pragma once

#include "MaskWindow.h"

class QPushButton;
class QLabel;
class QLineEdit;
class LoadingWindow : public MaskWindow
{
	Q_OBJECT
public:
	LoadingWindow(QWidget *parent = 0);
	virtual ~LoadingWindow();

    void setText(QString text);

public slots:
    void finish();

private:
    QWidget* createCentralWidget();

private:
	QLabel* m_textLabel;      //授权码提示标签
};