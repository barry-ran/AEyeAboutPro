#ifndef SUPERBUTTON_H
#define SUPERBUTTON_H

#include <QPushButton>
#include "ui_SuperButton.h"

class SuperButton : public QPushButton
{
	Q_OBJECT

public:
	SuperButton(QWidget *parent = 0);
	~SuperButton();

	void InitButton(QString buttonName, QString buttonIcon, QString stylesheet);
	void setIconSize(int width, int height);
private:


private:
	Ui::SuperButton ui;
};

#endif // SUPERBUTTON_H
