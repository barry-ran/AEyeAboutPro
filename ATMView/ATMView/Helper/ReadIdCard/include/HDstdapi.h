#ifndef APPLICATION_H
#define APPLICATION_H
#include <windows.h>

//״̬��
#define SHD_OK					  0		 //ִ�гɹ�
#define SHD_WOK					  1		 //ִ�гɹ�
#define SHD_Connect_Error		 -1	     //�豸���Ӵ�
#define SHD_UnConnected		 	 -2	     //�豸δ��������(û��ִ�д��豸����)
#define SHD_BadLoadDLL_Error	 -3	     //(��̬��)����ʧ��
#define SHD_Parameter_Error		 -4	     //(������̬���)������
#define SHD_Request_Error		 -5		 //Ѱ��ʧ��
#define SHD_Select_Error		 -6		 //ѡ��ʧ��
#define SHD_ReadBase_Error	     -7		 //����ʧ��
#define SHD_ReadBaseFP_Error     -8	     //��ȡ׷����Ϣʧ��
#define SHD_ReadADD_Error	     -9	     //��ȡ׷����Ϣʧ��
#define SHD_Sam_Error	        -10      //����ͨ��ʧ��
#define SHD_CheckSam_Error	    -11      //����ͨ��ʧ��
#define SHD_SamToFinger_Error	-12      //����ͨ��ģ�鲻֧�ֻ�ȡָ��
#define SHD_OTHER_ERROR	        -999	 //�����쳣����



#ifdef __cplusplus
extern "C" {
#endif

int WINAPI HD_InitComm(int Port);
int WINAPI HD_CloseComm(int Port);

int WINAPI HD_GetCOMBaud(unsigned int *puiBaudRate);
int WINAPI HD_SetCOMBaud(unsigned int uiCurrBaud, unsigned int uiSetBaud);

int WINAPI HD_Authenticate(int b);
int WINAPI HD_ReadCard(); //���֤����

int WINAPI HD_Read_IDInfo(char* pBmpData, char *BaseMsgData); //���֤ԭʼ���� ����+��Ƭ
int WINAPI HD_Read_IDFPInfo(char* pFingerData, char* pBmpData, char *BaseMsgData); //���֤ԭʼ���� ��ָ�� 



/*
��ȡ�������֤��Ϣ char * pOutputInfo
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
/*���pBmpFile==NULL����������Ƭ������������Ƭ�������봫��·�������磺C:/zhaopian/zp.bmp
  PS����֧�־������֤
*/







int WINAPI HD_Read_NewAppMsg(char* AppAddressMsg);
//��ȡ ���֤׷�ӵ�ַ��Ϣ

int WINAPI HD_Get_SAMIDToStr(char* SAMIDMsg);
//��ȡ����ģ��ID�����Ϊ�ַ���

int WINAPI HD_ResetSAM(int Port);
int WINAPI HD_Set_MaxRFByte(unsigned char RFByte);
int WINAPI HD_Get_SAMStatus();
int WINAPI HD_Get_SAMID(unsigned char* SAMID);
int WINAPI HD_ID_RequestIDCard();
int WINAPI HD_ID_SelectIDCard();


//�ַ���תʮ��������ֵ��
	void WINAPI StrToHex(unsigned char *Src,unsigned char *Des);
	//ʮ��������ֵ��ת�ַ���
	void WINAPI HexToStr(unsigned char *Src,unsigned char *Des,int len);

#ifdef __cplusplus
}
#endif

#endif