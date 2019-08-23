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
	SuperButton* m_exitBtn;         //退出按钮
	SuperButton* m_minBtn;          //最小化按钮
	SuperButton* m_rebootBtn;       //重启按钮
	SuperButton* m_shutdownBtn;     //关机按钮
};

#endif // SYSTEMSETTINGSDLG_H
