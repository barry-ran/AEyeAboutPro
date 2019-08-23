/***********************************************************************************
*								AIOViewer.cpp
*
* Copyright(C):	智慧眼科技股份有限公司
*
* Author:  YCL
*
* Date: 2019-06
*
* Description: 自助终端主界面
***********************************************************************************/

#include "AIOViewer.h"
#include "HttpAgent.h"
#include "commonFunc.h"
#include "IdentifyDlg.h"
#include "LoadingWindow.h"
#include "AuthorizateDlg.h"
#include "SystemSettingsDlg.h"
#include "ReadCardThread.h"
#include "PixmapLoader.h"
#include "ArrowWidget.h"
#include "MessageWindow.h"
#include "GlogManager.h"
#include "UserConfig.h"
#include "CommonConstData.h"
#include "GlobalSignal.h"

#include <QMouseEvent>

AIOViewer::AIOViewer(QWidget *parent)
	: QMainWindow(parent)
	, m_identifyDlg(NULL)
	, m_loadingDlg(NULL)
	, m_authorizateDlg(NULL)
	, m_settingsDlg(NULL)
	, m_arrowWgt(NULL)
	, m_counter(TIMING)
    , m_offlineCount(0)
	, m_heartbeatTimes(0)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Window);
	showFullScreen();

	InitUI();
	InitTimer();
	InitStateMachine();
	InitConnect();

	QString userId, passwd;
	INSTANCE_USER_CONFIG->getOperatorInfo(userId, passwd);
	INSTANCE_USER_CONFIG->setVersion(TERM_VERSION);

	OperatorInfo info;
	info.userId =userId;
	info.passwd = passwd;
	info.type = "1";
	m_interfaceHead.userId = userId;
	m_interfaceHead.terminalVersion = INSTANCE_USER_CONFIG->getVersion();
	m_interfaceHead.terminalId = INSTANCE_USER_CONFIG->getMac();

	m_heartbeat_timer->start();
	onTimeoutHeartbeat();

	HttpAgent::instance()->RequestOnOperatorLogin(info, m_interfaceHead);
}

AIOViewer::~AIOViewer()
{

}

void AIOViewer::RespondOnOperatorLogin( int nCode, QString sMsg, QString sessionId)
{
	if (nCode != e_success)
	{
		LOG(INFO)<<"OperatorLogin 请求出现异常 -- 错误码: "<<nCode<<", 错误信息: "<<sMsg.toLocal8Bit().data();
		MessageWindow msgWindow(MessageWindow::Warning, this);
		msgWindow.setText(QStringLiteral("系统初始化异常--错误码:%1, 错误信息:%2").arg(nCode).arg(sMsg));
		msgWindow.exec();
	}
	else
	{
		LOG(INFO)<<"OperatorLogin 请求成功";
	    m_interfaceHead.sessionId = sessionId;
	}
}

void AIOViewer::InitUI()
{
	setWindowIcon(QIcon(QStringLiteral(":/AIOViewer/Resources/desktop.png")));

	QString stylesheet = "QLabel{font-size:24px;color:white;} QPushButton{background:#00cb00;border-radius:4px;}";
	ui.btn_IdCard->InitButton(QStringLiteral("身份证"), ":/AIOViewer/Resources/idCard.png", stylesheet);
	ui.btn_IdCard->setIconSize(128, 128);
	ui.btn_SiCard->InitButton(QStringLiteral("社保卡"), ":/AIOViewer/Resources/securityCard.png", stylesheet);
	ui.btn_SiCard->setIconSize(128, 128);

	QString commonStyle = "QLabel{font-size:14px;color:white;} QPushButton{background:rgb(0, 144, 216);border-radius:4px;}";
	ui.btn_faceIdentify->InitButton(QStringLiteral("人脸认证"), ":/AIOViewer/Resources/face.png", commonStyle);
    ui.btn_veinIdentify->InitButton(QStringLiteral("指静脉认证"), ":/AIOViewer/Resources/vein.png", commonStyle);
	ui.btn_fingerIdentify->InitButton(QStringLiteral("指纹认证"), ":/AIOViewer/Resources/finger.png", commonStyle);

	ui.lbl_version->setText(INSTANCE_USER_CONFIG->getVersion());
}

