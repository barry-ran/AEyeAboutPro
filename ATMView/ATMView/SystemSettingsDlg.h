#ifndef SYSTEMSETTINGSDLG_H
#define SYSTEMSETTINGSDLG_H

#include <QDialog>
#include "ui_SystemSettingsDlg.h"

class SuperButton;
class SystemSettingsDlg : public QDialog
{
	Q_OBJECT

public:
	SystemSettingsDlg(QWidget *parent = 0);
	~SystemSettingsDlg();

	void load();

signals:
	void sigOnToDesktop();

private:
	void InitUI();
	void InitConnect();

private slots:
	void onCommit();
	void onReboot();
	void onShutdown();
	void onExitApp();
	void onToDesktop();

private:
	Ui::SystemSettingsDlg ui;
	SuperButton* m_exitBtn;         //�˳���ť
	SuperButton* m_minBtn;          //��С����ť
	SuperButton* m_rebootBtn;       //������ť
	SuperButton* m_shutdownBtn;     //�ػ���ť
};

#endif // SYSTEMSETTINGSDLG_H
