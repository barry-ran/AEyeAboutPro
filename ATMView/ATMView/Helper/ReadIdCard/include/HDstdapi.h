#ifndef APPLICATION_H
#define APPLICATION_H
#include <windows.h>

//状态码
#define SHD_OK					  0		 //执行成功
#define SHD_WOK					  1		 //执行成功
#define SHD_Connect_Error		 -1	     //设备连接错
#define SHD_UnConnected		 	 -2	     //设备未建立连接(没有执行打开设备函数)
#define SHD_BadLoadDLL_Error	 -3	     //(动态库)加载失败
#define SHD_Parameter_Error		 -4	     //(发给动态库的)参数错
#define SHD_Request_Error		 -5		 //寻卡失败
#define SHD_Select_Error		 -6		 //选卡失败
#define SHD_ReadBase_Error	     -7		 //读卡失败
#define SHD_ReadBaseFP_Error     -8	     //读取追加信息失败
#define SHD_ReadADD_Error	     -9	     //读取追加信息失败
#define SHD_Sam_Error	        -10      //管理通信失败
#define SHD_CheckSam_Error	    -11      //检验通信失败
#define SHD_SamToFinger_Error	-12      //管理通信模块不支持获取指纹
#define SHD_OTHER_ERROR	        -999	 //其他异常错误



#ifdef __cplusplus
extern "C" {
#endif

int WINAPI HD_InitComm(int Port);
int WINAPI HD_CloseComm(int Port);

int WINAPI HD_GetCOMBaud(unsigned int *puiBaudRate);
int WINAPI HD_SetCOMBaud(unsigned int uiCurrBaud, unsigned int uiSetBaud);

int WINAPI HD_Authenticate(int b);
int WINAPI HD_ReadCard(); //身份证读卡

int WINAPI HD_Read_IDInfo(char* pBmpData, char *BaseMsgData); //身份证原始数据 文字+照片
int WINAPI HD_Read_IDFPInfo(char* pFingerData, char* pBmpData, char *BaseMsgData); //身份证原始数据 含指纹 



/*
获取单条身份证信息 char * pOutputInfo
*/
int WINAPI GetName(char* pName);
int WINAPI GetSex(char* pSex);
int WINAPI GetNation(char* pNation);
int WINAPI GetBirth(char* pBirth);
int WINAPI GetAddress(char* pAddress);
int WINAPI GetCertNo(char* pCertNo);
int WINAPI GetDepartemt(char* pDepartemt);
int WINAPI GetEffectDate(char* pEffectDate);
int WINAPI GetExpireDate(char* pExpireDate);

int WINAPI GetTXZHM(char* pTXZHM);
int WINAPI GetTXZQFCS(char* pTXZQFCS);

int WINAPI GetB64FileData(char* pB64FileData);
int WINAPI GetBmpFileData(char* pBmpFileData);
int   WINAPI GetBmpFile(char* pBmpfilepath);

int	  WINAPI IsFingerExist();
int	  WINAPI GetFingerprint(unsigned char* fpInfo);

int	WINAPI GetCardType();
int WINAPI GetEnName(char* pEnName);
int WINAPI GetNationalityCode(char* pNationalityCode);
int WINAPI GetCardVersion(char* pCardVersion);
int WINAPI GetAuthorCode(char* pAuthorCode);
int WINAPI GetCardTypeFlag(char* pCardTypeFlag);


int WINAPI HD_Read_BaseMsg(const char* pBmpFile,
						   char *pName, 
						   char *pSex, 
						   char *pNation, 
						   char *pBirth, 
						   char *pAddress, 
						   char *pCertNo, 
						   char *pDepartment, 
						   char *pEffectData, 
						   char *pExpire);
/*如果pBmpFile==NULL，则不生成照片，如需生成照片，这里请传入路径。例如：C:/zhaopian/zp.bmp
  PS：仅支持居民身份证
*/







int WINAPI HD_Read_NewAppMsg(char* AppAddressMsg);
//读取 身份证追加地址信息

int WINAPI HD_Get_SAMIDToStr(char* SAMIDMsg);
//获取管理模块ID，输出为字符串

int WINAPI HD_ResetSAM(int Port);
int WINAPI HD_Set_MaxRFByte(unsigned char RFByte);
int WINAPI HD_Get_SAMStatus();
int WINAPI HD_Get_SAMID(unsigned char* SAMID);
int WINAPI HD_ID_RequestIDCard();
int WINAPI HD_ID_SelectIDCard();


//字符串转十六进制数值串
	void WINAPI StrToHex(unsigned char *Src,unsigned char *Des);
	//十六进制数值串转字符串
	void WINAPI HexToStr(unsigned char *Src,unsigned char *Des,int len);

#ifdef __cplusplus
}
#endif

#endif