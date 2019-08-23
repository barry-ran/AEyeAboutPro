#ifndef AIOVIEWER_H
#define AIOVIEWER_H

#include <QtWidgets/QMainWindow>
#include <QTimer>
#include <QStateMachine>
#include <QState>
#include "ui_AIOViewer.h"
#include "HttpStructData.h"

#define TIMING 60    //登录推出计时
#define TERM_VERSION "v1.0.0"   //终端版本号

class ArrowWidget;
class LoadingWindow;
class IdentifyDlg;
class AuthorizateDlg;
class SystemSettingsDlg;
class AIOViewer : public QMainWindow
{
	Q_OBJECT

public:
	AIOViewer(QWidget *parent = 0);
	~AIOViewer();

private slots:
	//经办人登录应答
	void RespondOnOperatorLogin(int nCode, QString sMsg, QString sessionId);
	//获取基本信息应答
	void RespondOnGetBaseInfo(int nCode, QString sMsg, ModelStatus modelStatus, QString sysNo);
	//获取身份证照片应答
	void RespondOnGetIdCardPic(int nCode, QString sMsg, QString picData);
	//是否能认证应答
	void RespondOnIfCanIdentify(int nCode, QString sMsg, bool successed, QString batchId);
    //心跳应答
	void RespondOnHeartbeat(int nCode, QString sMsg);

	//选择身份证登录
	void slotOnLoginByIdCard();
	//选择社保卡登录
	void slotOnLoginBySiCard();
	//返回主页
	void slotOnBackHomePage();
	//显示人脸认证窗口
	void slotOnFaceIdentify();
	//显示指静脉认证窗口
	void slotOnVeinIdentify();
	//显示指纹认证窗口
	void slotOnFingerIdentify();
	//授权
	void slotOnAuthorizate();
	//授权完成
	void slotOnAuthorizateFinished();
	//显示认证选择页面
	void showIdentifySelectedPage();
    //读卡成功
	void onReadCardSuccessed(AuthReadCardResult readCardResult);
	//读卡失败
	void onReadCardFailed(int errCode);
	//进入初始化状态
	void onEnterInitState();
	//进入用户操作状态
	void onEnterWorkState();
	//推出用户操作状态
    void onExitWorkState();
	//心跳定时响应
	void onTimeoutHeartbeat();
	//定时器响应
	void onTimeoutFunc();
	//返回桌面
	void onToDesktop();

	void onButtonActivateOn();

signals:
	//切换到初始化状态
	void TranslateToInitState();
	//切换到用户操作状态
	void TranslateToWorkState();

private:
	//初始化UI
	void InitUI();
	//刷新UI
	void UpdateUI(ModelStatus modelStatus);
	//初始化连接
	void InitConnect();
	//初始化状态机
	void InitStateMachine();
	//初始化定时器
	void InitTimer();
	//获取按钮状态
	QString getButtonStyle(bool status);
	QString getButtonModelStatus(bool status, QString& style);
	//终端状态改变
	void TerminateStatusChanged(bool onLine);
	//显示气泡弹框
	void showBubbleTips();
	//关闭气泡弹窗
	void closeBubbleTips();

private slots:
	//显示加载框
	void showLoadingProgress(QString loadingText);
	//关闭加载框
	void closeLoadingProgress();

private:
	Ui::AIOViewerClass ui;
	/***心跳相关*****/
	QTimer* m_heartbeat_timer;  //心跳定时器
	int m_heartbeatTimes;       //心跳次数
	int m_offlineCount;         //离线次数

	QTimer* m_count_timer;      //计时推出定时器
	int m_counter;              //推出计时
	QString m_sysNo;            //系统编号

	InterfaceInputHead m_interfaceHead;    
	AuthReadCardResult m_readCardResult;

	IdentifyDlg* m_identifyDlg;
	LoadingWindow* m_loadingDlg;
	AuthorizateDlg* m_authorizateDlg;
	SystemSettingsDlg* m_settingsDlg;
	ArrowWidget* m_arrowWgt;

	//状态机
	QStateMachine *m_stateMachine;  
	QState* m_InitState;
	QState* m_WorkState;
};

#endif // AIOVIEWER_H
