/***********************************************************************************
*								EnumData.h
*
* Copyright(C):	智慧眼科技股份有限公司
*
* Author:  YCL
*
* Date: 2019-06
*
* Description: 通用枚举型数据
***********************************************************************************/

#pragma once

enum ServerHttpErrorCode{
	e_connectServerError = -1,
	e_success = 0, // 成功
	e_paramError = 1, // 参数错误，未找到参数
};

enum BioType
{
	BioType_None = 0,
	BioType_Face = 11,         //人脸
	BioType_FVein = 12,        //指静脉
	//    BiometricType_ParmVein = 13,
	//    BiometricType_Eye = 14,
	BioType_FPrint = 15,       //指纹
	//    BiometricType_Voice = 16,
};

enum ModelType
{
	//    BioModel_Default = 0,
	ModelType_VIS = 111,         // 可见光
	ModelType_NIR = 112,         // 近红外
	ModelType_FVein = 121,        // 指静脉反射
	ModelType_FPrint = 151,        // 指纹
};

//读卡类型
enum ReadCardType
{
   TYPE_IDCARD = 10001,                    //身份证
   TYPE_SECURITYCARD = 10002,              //社保卡
};

//读卡器操作码
enum CardReaderCode
{
	E_READ_SUCCESS = 0,                        //成功
	E_SI_CONNECT_FAILED = -1001,          //社保卡读卡器连接失败
	E_SI_READ_FAILED = -1002,             //社保卡读卡器读卡失败
	E_ID_CONNECT_FAILED = -1003,          //身份证读卡器连接失败
	E_ID_AUTHENTICATE_FAILED = -1004,     //身份证读卡器卡认证失败
	E_ID_READ_FAILED = -1005,             //身份证读卡器读卡失败
};