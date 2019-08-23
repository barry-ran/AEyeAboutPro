#ifndef AUTHORIZATEDLG_H
#define AUTHORIZATEDLG_H

#include "MaskWindow.h"
#include "ui_AuthorizateDlg.h"

class AuthorizateDlg : public MaskWindow
{
	Q_OBJECT

public:
	AuthorizateDlg(QWidget *parent = 0);
	~AuthorizateDlg();

	void load();
signals:
	//ÊÚÈ¨Íê³É
	void sigOnAuthorizateFinished();

private slots:
	void onAuthorizate();

private:
	void InitUI();
	void InitConnect();

private:
	Ui::AuthorizateDlg ui;
};

#endif // AUTHORIZATEDLG_H