void AIOViewer::InitConnect()
{
	connect(ui.btn_IdCard, SIGNAL(clicked()), this, SLOT(slotOnLoginByIdCard()));
	connect(ui.btn_SiCard, SIGNAL(clicked()), this, SLOT(slotOnLoginBySiCard()));
	connect(ui.btn_return, SIGNAL(clicked()), this, SLOT(slotOnBackHomePage()));
	connect(ui.btn_faceIdentify, SIGNAL(clicked()), this, SLOT(slotOnFaceIdentify()));
	connect(ui.btn_veinIdentify, SIGNAL(clicked()), this, SLOT(slotOnVeinIdentify()));
	connect(ui.btn_fingerIdentify, SIGNAL(clicked()), this, SLOT(slotOnFingerIdentify()));
	connect(ui.btn_settings, SIGNAL(clicked()), this, SLOT(slotOnAuthorizate()));
	connect(ui.btn_exit, SIGNAL(clicked()), this, SLOT(onExitWorkState()));

	connect(HttpAgent::instance(), SIGNAL(RespondOnOperatorLogin(int, QString, QString)), 
		this, SLOT(RespondOnOperatorLogin(int, QString, QString)));
	connect(HttpAgent::instance(), SIGNAL(RespondOnGetBaseInfo(int, QString, ModelStatus, QString)), 
		this, SLOT(RespondOnGetBaseInfo(int, QString, ModelStatus, QString)));
	connect(HttpAgent::instance(), SIGNAL(RespondOnGetIdCardPic(int, QString, QString)), 
		this, SLOT(RespondOnGetIdCardPic(int, QString, QString)));
	connect(HttpAgent::instance(), SIGNAL(RespondOnIfCanIdentify(int, QString, bool, QString)), 
		this, SLOT(RespondOnIfCanIdentify(int, QString, bool, QString)));
	connect(HttpAgent::instance(), SIGNAL(RespondOnHeartbeat(int, QString)), 
		this, SLOT(RespondOnHeartbeat(int, QString)));

	connect(GlobalSignal::instance(), SIGNAL(onButtonActivateOn()), this, SLOT(onButtonActivateOn()));
}

void AIOViewer::slotOnBackHomePage()
{
	ui.wgt_main->setCurrentWidget(ui.page_home);
}

void AIOViewer::slotOnFaceIdentify()
{
	showLoadingProgress(QStringLiteral("正在加载，请稍后..."));
	HttpAgent::instance()->RequestOnIfCanIdentify(m_sysNo, m_interfaceHead);
}

void AIOViewer::showIdentifySelectedPage()
{
	closeLoadingProgress();
    ui.wgt_main->setCurrentWidget(ui.page_Identify);
}

void AIOViewer::slotOnAuthorizate()
{
	if (m_authorizateDlg == NULL)
	{
		m_authorizateDlg = new AuthorizateDlg;
		connect(m_authorizateDlg, SIGNAL(sigOnAuthorizateFinished()), this, SLOT(slotOnAuthorizateFinished()));
	}
	m_authorizateDlg->load();
	m_authorizateDlg->raise();
	m_authorizateDlg->show();
}

void AIOViewer::slotOnAuthorizateFinished()
{
	m_authorizateDlg->close();
	if (m_settingsDlg == NULL)
	{
		m_settingsDlg = new SystemSettingsDlg;
		connect(m_settingsDlg, SIGNAL(sigOnToDesktop()), this, SLOT(onToDesktop()));
	}
	m_settingsDlg->load();
	m_settingsDlg->exec();
}

void AIOViewer::RespondOnGetBaseInfo( int nCode, QString sMsg, ModelStatus modelStatus, QString sysNo )
{
    closeLoadingProgress();
	if (nCode != e_success)
	{
		LOG(INFO)<<"GetBaseInfo 请求出现异常 -- 错误码: "<<nCode<<", 错误信息: "<<sMsg.toLocal8Bit().data();
		emit TranslateToInitState();
		MessageWindow msgWindow(MessageWindow::Warning, this);
		msgWindow.setText(QStringLiteral("网络请求异常--错误码:%1, 错误信息:%2").arg(nCode).arg(sMsg));
		msgWindow.exec();
	}
	else
	{
		LOG(INFO)<<"GetBaseInfo 请求成功";
		m_sysNo = sysNo;
        UpdateUI(modelStatus);

		IdCardPicData idCardPicData;
		idCardPicData.sysCode = "0";
		idCardPicData.sysNo = m_sysNo;
		HttpAgent::instance()->RequestOnGetIdCardPic(idCardPicData, m_interfaceHead);

		emit TranslateToWorkState();
	}
}

