#pragma once

#include <QObject>
#include <QPoint>
#include <QTimer>

class QEvent;
class AppEventListener : public QObject
{
	Q_OBJECT

public:
	AppEventListener(QObject *parent = 0);
	~AppEventListener();

protected:
	virtual bool eventFilter(QObject *obj, QEvent *event);
};

