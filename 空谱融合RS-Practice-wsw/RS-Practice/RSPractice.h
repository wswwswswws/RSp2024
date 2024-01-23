#ifndef  _RS_PRACTICE_RSPRACTICE_H_
#define  _RS_PRACTICE_RSPRACTICE_H_

#include <QtWidgets/QMainWindow>
#include "ui_RSPractice.h"
#include "gdal_priv.h"
#include "armadillo"

using namespace arma;

class RSPractice : public QMainWindow {
    Q_OBJECT

 public:
    explicit RSPractice(QWidget *parent = Q_NULLPTR);

    // �źŲۣ����ؼ������Ĵ����¼�
 private slots:
    void on_mss_clicked();
    void on_pan_clicked();
    void on_pca_clicked();
    void on_gs_clicked();
    void on_ihs_clicked();
    void on_process_clicked();

 private:
    Ui::RSPracticeClass ui;
    // ���Ա�������������Ӱ��·��
    QString mssPath;
    QString panPath;
    QString pcaPath;
    QString gsPath;
    QString ihsPath;
    // �븴ѡ������Ĳ�������
    bool enablepca = false;
    bool enablegs = false;
    bool enableihs = false;
    // ��д����������Ĳ�������
    bool iswritingerror = false;
    // �洢PANӰ��ߴ���Ϣ������
    int rowHeightY;
    int colWidthX;
    int bandNum;
    long bandSize;
    // �洢MSSӰ��ߴ���Ϣ������
    int rowHeightY2;
    int colWidthX2;
    int bandNum2;
    long bandSize2;
    // ָ��ͬ��������ʱ�������������д��
    float* pTempData = nullptr;

private:
    // ����ʵ�ָ��������ںϹ��ܵĺ���
    void ExcutePCA(const fcube& panFcube, const fcube& mssFcube);// ���ɷַ�������
    void ExcuteGS(const fcube& panFcube, const fcube& mssFcube);// Gram-Schmidt����
    void ExcuteIHS(const fcube& panFcube, const fcube& mssFcube);// IHS����
    // �������ܺ���������
    void WriteImage(QString path, int opbandNum);// ͼ��д������
    fcube m2presize(fcube& inputImage);// ר���ڽ�MSS�ϲ�����PAN�ߴ���ϲ���������������˫�����ڲ壩
};

#endif  // _RS_PRACTICE_RSPRACTICE_H_