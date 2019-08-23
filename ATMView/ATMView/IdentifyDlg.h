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

	//�����
	void openCamera();
private:
	void InitUI();
	void InitConnect();
	void onCompleteIdentify(int result);    //�����֤

private slots:
	//�˳���֤
	void onExitIdentify();
	//�ɼ�
	void onCollect();
	void onMsgReceived(int code, QString msg);
	void onCollectFinished(CameraData cameraData);

	//��̨�ȶ�����Ӧ��
	void RespondOnBackendRecognize(int nCode, QString sMsg, int result);
	//�����֤����Ӧ��
	void RespondOnCompleteIdentify(int nCode, QString sMsg, int result);

private:
	Ui::IdentifyDlg ui;
	InterfaceInputHead m_interfaceHeader;

	QString m_sysNo;
	QString m_batchId;
};

#endif // IDENTIFYDLG_H
