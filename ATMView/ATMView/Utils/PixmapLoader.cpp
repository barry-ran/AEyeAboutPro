/***********************************************************************************
*								PixmapLoader.cpp
*
* Copyright(C):	智慧眼科技股份有限公司
*
* Author:  YCL
*
* Date: 2019-06
*
* Description: 图片资源解析器
***********************************************************************************/

#include "PixmapLoader.h"
#include "Base64.h"
#include <QtGui>
#include <QPixmap>
#include <QImage>

QPixmap* PixmapLoader::loadFromBase64JPGBuf(const char* buf, int iBufLength, int iWidth, int iHeight) {
    QImage* pQImage = new QImage(iWidth, iHeight, QImage::Format_ARGB32);

    char* rbuf = new char[iBufLength];
    memset(rbuf, 0, iBufLength);
    int iLength = Base64::decode(rbuf, buf, iBufLength);

    bool bRet = pQImage->loadFromData((uchar *)rbuf, iLength, "JPG");

    delete[] rbuf;
    if(!bRet) {
        return NULL;
    }

    QPixmap* pQPixmap = new QPixmap(iWidth, iHeight);
    *pQPixmap = QPixmap::fromImage(pQImage->scaled(iWidth, iHeight));

    return pQPixmap;
}

QPixmap* PixmapLoader::loadFromJPGBuf(const char* buf, int iBufLength, int iWidth, int iHeight) {
    QImage* pQImage = new QImage(iWidth, iHeight, QImage::Format_ARGB32);

    bool bRet = pQImage->loadFromData((uchar *)buf, iBufLength, "JPG");
    if(!bRet) {
        return NULL;
    }

    QPixmap* pQPixmap = new QPixmap(iWidth, iHeight);
    *pQPixmap = QPixmap::fromImage(pQImage->scaled(iWidth, iHeight));

    return pQPixmap;
}

QPixmap* PixmapLoader::loadFromBase64BMPBuf(const char* buf, int iBufLength, int iWidth, int iHeight) {
	char* rbuf = new char[iBufLength];
	memset(rbuf, 0, iBufLength);
	int iLength = Base64::decode(rbuf, buf, iBufLength);

	QPixmap* pQPixmap = new QPixmap;
	bool bRet = pQPixmap->loadFromData((uchar *)rbuf, iLength/*, "JPG"*/);

	delete[] rbuf;
	if(!bRet) {
		return NULL;
	}

    QPixmap* pQPixmapR = new QPixmap(iWidth, iHeight);
    *pQPixmapR = pQPixmap->scaled(iWidth, iHeight);

	return pQPixmapR;
}

QPixmap* PixmapLoader::loadFromBMPBuf(const char* buf, int iBufLength, int iWidth, int iHeight) {
	QPixmap* pQPixmap = new QPixmap;
	bool bRet = pQPixmap->loadFromData((uchar *)buf, iBufLength);

	if(!bRet) {
		return NULL;
	}

    QPixmap* pQPixmapR = new QPixmap(iWidth, iHeight);
    *pQPixmapR = pQPixmap->scaled(iWidth, iHeight);

	return pQPixmapR;
}
