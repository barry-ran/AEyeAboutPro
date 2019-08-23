/***********************************************************************************
*								ReadCardThread.cpp
*
* Copyright(C):	智慧眼科技股份有限公司
*
* Author:  YCL
*
* Date: 2019-06
*
* Description: 读卡线程，读取身份证和社保卡信息
***********************************************************************************/

#include "ReadCardThread.h"
#include "IdCardReader.h"
#include "SiCardReader.h"
#include "GlogManager.h"

#include <time.h>

ReadCardThread::ReadCardThread(ReadCardType type, QObject *parent)
	: QThread(parent)
{
	m_cardReader_type = type;
}

ReadCardThread::~ReadCardThread()
{

}

int ReadCardThread::readCard()
{
	bool successed = false;
	AuthReadCardResult readCardResult;
	int ret = -1;

	switch (m_cardReader_type)
	{
	case TYPE_IDCARD:
		LOG(INFO)<<"读取身份证信息...";
		ret = IdCardReader::instance()->read(readCardResult);
		break;
	case TYPE_SECURITYCARD:
		LOG(INFO)<<"读取社保卡信息...";
		ret = SiCardReader::instance()->read(readCardResult);
		break;
	}

	if (ret == E_READ_SUCCESS)
	{
		m_readCardResult.cardType = readCardResult.cardType;
		m_readCardResult.certificateNumber = readCardResult.certificateNumber;
		m_readCardResult.name = readCardResult.name;
	}
	return ret;
}

void ReadCardThread::run()
{
	const int tryTimes = 5;
	int errCode = -1;
	for (int i = 0; i < tryTimes; i++)
	{
		errCode = readCard();
		if (errCode == E_READ_SUCCESS)
		{
			emit readSuccessed(m_readCardResult);
			return;
		}
		msleep(100);
	}
	emit readFailed(errCode);
}
