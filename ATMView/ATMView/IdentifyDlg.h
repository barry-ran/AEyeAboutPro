#ifndef IDENTIFYDLG_H
#define IDENTIFYDLG_H

#include <QDialog>

#include "HttpStructData.h"
#include "ui_IdentifyDlg.h"

class IdentifyDlg : public QDialog
{
	Q_OBJECT

public:
	IdentifyDlg(QString sysNo, QString batchId, InterfaceInputHead header, QWidget *parent = 0);
	~IdentifyDlg();

	//打开相机
	void openCamera();
private:
	void InitUI();
	void InitConnect();
	void onCompleteIdentify(int result);    //完成认证

private slots:
	//退出认证
	void onExitIdentify();
	//采集
	void onCollect();
	void onMsgReceived(int code, QString msg);
	void onCollectFinished(CameraData cameraData);

	//后台比对请求应答
	void RespondOnBackendRecognize(int nCode, QString sMsg, int result);
	//完成认证请求应答
	void RespondOnCompleteIdentify(int nCode, QString sMsg, int result);

private:
	Ui::IdentifyDlg ui;
	InterfaceInputHead m_interfaceHeader;

	QString m_sysNo;
	QString m_batchId;
};

#endif // IDENTIFYDLG_H
