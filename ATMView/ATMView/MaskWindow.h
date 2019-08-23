#ifndef TRANSLUCENTWINDOW_H
#define TRANSLUCENTWINDOW_H

#include <QDialog>

class QPaintEvent;
class MaskWindow : public QDialog
{
    Q_OBJECT

public:
    MaskWindow(QWidget *parent = 0);
    ~MaskWindow();

    void setCentralWidget(QWidget* centralWidget);

protected:
    virtual void paintEvent(QPaintEvent *p);
};

#endif // TRANSLUCENTWINDOW_H
