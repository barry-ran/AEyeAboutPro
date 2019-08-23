/***********************************************************************************
*								IdCardReader.cpp
*
* Copyright(C):	�ǻ��ۿƼ��ɷ����޹�˾
*
* Author:  YCL
*
* Date: 2019-06
*
* Description: ���֤�������Ĳ�����
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

	//���Ӷ�����
	for (i = 0; i < MAX_HD900_IDCARD_USBPORT; i++) {
		if (E_READ_SUCCESS == HD_InitComm(1001 + i)) {  //�����˿�
			portId = 1001 + i;
			break;
		}
	}

	if (i == 8)
	{
		LOG(WARNING)<<"�������֤������ʧ��!!!";
		return E_ID_CONNECT_FAILED;
	}

	int ret = HD_Authenticate(1);
	if (ret != E_READ_SUCCESS)
	{
		LOG(WARNING)<<"���֤����֤ʧ��!!!";
		HD_CloseComm(portId);
		return E_ID_AUTHENTICATE_FAILED;
	}

	//������Ϣ
	ret = HD_ReadCard();
	if (ret != E_READ_SUCCESS)
	{
		LOG(WARNING)<<"���֤����ʧ��!!!";
		HD_CloseComm(portId);
		return E_ID_READ_FAILED;
	}

	//��ȡ������֤������
	GetName(name);
	GetCertNo(idCard);

	readCardResult.name = QString(QString::fromLocal8Bit(name));
	readCardResult.certificateNumber = QString(QLatin1String(idCard));
	readCardResult.cardType = TYPE_IDCARD;

	//�ر�����
	HD_CloseComm(portId);

	return E_READ_SUCCESS;
}
