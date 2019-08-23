#ifndef AIOVIEWER_H
#define AIOVIEWER_H

#include <QtWidgets/QMainWindow>
#include <QTimer>
#include <QStateMachine>
#include <QState>
#include "ui_AIOViewer.h"
#include "HttpStructData.h"

#define TIMING 60    //��¼�Ƴ���ʱ
#define TERM_VERSION "v1.0.0"   //�ն˰汾��

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
	//�����˵�¼Ӧ��
	void RespondOnOperatorLogin(int nCode, QString sMsg, QString sessionId);
	//��ȡ������ϢӦ��
	void RespondOnGetBaseInfo(int nCode, QString sMsg, ModelStatus modelStatus, QString sysNo);
	//��ȡ���֤��ƬӦ��
	void RespondOnGetIdCardPic(int nCode, QString sMsg, QString picData);
	//�Ƿ�����֤Ӧ��
	void RespondOnIfCanIdentify(int nCode, QString sMsg, bool successed, QString batchId);
    //����Ӧ��
	void RespondOnHeartbeat(int nCode, QString sMsg);

	//ѡ�����֤��¼
	void slotOnLoginByIdCard();
	//ѡ���籣����¼
	void slotOnLoginBySiCard();
	//������ҳ
	void slotOnBackHomePage();
	//��ʾ������֤����
	void slotOnFaceIdentify();
	//��ʾָ������֤����
	void slotOnVeinIdentify();
	//��ʾָ����֤����
	void slotOnFingerIdentify();
	//��Ȩ
	void slotOnAuthorizate();
	//��Ȩ���
	void slotOnAuthorizateFinished();
	//��ʾ��֤ѡ��ҳ��
	void showIdentifySelectedPage();
    //�����ɹ�
	void onReadCardSuccessed(AuthReadCardResult readCardResult);
	//����ʧ��
	void onReadCardFailed(int errCode);
	//�����ʼ��״̬
	void onEnterInitState();
	//�����û�����״̬
	void onEnterWorkState();
	//�Ƴ��û�����״̬
    void onExitWorkState();
	//������ʱ��Ӧ
	void onTimeoutHeartbeat();
	//��ʱ����Ӧ
	void onTimeoutFunc();
	//��������
	void onToDesktop();

	void onButtonActivateOn();

signals:
	//�л�����ʼ��״̬
	void TranslateToInitState();
	//�л����û�����״̬
	void TranslateToWorkState();

private:
	//��ʼ��UI
	void InitUI();
	//ˢ��UI
	void UpdateUI(ModelStatus modelStatus);
	//��ʼ������
	void InitConnect();
	//��ʼ��״̬��
	void InitStateMachine();
	//��ʼ����ʱ��
	void InitTimer();
	//��ȡ��ť״̬
	QString getButtonStyle(bool status);
	QString getButtonModelStatus(bool status, QString& style);
	//�ն�״̬�ı�
	void TerminateStatusChanged(bool onLine);
	//��ʾ���ݵ���
	void showBubbleTips();
	//�ر����ݵ���
	void closeBubbleTips();

private slots:
	//��ʾ���ؿ�
	void showLoadingProgress(QString loadingText);
	//�رռ��ؿ�
	void closeLoadingProgress();

private:
	Ui::AIOViewerClass ui;
	/***�������*****/
	QTimer* m_heartbeat_timer;  //������ʱ��
	int m_heartbeatTimes;       //��������
	int m_offlineCount;         //���ߴ���

	QTimer* m_count_timer;      //��ʱ�Ƴ���ʱ��
	int m_counter;              //�Ƴ���ʱ
	QString m_sysNo;            //ϵͳ���

	InterfaceInputHead m_interfaceHead;    
	AuthReadCardResult m_readCardResult;

	IdentifyDlg* m_identifyDlg;
	LoadingWindow* m_loadingDlg;
	AuthorizateDlg* m_authorizateDlg;
	SystemSettingsDlg* m_settingsDlg;
	ArrowWidget* m_arrowWgt;

	//״̬��
	QStateMachine *m_stateMachine;  
	QState* m_InitState;
	QState* m_WorkState;
};

#endif // AIOVIEWER_H
