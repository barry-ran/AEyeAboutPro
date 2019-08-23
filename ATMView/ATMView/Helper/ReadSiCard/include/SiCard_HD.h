#ifndef SICARD_H_H
#define SICARD_H_H


#include <windows.h>







#ifdef __cplusplus
extern "C"{
#endif




/***********************************************************
1.1.1	打开读写卡设备iDOpenPort
输入参数：
Int	iReaderPort		读卡器所连接的端口
100	USB

输出参数：
无		
返回值说明：
		Int 		>0  读卡器设备句柄
		-1			连接失败

***********************************************************/
long WINAPI iDOpenPort(int iReaderPort);


/**********************************************************
1.1.3	关闭读写卡设备iDCloseReader
输入参数：
Int			iReaderHandle			读卡器设备句柄
输出参数：
无		
返回值说明	：
		Int		0		处理成功
				非0		处理失败
**********************************************************/
long WINAPI iDCloseReader(long iReaderHandle);

/*********************************************************
1.2.1	更改卡密码iPChangePIN
输入参数		：
Int			iReaderHandle	读卡器设备句柄		
String		szOldPasswd		原密码
String		szNewPasswd		新密码
输出参数		：
			无
返回值说明	：
			Int			0		处理成功
						非0		处理失败
*********************************************************/
long WINAPI iPChangePIN(long iReaderHandle, char *szOldPasswd, char *szNewPasswd);

/********************************************************
1.2.3	校验密码函数iPInputPIN
输入参数		：
Int			iReaderHandle			读卡器设备句柄
String		szPasswd				输入密码		
输出参数		：
	无
返回值说明	：
			0	校验成功
			1-n 剩余校验次数
			-1	卡已被锁
**********************************************************/
long WINAPI iPInputPIN(long iReaderHandle, char *szPasswd);


/***********************************************************
2.1.1	读卡机构信息iRMFCardDeptInfo 
输入参数		：
Int			iReaderHandle			读卡器设备句柄		
输出参数		：
String		szCardID			卡号
String		szCardCertID		卡的识别码
String		szCardType			卡类别
String		szCardVersion		规范版本
String		szOrgDeptID			机构编号
String		szDispCardDate		发卡日期
String		szExpireDate		有效期
返回值说明	：
int			0		处理成功
			非0		处理失败
***********************************************************/
long WINAPI iRMFCardDeptInfo(long iReaderHandle,
							char *szCardID,
							char *szCardCertID,
							char *szCardType,
							char *szCardVersion,
							char *szOrgDeptID,
							char *szDispCardDate,
							char *szExpireDate
							);


/***************************************************************
2.1.2	读持卡人基本信息iRMFCardOwnerInfo 
输入参数		：
Int			iReaderHandle			读卡器设备句柄		
输出参数		：
	String		szSfzhm				身份证号码
	String		szName				姓名
	String		szSex				性别
	String		szFolk				民族
	String		szBirthDate			出生日期
	String		szBirthPlace		出生地
返回值说明	：
	Int			0			处理成功
				非0			处理失败
****************************************************************/
long WINAPI iRMFCardOwnerInfo(long iReaderHandle,
							 char *szSfzhm,
							 char *szName,
							 char *szSex,
							 char *szFolk,
							 char *szBirthDate,
							 char *szBirthPlace
							 );



/************************************************************
取错误信息iGetErrorInfo
输入参数 ：
	Int		ErrorCode		 错误代码 
输出参数 ：
	无
返回值说明 ：
	String  ErrorInfo		 错误信息
************************************************************/
char * WINAPI iGetErrorInfo(int ErrorCode);






#ifdef __cplusplus
}
#endif

#endif