void AIOViewer::UpdateUI( ModelStatus modelStatus)
{	
	ui.btn_faceIdentify->InitButton(QStringLiteral("人脸认证"), ":/AIOViewer/Resources/face.png", getButtonStyle(modelStatus.faceModelStatus));
	ui.btn_veinIdentify->InitButton(QStringLiteral("指静脉认证"), ":/AIOViewer/Resources/vein.png", getButtonStyle(modelStatus.fveinModelStatus));
	ui.btn_fingerIdentify->InitButton(QStringLiteral("指纹认证"), ":/AIOViewer/Resources/finger.png", getButtonStyle(modelStatus.fprintModelStatus));

	ui.btn_faceIdentify->setDisabled(!modelStatus.faceModelStatus);
	ui.btn_veinIdentify->setDisabled(!modelStatus.fveinModelStatus);
	ui.btn_fingerIdentify->setDisabled(!modelStatus.fprintModelStatus);

	QString style;
	ui.status_faceIdentify->setText(getButtonModelStatus(modelStatus.faceModelStatus, style));
	ui.status_faceIdentify->setStyleSheet(style);
	ui.status_veinIdentify->setText(getButtonModelStatus(modelStatus.fveinModelStatus, style));
	ui.status_veinIdentify->setStyleSheet(style);
	ui.status_fingerIdentify->setText(getButtonModelStatus(modelStatus.fprintModelStatus, style));
	ui.status_fingerIdentify->setStyleSheet(style);

	ui.lbl_userName->setText(m_readCardResult.name);
	ui.lbl_idCard->setText(CommonFunc::handleIdCardInfo(m_readCardResult.certificateNumber));
}

QString AIOViewer::getButtonStyle( bool status )
{
	QString style;
	if (status)
	{
		style = "QLabel{font-size:14px;color:white;} QPushButton{background:rgb(0, 144, 216);border-radius:4px;}";
	}
	else
	{
		style = "QLabel{font-size:14px;color:white;} QPushButton{background:gray;border-radius:4px;}";
	}
	return style;
}

QString AIOViewer::getButtonModelStatus( bool status, QString& style )
{
	QString text;
	if (status)
	{
		text  = QStringLiteral("可认证");
		style = "font-size:14px;color:rgb(0, 144, 216);";
	}
	else
	{
		text = QStringLiteral("未建模");
		style = "font-size:14px;color:gray;";
	}
	return text;
}

void AIOViewer::showLoadingProgress( QString loadingText )
{
	if (m_loadingDlg == NULL)
	{
		m_loadingDlg = new LoadingWindow;
	}
	m_loadingDlg->setText(loadingText);
	m_loadingDlg->raise();
	m_loadingDlg->show();
}

void AIOViewer::closeLoadingProgress()
{
	if (m_loadingDlg != NULL)
	{
		m_loadingDlg->finish();
	}
}

void AIOViewer::InitTimer()
{
	m_heartbeat_timer = new QTimer(this);
	m_heartbeat_timer->setInterval(5000);
	connect(m_heartbeat_timer, SIGNAL(timeout()), this, SLOT(onTimeoutHeartbeat()));

	m_count_timer = new QTimer(this);
	m_count_timer->setInterval(1000);
	connect(m_count_timer, SIGNAL(timeout()), this, SLOT(onTimeoutFunc()));
}

void AIOViewer::onReadCardSuccessed( AuthReadCardResult readCardResult )
{
	closeLoadingProgress();

	m_readCardResult = readCardResult;
	UserBaseInfo info;
	info.name = m_readCardResult.name;
	info.idCard = m_readCardResult.certificateNumber;
	info.cardType = "0";
	HttpAgent::instance()->RequestOnGetBaseInfo(info, m_interfaceHead);
}

void AIOViewer::onReadCardFailed(int errCode)
{
	closeLoadingProgress();

	QString tipText;
	switch (errCode)
	{
	case E_SI_CONNECT_FAILED:
		tipText = Str_SiConnectFailed;
		break;
	case E_SI_READ_FAILED:
		tipText = Str_SiReadFailed;
		break;
	case E_ID_CONNECT_FAILED:
		tipText = Str_IdConnectFailed;
		break;
	case E_ID_AUTHENTICATE_FAILED:
		tipText = Str_IdAuthenticateFailed;
		break;
	case E_ID_READ_FAILED:
		tipText = Str_IdReadFailed;
		break;
	}

	MessageWindow msgWindow(MessageWindow::Warning, this);
	msgWindow.setText(tipText);
	msgWindow.exec(); 
}

