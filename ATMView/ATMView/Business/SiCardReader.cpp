/***********************************************************************************
*								SiCardReader.cpp
*
* Copyright(C):	智慧眼科技股份有限公司
*
* Author:  YCL
*
* Date: 2019-06
*
* Description: 社保卡读卡器的操作类
***********************************************************************************/

#include "SiCardReader.h"
#include "SiCard_HD.h"
#include "GlogManager.h"
#include "EnumData.h"

SiCardReader* SiCardReader::m_pInstance = NULL;

SiCardReader::SiCardReader(QObject *parent)
	: QObject(parent)
{

}

SiCardReader::~SiCardReader()
{

}

SiCardReader* SiCardReader::instance()
{
	if (m_pInstance == NULL)
	{
		m_pInstance = new SiCardReader;
	}
	return m_pInstance;
}

int SiCardReader::read( AuthReadCardResult& readCardResult )
{
	int portId = 100;
	char cardNumber[50];
	char name[50];
	char sex[20];
	char folk[20];
	char birthDate[50];
	char birthPlace[50];
	char* errMsg;

	long handleId = iDOpenPort(portId);
	if (handleId == -1)
	{
		LOG(WARNING)<<"社保卡读卡器打开端口失败！！！";
		return E_SI_CONNECT_FAILED;
	}

	long ret = iRMFCardOwnerInfo(handleId, cardNumber, name, sex, folk, birthDate, birthPlace);
	if (ret != 0)
	{
		errMsg = iGetErrorInfo(ret);
		LOG(WARNING)<<"社保卡读卡失败："<<errMsg;
		iDCloseReader(handleId);
		return E_SI_READ_FAILED;
	}

	readCardResult.name = QString(QString::fromLocal8Bit(name));
	readCardResult.certificateNumber = QString(QLatin1String(cardNumber));
	readCardResult.cardType = TYPE_SECURITYCARD;
	 
	iDCloseReader(handleId);

	return E_READ_SUCCESS;
}
