#ifndef __AEYELOADIMG_H__
#define __AEYELOADIMG_H__

class QPixmap;
class PixmapLoader 
{
public:
	static QPixmap* loadFromBase64JPGBuf(const char* buf, int iBufLength, int iWidth, int iHeight);
    static QPixmap* loadFromJPGBuf(const char* buf, int iBufLength, int iWidth, int iHeight);
	static QPixmap* loadFromBase64BMPBuf(const char* buf, int iBufLength, int iWidth, int iHeight);
	static QPixmap* loadFromBMPBuf(const char* buf, int iBufLength, int iWidth, int iHeight);
};

#endif // !__AEYELOADIMG_H__
