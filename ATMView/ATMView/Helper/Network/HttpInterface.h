/***********************************************************************************
*								HttpInterface.h
*
* Copyright(C):	智慧眼科技股份有限公司
*
* Author:  YCL
*
* Date: 2019-06
*
* Description: 网络请求地址、异常状态、接口声明、行为声明
***********************************************************************************/

#include <QString>

// 网络响应异常
const QString c_sNetError = QStringLiteral("网络连接异常");
const QString c_sServerJsonError = QStringLiteral("服务器数据异常");

//服务类型地址
const QString c_sFormalServerUrl = "http://61.178.32.128:7007";     //正式服务器地址
const QString c_sLocalServerUrl = "http://192.168.42.25:8082";      //本地服务器地址

//接口声明
const QString c_sHttpInterfaceParam = "/ws/services/MainServlet?wsdl";


//经办人登录
const QString c_sHttpActionOperatorLogin = "operatorLogin";
//获取用户基本信息
const QString c_sHttpActionGetBaseInfo = "getBaseInfo";
//获取用户身份证照片
const QString c_sHttpActionGetIdCardPic = "getIdCardPic";
//是否能认证
const QString c_sHttpActionIfCanIdentify = "ifCanIdentify";
//后台比对
const QString c_sHttpActionBackendRecognize = "backendRecognize";
//完成认证
const QString c_sHttpActionCompleteIdentify = "completeIdentify";
//心跳
const QString c_sHttpActionHeartbeat = "heartbeat";