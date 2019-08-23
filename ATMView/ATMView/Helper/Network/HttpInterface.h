/***********************************************************************************
*								HttpInterface.h
*
* Copyright(C):	�ǻ��ۿƼ��ɷ����޹�˾
*
* Author:  YCL
*
* Date: 2019-06
*
* Description: ���������ַ���쳣״̬���ӿ���������Ϊ����
***********************************************************************************/

#include <QString>

// ������Ӧ�쳣
const QString c_sNetError = QStringLiteral("���������쳣");
const QString c_sServerJsonError = QStringLiteral("�����������쳣");

//�������͵�ַ
const QString c_sFormalServerUrl = "http://61.178.32.128:7007";     //��ʽ��������ַ
const QString c_sLocalServerUrl = "http://192.168.42.25:8082";      //���ط�������ַ

//�ӿ�����
const QString c_sHttpInterfaceParam = "/ws/services/MainServlet?wsdl";


//�����˵�¼
const QString c_sHttpActionOperatorLogin = "operatorLogin";
//��ȡ�û�������Ϣ
const QString c_sHttpActionGetBaseInfo = "getBaseInfo";
//��ȡ�û����֤��Ƭ
const QString c_sHttpActionGetIdCardPic = "getIdCardPic";
//�Ƿ�����֤
const QString c_sHttpActionIfCanIdentify = "ifCanIdentify";
//��̨�ȶ�
const QString c_sHttpActionBackendRecognize = "backendRecognize";
//�����֤
const QString c_sHttpActionCompleteIdentify = "completeIdentify";
//����
const QString c_sHttpActionHeartbeat = "heartbeat";