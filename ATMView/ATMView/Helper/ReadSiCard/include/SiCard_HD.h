#ifndef SICARD_H_H
#define SICARD_H_H


#include <windows.h>







#ifdef __cplusplus
extern "C"{
#endif




/***********************************************************
1.1.1	�򿪶�д���豸iDOpenPort
���������
Int	iReaderPort		�����������ӵĶ˿�
100	USB

���������
��		
����ֵ˵����
		Int 		>0  �������豸���
		-1			����ʧ��

***********************************************************/
long WINAPI iDOpenPort(int iReaderPort);


/**********************************************************
1.1.3	�رն�д���豸iDCloseReader
���������
Int			iReaderHandle			�������豸���
���������
��		
����ֵ˵��	��
		Int		0		����ɹ�
				��0		����ʧ��
**********************************************************/
long WINAPI iDCloseReader(long iReaderHandle);

/*********************************************************
1.2.1	���Ŀ�����iPChangePIN
�������		��
Int			iReaderHandle	�������豸���		
String		szOldPasswd		ԭ����
String		szNewPasswd		������
�������		��
			��
����ֵ˵��	��
			Int			0		����ɹ�
						��0		����ʧ��
*********************************************************/
long WINAPI iPChangePIN(long iReaderHandle, char *szOldPasswd, char *szNewPasswd);

/********************************************************
1.2.3	У�����뺯��iPInputPIN
�������		��
Int			iReaderHandle			�������豸���
String		szPasswd				��������		
�������		��
	��
����ֵ˵��	��
			0	У��ɹ�
			1-n ʣ��У�����
			-1	���ѱ���
**********************************************************/
long WINAPI iPInputPIN(long iReaderHandle, char *szPasswd);


/***********************************************************
2.1.1	����������ϢiRMFCardDeptInfo 
�������		��
Int			iReaderHandle			�������豸���		
�������		��
String		szCardID			����
String		szCardCertID		����ʶ����
String		szCardType			�����
String		szCardVersion		�淶�汾
String		szOrgDeptID			�������
String		szDispCardDate		��������
String		szExpireDate		��Ч��
����ֵ˵��	��
int			0		����ɹ�
			��0		����ʧ��
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
2.1.2	���ֿ��˻�����ϢiRMFCardOwnerInfo 
�������		��
Int			iReaderHandle			�������豸���		
�������		��
	String		szSfzhm				���֤����
	String		szName				����
	String		szSex				�Ա�
	String		szFolk				����
	String		szBirthDate			��������
	String		szBirthPlace		������
����ֵ˵��	��
	Int			0			����ɹ�
				��0			����ʧ��
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
ȡ������ϢiGetErrorInfo
������� ��
	Int		ErrorCode		 ������� 
������� ��
	��
����ֵ˵�� ��
	String  ErrorInfo		 ������Ϣ
************************************************************/
char * WINAPI iGetErrorInfo(int ErrorCode);






#ifdef __cplusplus
}
#endif

#endif