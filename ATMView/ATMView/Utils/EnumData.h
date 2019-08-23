/***********************************************************************************
*								EnumData.h
*
* Copyright(C):	�ǻ��ۿƼ��ɷ����޹�˾
*
* Author:  YCL
*
* Date: 2019-06
*
* Description: ͨ��ö��������
***********************************************************************************/

#pragma once

enum ServerHttpErrorCode{
	e_connectServerError = -1,
	e_success = 0, // �ɹ�
	e_paramError = 1, // ��������δ�ҵ�����
};

enum BioType
{
	BioType_None = 0,
	BioType_Face = 11,         //����
	BioType_FVein = 12,        //ָ����
	//    BiometricType_ParmVein = 13,
	//    BiometricType_Eye = 14,
	BioType_FPrint = 15,       //ָ��
	//    BiometricType_Voice = 16,
};

enum ModelType
{
	//    BioModel_Default = 0,
	ModelType_VIS = 111,         // �ɼ���
	ModelType_NIR = 112,         // ������
	ModelType_FVein = 121,        // ָ��������
	ModelType_FPrint = 151,        // ָ��
};

//��������
enum ReadCardType
{
   TYPE_IDCARD = 10001,                    //���֤
   TYPE_SECURITYCARD = 10002,              //�籣��
};

//������������
enum CardReaderCode
{
	E_READ_SUCCESS = 0,                        //�ɹ�
	E_SI_CONNECT_FAILED = -1001,          //�籣������������ʧ��
	E_SI_READ_FAILED = -1002,             //�籣������������ʧ��
	E_ID_CONNECT_FAILED = -1003,          //���֤����������ʧ��
	E_ID_AUTHENTICATE_FAILED = -1004,     //���֤����������֤ʧ��
	E_ID_READ_FAILED = -1005,             //���֤����������ʧ��
};