void AIOViewer::slotOnLoginByIdCard()
{
	showLoadingProgress(QStringLiteral("正在加载，请稍候..."));

	ReadCardThread* thread = new ReadCardThread(TYPE_IDCARD, this);
	qRegisterMetaType<AuthReadCardResult>("AuthReadCardResult");
	connect(thread, SIGNAL(readFailed(int)), this, SLOT(onReadCardFailed(int)));
	connect(thread, SIGNAL(readSuccessed(AuthReadCardResult)), this, SLOT(onReadCardSuccessed(AuthReadCardResult)));
	thread->start();
}

void AIOViewer::slotOnLoginBySiCard()
{
	showLoadingProgress(QStringLiteral("正在加载，请稍候..."));

	ReadCardThread* thread = new ReadCardThread(TYPE_SECURITYCARD, this);
	qRegisterMetaType<AuthReadCardResult>("AuthReadCardResult");
	connect(thread, SIGNAL(readFailed(int)), this, SLOT(onReadCardFailed(int)));
	connect(thread, SIGNAL(readSuccessed(AuthReadCardResult)), this, SLOT(onReadCardSuccessed(AuthReadCardResult)));
	thread->start();
}

void AIOViewer::InitStateMachine()
{
	m_stateMachine = new QStateMachine(this);
	m_InitState = new QState(m_stateMachine);
	m_WorkState = new QState(m_stateMachine);

	connect(m_InitState, SIGNAL(entered()), this, SLOT(onEnterInitState()));
	connect(m_WorkState, SIGNAL(entered()), this, SLOT(onEnterWorkState()));

	m_InitState->addTransition(this, SIGNAL(TranslateToWorkState()), m_WorkState);
	m_WorkState->addTransition(this, SIGNAL(TranslateToInitState()), m_InitState);

	m_stateMachine->setInitialState(m_InitState);
	m_stateMachine->start();
}

void AIOViewer::onEnterInitState()
{
	m_readCardResult.clear();

	ui.lbl_userName->setText("***");
	ui.lbl_idCard->setText("******************");
	ui.lbl_icon->setPixmap(QPixmap::fromImage(QImage(":/AIOViewer/Resources/user_icon.png")));

	ui.btn_exit->setHidden(true);
	ui.lbl_clock->setHidden(true);
	ui.lbl_timing->setHidden(true);
	ui.btn_return->setHidden(true);

	ui.wgt_main->setCurrentWidget(ui.page_home);
	m_count_timer->stop();
	m_counter = TIMING;
}

void AIOViewer::onEnterWorkState()
{
	ui.btn_exit->setHidden(false);
	ui.lbl_clock->setHidden(false);
	ui.lbl_timing->setHidden(false);

	ui.wgt_main->setCurrentWidget(ui.page_Identify);
    m_count_timer->start();
	onTimeoutFunc();
}

void AIOViewer::onTimeoutFunc()
{
	ui.lbl_timing->setText(QString::number(m_counter--));
	if (m_counter == -1)
	{
		onExitWorkState();
	}
}

void AIOViewer::onExitWorkState()
{
	emit TranslateToInitState();
}

void AIOViewer::RespondOnGetIdCardPic( int nCode, QString sMsg, QString picData )
{
	if (nCode != e_success)
	{
		LOG(INFO)<<"GetIdCardPic 请求出现异常 -- 错误码: "<<nCode<<", 错误信息: "<<sMsg.toLocal8Bit().data();
		MessageWindow msgWindow(MessageWindow::Warning, this);
		msgWindow.setText(QStringLiteral("网络请求异常--错误码:%1, 错误信息:%2").arg(nCode).arg(sMsg));
		msgWindow.exec();
	}
	else
	{
		LOG(INFO)<<"GetIdCardPic 请求成功";
		if (!picData.isEmpty())
		{
			QPixmap *p;
			p = PixmapLoader::loadFromBase64BMPBuf(picData.toStdString().c_str(), picData.length(), ui.lbl_icon->size().width(), ui.lbl_icon->size().height());
			*p = p->scaled(ui.lbl_icon->size().width(), ui.lbl_icon->size().height() - 2, Qt::KeepAspectRatio);
			ui.lbl_icon->setPixmap(*p);
		}
	}
}

