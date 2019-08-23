/***********************************************************************************
*								IdentifyDlg.cpp
*
* Copyright(C):	智慧眼科技股份有限公司
*
* Author:  YCL
*
* Date: 2019-06
*
* Description: 认证窗口实例
***********************************************************************************/

#include "IdentifyDlg.h"
#include "CameraReader.h"
#include "EnumData.h"
#include "HttpAgent.h"
#include "PixmapLoader.h"
#include "GlogManager.h"
#include "MessageWindow.h"
#include "CommonConstData.h"

#include <QFile>

#define FaceDevice_Code    2
#define FaceDevice_Name   "F110"

IdentifyDlg::IdentifyDlg(QString sysNo, QString batchId, InterfaceInputHead header, QWidget *parent)
	: QDialog(parent)
	, m_batchId(batchId)
    , m_sysNo(sysNo)
	, m_interfaceHeader(header)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Window);

	InitUI();
	InitConnect();

	if (!CameraReader::instance()->InitSDK(ui.lbl_collect->winId()))
	{
		MessageWindow msgWindow(MessageWindow::Warning, this);
		msgWindow.setText(Str_InitCameraFailed);
		msgWindow.exec();
	}
}

IdentifyDlg::~IdentifyDlg()
{
	
}

void IdentifyDlg::InitUI()
{
	QString commonStyle = "QLabel{font-size:14px;color:white;} QPushButton{background:rgb(0, 144, 216);border-radius:60px;}";
	ui.btn_collect->InitButton(QStringLiteral("开始采集"), ":/AIOViewer/Resources/collect.png", commonStyle);

	ui.widget->hide();
	ui.lbl_tips->setText(QStringLiteral("点击开始采集后请正视摄像头，直至认证完成！！！"));
}

void IdentifyDlg::InitConnect()
{
	connect(ui.btn_return, SIGNAL(clicked()), this, SLOT(onExitIdentify()));
	connect(ui.btn_collect, SIGNAL(clicked()), this, SLOT(onCollect()));

	connect(HttpAgent::instance(), SIGNAL(RespondOnBackendRecognize(int, QString, int)), 
		this, SLOT(RespondOnBackendRecognize(int, QString, int)));
	connect(HttpAgent::instance(), SIGNAL(RespondOnCompleteIdentify(int, QString, int)), 
		this, SLOT(RespondOnCompleteIdentify(int, QString, int)));

	connect(CameraReader::instance(), SIGNAL(onMsgReceived(int, QString)), this, SLOT(onMsgReceived(int, QString)));
	qRegisterMetaType<CameraData>("CameraData");
	connect(CameraReader::instance(), SIGNAL(onCollectFinished(CameraData)), this, SLOT(onCollectFinished(CameraData)));
}

void IdentifyDlg::onExitIdentify()
{
	close();
	CameraReader::instance()->closeCamera();
}

void IdentifyDlg::onCollect()
{
	LOG(INFO)<<"开始摄像头采集...";
	CameraReader::instance()->startCollect();
}

void IdentifyDlg::onMsgReceived( int code, QString msg )
{
	LOG(INFO)<<"摄像头采集异常：code："<<code<<"; errMsg: "<<msg.toLocal8Bit().data();
}

void IdentifyDlg::onCollectFinished( CameraData cameraData )
{
	LOG(INFO)<<"摄像头采集完成...";

// 	QPixmap *p;
// 	p = PixmapLoader::loadFromBase64BMPBuf(cameraData.imageInfoData[0].imageData.toStdString().c_str(), cameraData.imageInfoData[0].imageData.length(), 
// 		ui.lbl_collect_2->size().width(), ui.lbl_collect_2->size().height());
// 	*p = p->scaled(ui.lbl_collect_2->size().width(), ui.lbl_collect_2->size().height() - 2, Qt::KeepAspectRatio);
// 	ui.lbl_collect_2->setPixmap(*p);

    BackendRecognizeData backendRecognizeData;
	BackendRecognizeData::CompareDataItem compareDataItem;
	compareDataItem.bioType = QString::number(BioType_Face);
	compareDataItem.modelType = QString::number(ModelType_VIS);
	compareDataItem.deviceType = FaceDevice_Name;
	compareDataItem.picImage = cameraData.imageInfoData[0].imageData;
	compareDataItem.pics.append(cameraData.imageInfoData[0].imageData);
	compareDataItem.faces.append(cameraData.imageInfoData[0].faceRect);

	backendRecognizeData.sysNo = m_sysNo;
	backendRecognizeData.batchId = m_batchId;
	backendRecognizeData.compareData.append(compareDataItem);
	HttpAgent::instance()->RequestOnBackendRecognize(backendRecognizeData, m_interfaceHeader);
}

void IdentifyDlg::openCamera()
{
	if (!CameraReader::instance()->openCamera())
	{
		MessageWindow msgWindow(MessageWindow::Warning, this);
		msgWindow.setText(Str_OpenCameraFailed);
		msgWindow.exec();
		return;
	}
	showFullScreen();
}

void IdentifyDlg::RespondOnBackendRecognize( int nCode, QString sMsg, int result )
{
	if (nCode != e_success)
	{
		LOG(INFO)<<"BackendRecognize 请求出现异常 -- 错误码: "<<nCode<<", 错误信息: "<<sMsg.toLocal8Bit().data();
		MessageWindow msgWindow(MessageWindow::Warning, this);
		msgWindow.setText(QStringLiteral("网络请求出现异常--错误码:%1, 错误信息:%2").arg(nCode).arg(sMsg));
		msgWindow.exec();
	}
	else
	{
		LOG(INFO)<<"BackendRecognize 请求成功";
		if (result == 1)  //认证成功
		{
			LOG(INFO)<<"后台比对成功";
		}
		else
		{
			LOG(INFO)<<"后台比对失败";
		}

	    onCompleteIdentify(result);
	}
}

void IdentifyDlg::onCompleteIdentify( int result )
{
	CompleteIdentifyData completeIdentifyData;
	completeIdentifyData.sysNo = m_sysNo;
	completeIdentifyData.batchId = m_batchId;

	CompleteIdentifyData::RecognizeDataItem dataItem;
	dataItem.result = QString::number(result);
	dataItem.bioType = QString::number(BioType_Face);
	completeIdentifyData.recognizeData.append(dataItem);
	HttpAgent::instance()->RequestOnCompleteIdentify(completeIdentifyData, m_interfaceHeader);
}

void IdentifyDlg::RespondOnCompleteIdentify( int nCode, QString sMsg, int result )
{
	if (nCode != e_success)
	{
		LOG(INFO)<<"CompleteIdentify 请求出现异常 -- 错误码: "<<nCode<<", 错误信息: "<<sMsg.toLocal8Bit().data();
		MessageWindow msgWindow(MessageWindow::Warning, this);
		msgWindow.setText(QStringLiteral("网络请求出现异常--错误码:%1, 错误信息:%2").arg(nCode).arg(sMsg));
		msgWindow.exec();
	}
	else
	{
		LOG(INFO)<<"CompleteIdentify 请求成功";
		if (result == 1)  //认证成功
		{
			LOG(INFO)<<"后台认证成功";
			MessageWindow msgWindow(MessageWindow::Information, this);
			msgWindow.setText(QStringLiteral("认证成功"));
			msgWindow.exec();
			onExitIdentify();
		}
		else
		{
			LOG(INFO)<<"后台认证失败";
			MessageWindow msgWindow(MessageWindow::Error, this);
			msgWindow.setText(QStringLiteral("认证失败"));
			msgWindow.exec();
		}
	}
}
