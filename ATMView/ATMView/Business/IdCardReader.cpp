/***********************************************************************************
*								IdCardReader.cpp
*
* Copyright(C):	智慧眼科技股份有限公司
*
* Author:  YCL
*
* Date: 2019-06
*
* Description: 身份证读卡器的操作类
***********************************************************************************/

#include "IdCardReader.h"
#include "HDstdapi.h"
#include "EnumData.h"
#include "GlogManager.h"
#include "EnumData.h"

IdCardReader* IdCardReader::m_pInstance = NULL;

IdCardReader::IdCardReader(QObject *parent)
	: QObject(parent)
{

}

IdCardReader::~IdCardReader()
{

}

IdCardReader* IdCardReader::instance()
{
	if (m_pInstance == NULL)
	{
		m_pInstance = new IdCardReader;
	}
	return m_pInstance;
}

int IdCardReader::read(AuthReadCardResult& readCardResult)
{
	int portId = 0;
	char name[50];
	char idCard[50];
	int i;

	//连接读卡器
	for (i = 0; i < MAX_HD900_IDCARD_USBPORT; i++) {
		if (E_READ_SUCCESS == HD_InitComm(1001 + i)) {  //遍历端口
			portId = 1001 + i;
			break;
		}
	}

	if (i == 8)
	{
		LOG(WARNING)<<"连接身份证读卡器失败!!!";
		return E_ID_CONNECT_FAILED;
	}

	int ret = HD_Authenticate(1);
	if (ret != E_READ_SUCCESS)
	{
		LOG(WARNING)<<"身份证卡认证失败!!!";
		HD_CloseComm(portId);
		return E_ID_AUTHENTICATE_FAILED;
	}

	//读卡信息
	ret = HD_ReadCard();
	if (ret != E_READ_SUCCESS)
	{
		LOG(WARNING)<<"身份证读卡失败!!!";
		HD_CloseComm(portId);
		return E_ID_READ_FAILED;
	}

	//获取姓名和证件号码
	GetName(name);
	GetCertNo(idCard);

	readCardResult.name = QString(QString::fromLocal8Bit(name));
	readCardResult.certificateNumber = QString(QLatin1String(idCard));
	readCardResult.cardType = TYPE_IDCARD;

	//关闭连接
	HD_CloseComm(portId);

	return E_READ_SUCCESS;
}
