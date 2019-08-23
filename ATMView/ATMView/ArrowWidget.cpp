/***********************************************************************************
*								ArrowWidget.cpp
*
* Copyright(C):	智慧眼科技股份有限公司
*
* Author:  YCL
*
* Date: 2019-06
*
* Description: 气泡弹窗实例
***********************************************************************************/

#include "ArrowWidget.h"
#include <QMouseEvent>
#include <QPaintEvent>
#include <QHBoxLayout>
#include <QPainter>

ArrowWidget::ArrowWidget(QWidget *parent)
	: QWidget(parent)
	, m_startX(50)
	, m_triangleWidth(TRIANGLE_WIDTH)
	, m_triangleHeight(TRIANGLE_HEIGHT)
{
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);

	//设置阴影边框
	m_showEffect = new QGraphicsDropShadowEffect(this);
	m_showEffect->setOffset(0, 0);
	m_showEffect->setColor(Qt::gray);
	m_showEffect->setBlurRadius(SHADOW_WIDTH);
	this->setGraphicsEffect(m_showEffect);

	m_lbl_text = new QLabel;
	m_lbl_text->setStyleSheet(QString("font-size:12px;color:black;padding-left:6px;font-family:Microsoft YaHei;"));
	QHBoxLayout* hMainLayout = new QHBoxLayout(this);
	hMainLayout->addWidget(m_lbl_text);
	hMainLayout->setSpacing(0);
	hMainLayout->setContentsMargins(SHADOW_WIDTH, SHADOW_WIDTH + TRIANGLE_HEIGHT, SHADOW_WIDTH, SHADOW_WIDTH);
}

ArrowWidget::~ArrowWidget()
{

}

void ArrowWidget::setStartPos( int startX )
{
	m_startX = startX;
}

void ArrowWidget::setTriangleInfo( int width, int height )
{
	m_triangleWidth = width;
	m_triangleHeight = height;
}

void ArrowWidget::setText( QString text )
{
	m_lbl_text->setText(text);
}

QString ArrowWidget::text() const
{
	return m_lbl_text->text();
}

void ArrowWidget::paintEvent( QPaintEvent *event )
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setPen(Qt::NoPen);
	painter.setBrush(QColor("#fff"));

	//小三角形区域
	QPainterPath drawPath;
	QPolygon trianglePolygon;
	switch (m_derect)
	{
	case up:
		trianglePolygon << QPoint(m_startX, m_triangleHeight + SHADOW_WIDTH);
		trianglePolygon << QPoint(m_startX + m_triangleWidth / 2, SHADOW_WIDTH);
	    trianglePolygon << QPoint(m_startX + m_triangleWidth, m_triangleHeight + SHADOW_WIDTH);
		drawPath.addRoundedRect(QRect(SHADOW_WIDTH, m_triangleHeight + SHADOW_WIDTH,\
				 width() - SHADOW_WIDTH * 2, height() - SHADOW_WIDTH * 2 - m_triangleHeight),\
				 BORDER_RADIUS, BORDER_RADIUS);
		break;
	case left:
		trianglePolygon << QPoint(3 + m_triangleHeight, 43);
		trianglePolygon << QPoint(8, 48 + m_triangleWidth / 2);
	    trianglePolygon << QPoint(3 + m_triangleHeight, 39 + m_triangleWidth);
	    drawPath.addRoundedRect(QRect(SHADOW_WIDTH, m_triangleHeight + SHADOW_WIDTH,\
				width() - SHADOW_WIDTH * 2, height() - SHADOW_WIDTH * 2 - m_triangleHeight),\
				BORDER_RADIUS, BORDER_RADIUS);
		break;
	case right:
		trianglePolygon << QPoint(115, 40);
		trianglePolygon << QPoint(116 + m_triangleHeight, 48 + m_triangleWidth / 2);
		trianglePolygon << QPoint(115, 39 + m_triangleWidth);
		drawPath.addRoundedRect(QRect(SHADOW_WIDTH, m_triangleHeight + SHADOW_WIDTH,\
				width() - SHADOW_WIDTH * 2, height() - SHADOW_WIDTH * 2 - m_triangleHeight),\
				BORDER_RADIUS, BORDER_RADIUS);
		break;
	case down:
		trianglePolygon << QPoint(m_startX, 65);
		trianglePolygon << QPoint(m_startX + m_triangleWidth / 2, 65 + m_triangleHeight);
		trianglePolygon << QPoint(m_startX + m_triangleWidth, 65);
		drawPath.addRoundedRect(QRect(SHADOW_WIDTH, m_triangleHeight + SHADOW_WIDTH,\
				width() - SHADOW_WIDTH * 2, height() - SHADOW_WIDTH * 2 - m_triangleHeight),\
				BORDER_RADIUS, BORDER_RADIUS);
		break;
	default: break;
	}

	drawPath.addPolygon(trianglePolygon);
	painter.drawPath(drawPath);
}

void ArrowWidget::mousePressEvent( QMouseEvent *event )
{
	this->close();
}

void ArrowWidget::setDerection( Derection d )
{
	m_derect = d;
}
