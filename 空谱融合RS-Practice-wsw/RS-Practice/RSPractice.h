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

    // 信号槽，即控件出发的处理事件
 private slots:
    void on_mss_clicked();
    void on_pan_clicked();
    void on_pca_clicked();
    void on_gs_clicked();
    void on_ihs_clicked();
    void on_process_clicked();

 private:
    Ui::RSPracticeClass ui;
    // 类成员变量，输入输出影像路径
    QString mssPath;
    QString panPath;
    QString pcaPath;
    QString gsPath;
    QString ihsPath;
    // 与复选框关联的布尔变量
    bool enablepca = false;
    bool enablegs = false;
    bool enableihs = false;
    // 与写出错误关联的布尔变量
    bool iswritingerror = false;
    // 存储PAN影像尺寸信息及索引
    int rowHeightY;
    int colWidthX;
    int bandNum;
    long bandSize;
    // 存储MSS影像尺寸信息及索引
    int rowHeightY2;
    int colWidthX2;
    int bandNum2;
    long bandSize2;
    // 指向不同方法的临时结果，帮助数据写入
    float* pTempData = nullptr;

private:
    // 声明实现各方法的融合功能的函数
    void ExcutePCA(const fcube& panFcube, const fcube& mssFcube);// 主成分分析方法
    void ExcuteGS(const fcube& panFcube, const fcube& mssFcube);// Gram-Schmidt方法
    void ExcuteIHS(const fcube& panFcube, const fcube& mssFcube);// IHS方法
    // 辅助功能函数的声明
    void WriteImage(QString path, int opbandNum);// 图像写出函数
    fcube m2presize(fcube& inputImage);// 专用于将MSS上采样至PAN尺寸的上采样函数（方法：双线性内插）
};

#endif  // _RS_PRACTICE_RSPRACTICE_H_