#ifndef ARROWWIDGET_H
#define ARROWWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QGraphicsEffect>

const int SHADOW_WIDTH = 15;         //阴影宽度
const int TRIANGLE_WIDTH = 15;       //小三角形宽
const int TRIANGLE_HEIGHT = 10;      //小三角形高
const int BORDER_RADIUS = 5;         //边缘弧度

class ArrowWidget : public QWidget
{
	Q_OBJECT

public:
	ArrowWidget(QWidget *parent = 0);
	~ArrowWidget();

	//小三角显示位置
	enum Derection{
		left,
		right,
		up,
		down
	};

	QGraphicsDropShadowEffect* m_showEffect;
	QLabel* m_lbl_text;

	//设置三角形的起始位置
	void setStartPos(int startX);
	//设置三角形的宽和高
	void setTriangleInfo(int width, int height);

	void setText(QString text);
	QString text() const;

	void setDerection(Derection d);

protected:
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);

private:
	//小三角形起始位置
	int m_startX;
	//小三角形的宽度
	int m_triangleWidth;
	//小三角形的高度
	int m_triangleHeight;
	//小三角形的显示位置
	Derection m_derect;
};

#endif // ARROWWIDGET_H