void AIOViewer::RespondOnIfCanIdentify( int nCode, QString sMsg, bool successed, QString batchId )
{
	if (nCode < e_success)
	{
		closeLoadingProgress();
		LOG(INFO)<<"IfCanIdentify 请求出现异常 -- 错误码: "<<nCode<<", 错误信息: "<<sMsg.toLocal8Bit().data();
		MessageWindow msgWindow(MessageWindow::Warning, this);
		msgWindow.setText(QStringLiteral("网络请求异常--错误码:%1, 错误信息:%2").arg(nCode).arg(sMsg));
		msgWindow.exec();
	}
	else
	{
		LOG(INFO)<<"IfCanIdentify 请求成功";
		if (successed)
		{
			if (m_identifyDlg == NULL)
			{
				m_identifyDlg = new IdentifyDlg(m_sysNo, batchId, m_interfaceHead);
			}
			closeLoadingProgress();
 			m_identifyDlg->openCamera();
		}
		else
		{
			//弹窗提醒
			closeLoadingProgress();
			LOG(INFO)<<sMsg.toLocal8Bit().data();
			MessageWindow msgWindow(MessageWindow::Warning, this);
			msgWindow.setText(QStringLiteral("%1").arg(sMsg));
			msgWindow.exec();
		}
	}
}

void AIOViewer::onTimeoutHeartbeat()
{
	HeartbeatData heartbeatData;
	heartbeatData.offlineCount = QString::number(m_offlineCount);

	HttpAgent::instance()->RequestOnHeartbeat(heartbeatData, m_interfaceHead);
	m_heartbeatTimes++;
}

void AIOViewer::RespondOnHeartbeat( int nCode, QString sMsg )
{
	if (nCode != e_success)
	{
		m_offlineCount++;
		LOG(INFO)<<"Heartbeat 请求出现异常 -- 错误码: "<<nCode<<", 错误信息: "<<sMsg.toLocal8Bit().data();
	}
	else
	{
		LOG(INFO)<<"Heartbeat 请求成功";
		m_offlineCount = 0;
        TerminateStatusChanged(true);
		closeBubbleTips();
	}

	if (5 == m_offlineCount)  //判断为离线
	{
		LOG(INFO)<<"设备已离线";
		TerminateStatusChanged(false);
		showBubbleTips();
	}
}

void AIOViewer::TerminateStatusChanged( bool onLine )
{
	QString style = onLine ? "border-image:url(:/AIOViewer/Resources/online.png);" : "border-image:url(:/AIOViewer/Resources/offline.png);";
    ui.lbl_devStatus->setStyleSheet(style);
}

void AIOViewer::showBubbleTips()
{
	if (m_arrowWgt == NULL)
	{
		m_arrowWgt = new ArrowWidget(this);
		m_arrowWgt->setDerection(ArrowWidget::right);
		m_arrowWgt->setStartPos(55);
		m_arrowWgt->setTriangleInfo(20, 12);
		m_arrowWgt->setText(QStringLiteral("设备已离线！！！"));
	}
	m_arrowWgt->setGeometry(this->width() - 130 - 88, this->height() - 80 - 6, 130, 80);
	m_arrowWgt->show();
}

void AIOViewer::onToDesktop()
{
	showMinimized();
}

void AIOViewer::slotOnVeinIdentify()
{
	MessageWindow msgWindow(MessageWindow::Information, this);
	msgWindow.setText(QStringLiteral("暂未开放，敬请期待！！！"));
	msgWindow.exec();
}

void AIOViewer::slotOnFingerIdentify()
{
	MessageWindow msgWindow(MessageWindow::Information, this);
	msgWindow.setText(QStringLiteral("暂未开放，敬请期待！！！"));
	msgWindow.exec();
}

void AIOViewer::closeBubbleTips()
{
	if (m_arrowWgt != NULL)
	{
		m_arrowWgt->close();
		m_arrowWgt->deleteLater();
		m_arrowWgt = NULL;
	}
}

void AIOViewer::onButtonActivateOn()
{
	m_counter = TIMING;
}
