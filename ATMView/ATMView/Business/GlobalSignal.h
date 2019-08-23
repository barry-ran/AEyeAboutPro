#ifndef GLOBALSIGNAL_H
#define GLOBALSIGNAL_H

#include <QObject>

class GlobalSignal : public QObject
{
	Q_OBJECT

public:
	static GlobalSignal* instance();

signals:
	void onButtonActivateOn();

private:
	explicit GlobalSignal(QObject *parent = 0);
	~GlobalSignal();

private:
	static GlobalSignal* m_pInstance;
};

#endif // GLOBALSIGNAL_H
