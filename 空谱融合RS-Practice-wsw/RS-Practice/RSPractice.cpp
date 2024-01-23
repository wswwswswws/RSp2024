#include "RSPractice.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QString>
#include <QDebug>
#include <cmath>

using namespace arma;

RSPractice ::RSPractice(QWidget *parent)
    : QMainWindow(parent) {
    ui.setupUi(this);
    //ui.lineEdit_input->setEnabled(false);
    //ui.lineEdit_output->setEnabled(false);
    // 复选框与槽连接
    connect(ui.checkBox_pca, &QCheckBox::stateChanged, [=](int state) {
        if (state == Qt::Checked) {
            //qDebug() << "pca复选框已勾选！";
            this->enablepca = true;
        }
        else {
            //qDebug() << "pca复选框未勾选！";
            this->enablepca = false;
        }
        });
    connect(ui.checkBox_gs, &QCheckBox::stateChanged, [=](int state) {
        if (state == Qt::Checked) {
            //qDebug() << "gs复选框已勾选！";
            this->enablegs = true;
        }
        else {
            //qDebug() << "gs复选框未勾选！";
            this->enablegs = false;
        }
        });
    connect(ui.checkBox_ihs, &QCheckBox::stateChanged, [=](int state) {
        if (state == Qt::Checked) {
            //qDebug() << "ihs复选框已勾选！";
            this->enableihs = true;
        }
        else {
            //qDebug() << "ihs复选框未勾选！";
            this->enableihs = false;
        }
        });
    // 信号槽连接
    connect(ui.pushButton_mss, SIGNAL(clicked()), \
    this, SLOT(on_mss_clicked()));
    connect(ui.pushButton_pan, SIGNAL(clicked()), \
        this, SLOT(on_pan_clicked()));
    connect(ui.pushButton_pca, SIGNAL(clicked()), \
        this, SLOT(on_pca_clicked()));
    connect(ui.pushButton_gs, SIGNAL(clicked()), \
    this, SLOT(on_gs_clicked()));
    connect(ui.pushButton_ihs, SIGNAL(clicked()), \
        this, SLOT(on_ihs_clicked()));
    connect(ui.pushButton_process, SIGNAL(clicked()), \
    this, SLOT(on_process_clicked()));
}

void RSPractice::on_mss_clicked() {
    this->mssPath = QFileDialog::getOpenFileName \
    (this, QStringLiteral("选择输入多光谱遥感影像"), "",
        tr("TIFF(*.tif *.tiff);;JPEG(*.jpg *.jpeg);;" "All files(*)"));
    ui.lineEdit_mss->setText(this->mssPath);
}

void RSPractice::on_pan_clicked()
{
    this->panPath = QFileDialog::getOpenFileName \
        (this, QStringLiteral("选择输入全色遥感影像"), "",
            tr("TIFF(*.tif *.tiff);;JPEG(*.jpg *.jpeg);;" "All files(*)"));
    ui.lineEdit_pan->setText(this->panPath);
}

void RSPractice::on_pca_clicked() {
    this->pcaPath = QFileDialog::getSaveFileName \
    (this, QStringLiteral("选择输出遥感影像"), "",
        tr("TIFF(*.tif *.tiff);;JPEG(*.jpg *.jpeg);;" "All files(*)"));
    ui.lineEdit_pca->setText(this->pcaPath);
}

void RSPractice::on_gs_clicked()
{
    this->gsPath = QFileDialog::getSaveFileName \
        (this, QStringLiteral("选择输出遥感影像"), "",
            tr("TIFF(*.tif *.tiff);;JPEG(*.jpg *.jpeg);;" "All files(*)"));
    ui.lineEdit_gs->setText(this->gsPath);
}

void RSPractice::on_ihs_clicked()
{
    this->ihsPath = QFileDialog::getSaveFileName \
        (this, QStringLiteral("选择输出遥感影像"), "",
            tr("TIFF(*.tif *.tiff);;JPEG(*.jpg *.jpeg);;" "All files(*)"));
    ui.lineEdit_ihs->setText(this->ihsPath);
}

void RSPractice::on_process_clicked() {
    // **************1-从GDAL中读取影像像素到数组************************//
    // 打开影像，获取数据集
    GDALDataset *poDataset;
    GDALAllRegister();
    CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");    // 设置GDAL支持中文路径
    // **********首先读取的是全色影像PAN
    poDataset = (GDALDataset *)GDALOpen \
    (this->panPath.toStdString().c_str(), GA_ReadOnly);
    if (poDataset == NULL) {
        QMessageBox::warning(this, "Warning", "Invaild input file name.");
        return;
    }
    // 获取影像尺寸信息
    rowHeightY = poDataset->GetRasterYSize();
    colWidthX = poDataset->GetRasterXSize();
    bandNum = poDataset->GetRasterCount();
    bandSize = rowHeightY*colWidthX;
    // 读取影像像素数据到数组
    float *pPanData = new float[rowHeightY * colWidthX * bandNum];
    int* panBandMap = new int[bandNum];
    for (int i = 0; i < bandNum; ++i)
        panBandMap[i] = i + 1;
    if (poDataset->RasterIO(GF_Read, 0, 0, colWidthX, rowHeightY, \
    pPanData, colWidthX, rowHeightY, \
    GDT_Float32, bandNum, panBandMap, 0, 0, 0) != CE_None)
        return;

    // **********第二个读取多光谱影像MSS
    poDataset = NULL;
    poDataset = (GDALDataset*)GDALOpen \
        (this->mssPath.toStdString().c_str(), GA_ReadOnly);
    if (poDataset == NULL) {
        QMessageBox::warning(this, "Warning", "Invaild input file name.");
        return;
    }
    // 获取影像尺寸信息
    rowHeightY2 = poDataset->GetRasterYSize();
    colWidthX2 = poDataset->GetRasterXSize();
    bandNum2 = poDataset->GetRasterCount();
    bandSize2 = rowHeightY2 * colWidthX2;
    // 读取影像像素数据到数组
    float* pMssData = new float[rowHeightY2 * colWidthX2 * bandNum2];
    int* panBandMap2 = new int[bandNum2];
    for (int i = 0; i < bandNum2; ++i)
        panBandMap2[i] = i + 1;
    if (poDataset->RasterIO(GF_Read, 0, 0, colWidthX2, rowHeightY2, \
        pMssData, colWidthX2, rowHeightY2, \
        GDT_Float32, bandNum2, panBandMap2, 0, 0, 0) != CE_None)
        return;
    // 关闭数据集
    GDALClose((GDALDatasetH)poDataset);

    // PAN:影像像素数组存储行主序--列主序
    float *pPanProcessData = new float[rowHeightY * colWidthX * bandNum];
    for (int b = 0; b < bandNum; ++b)
        for (int i = 0; i < rowHeightY; ++i)
            for (int j = 0; j < colWidthX; ++j)
                pPanProcessData[b*bandSize + j*rowHeightY + i] = \
                    pPanData[b*bandSize + i*colWidthX + j];
    // MSS:影像像素数组存储行主序--列主序
    float* pMssProcessData = new float[rowHeightY2 * colWidthX2 * bandNum2];
    for (int b = 0; b < bandNum2; ++b)
        for (int i = 0; i < rowHeightY2; ++i)
            for (int j = 0; j < colWidthX2; ++j)
                pMssProcessData[b * bandSize2 + j * rowHeightY2 + i] = \
                pMssData[b * bandSize2 + i * colWidthX2 + j];

    // PAN:将像素数组初始化为ammadillo中的多维矩阵数据结构
    fcube panFcube(pPanProcessData, rowHeightY, colWidthX, bandNum);
    // 输出部分像素值
    /*for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j)
            qDebug() << panFcube(i, j, 0) << " ";
        qDebug() << "\n";
    }*/
    // MSS:将像素数组初始化为ammadillo中的多维矩阵数据结构
    fcube mssFcube(pMssProcessData, rowHeightY2, colWidthX2, bandNum2);
    // 输出部分像素值
    /*for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j)
            qDebug() << mssFcube(i, j, 0) << " ";
        qDebug() << "\n";
    }*/

    // **************2-图像处理和写入结果************************//
    // MSS上采样
    mssFcube = m2presize(mssFcube);

    // MSS:将图像缩放到范围 [0, 1]
    for (uword i = 0; i < bandNum2; i++)
    {
        fmat band = mssFcube.slice(i);
        float minVal = band.min();
        float maxVal = band.max();

        mssFcube.slice(i) = (band - minVal) / (maxVal - minVal);
    }
    // PAN:将图像缩放到范围 [0, 1]
    for (uword i = 0; i < bandNum; i++)
    {
        fmat band = panFcube.slice(i);
        float minVal = band.min();
        float maxVal = band.max();

        panFcube.slice(i) = (band - minVal) / (maxVal - minVal);
    }
 
    // 执行空谱融合
    if (enablepca) ExcutePCA(panFcube, mssFcube);
    if (enablegs) ExcuteGS(panFcube, mssFcube);
    if (enableihs) ExcuteIHS(panFcube, mssFcube);
    
    // 清理内存
    delete[] pPanData;
    delete[] pMssData;
    delete[] panBandMap;
    delete[] panBandMap2;
    delete[] pPanProcessData;
    delete[] pMssProcessData;
    
    // 处理提示
    if (!iswritingerror) QMessageBox::information(this, "Information", "Successfully!");
}

void RSPractice::ExcutePCA(const fcube& panFcube, const fcube& mssFcube)
{
    // 创建临时多维矩阵防止改变输入矩阵影响其他函数使用
    fcube tempan = panFcube;
    fcube temmss = mssFcube;

    // 重新构造矩阵
    uword numRows = temmss.n_rows;
    uword nunCols = temmss.n_cols;
    uword numBands = temmss.n_slices;
    fmat data = join_rows(vectorise(temmss.slice(0)), vectorise(temmss.slice(1)));
    for (uword i = 2; i < numBands; i++) {
        data = join_rows(data, vectorise(temmss.slice(i)));
    }
    // 进行主成分分析
    fmat coeff;
    fmat score;
    fmat mu = zeros<fvec>(numBands).t();
    mu = mean(data, 0);
    princomp(coeff, score, data);
    fvec first_component = score.col(0);
    // 计算全色影像的均值和方差
    float PAN_mean = mean(vectorise(tempan));
    float PAN_std = stddev(vectorise(tempan));
    // 计算第一主成分的均值和方差
    float first_component_mean = mean(first_component);
    float first_component_std = stddev(first_component);
    // 将全色影像与第一主成分进行匹配
    fmat PAN_matched = ((tempan - PAN_mean) * (first_component_std / PAN_std)) + first_component_mean;
    score.col(0) = vectorise(PAN_matched);
    // 主成分逆变换并进行矩匹配
    fmat MSS_fused_vectorized = score * coeff.t() + repmat(mu, numRows * nunCols, 1);
    fcube MSS_fused(numRows, nunCols, numBands);
    for (uword i = 0; i < numBands; i++)
    {
        MSS_fused.slice(i) = reshape(MSS_fused_vectorized.col(i), numRows, nunCols);
    }

    // 初始化拉伸后的图像
    fcube MSS_stretched(numRows, nunCols, numBands, fill::zeros);
    
    // 对每个波段进行线性拉伸
    for (uword i = 0; i < numBands; i++)
    {
        fmat band = MSS_fused.slice(i);
        float minVal = band.min();
        float maxVal = band.max();

        MSS_stretched.slice(i) = (band - minVal) * (255.0 / (maxVal - minVal));
    }
    fcube MSS_RGB = join_slices(MSS_stretched.slice(2), MSS_stretched.slice(1));
    MSS_RGB = join_slices(MSS_RGB, MSS_stretched.slice(0));

    // 获取多维矩阵的数据裸指针
    pTempData = MSS_RGB.memptr();
    // 写出影像
    int opbandNum = MSS_RGB.n_slices;
    WriteImage(pcaPath, opbandNum);
}

void RSPractice::ExcuteGS(const fcube& panFcube, const fcube& mssFcube)
{
    // 创建临时多维矩阵防止改变输入矩阵影响其他函数使用
    fcube tempan = panFcube;
    fcube temmss = mssFcube;
    
    // 计算辅助波段 I（这里采用多光谱影像波段直接取均值作为辅助波段）
    fmat I = zeros<fmat>(rowHeightY, colWidthX);
    I = mean(temmss, 2);
    //qDebug() << "I rows: " << I.n_rows;
    //qDebug() << "I cols: " << I.n_cols;
    
    // 对多光谱影像和模拟的全色影像进行Gram-Schmidt正交变换
    // 初始化Gram-Schmidt分量矩阵
    fcube gs(rowHeightY, colWidthX, bandNum2, fill::zeros);
    // 第一个分量为模拟的全色影像
    gs.slice(0) = I;
    // 对每个多光谱波段进行循环
    for (uword i = 1; i < bandNum2; i++)
    {
        // 取出当前波段
        fmat band = temmss.slice(i);
        // 初始化投影矩阵
        fmat proj(rowHeightY, colWidthX, fill::zeros);
        // 对之前的分量进行循环
        for (uword j = 0; j < i; j++) {
            // 取出当前分量
            fmat comp = gs.slice(j);
            //qDebug() << "i,j:" << i << j;
            // 计算当前波段在当前分量上的投影
            fmat numerator = vectorise(band).t() * vectorise(comp);
            fmat denominator = vectorise(comp).t() * vectorise(comp);
            float nu = numerator(0, 0);
            float de = denominator(0, 0);
            proj = (nu / de) * comp;
        }
        // 当前波段减去投影得到正交的分量
        gs.slice(i) = band - proj;
    }
    // 用高分辨率的全色影像替换第一个分量
    gs.slice(0) = tempan;

    // 对替换后的分量进行Gram-Schmidt逆变换
    // 初始化融合后的多光谱影像
    fcube fused(rowHeightY, colWidthX, bandNum2, fill::zeros);
    // 第一个波段为替换后的全色影像
    fused.slice(0) = gs.slice(0);
    // 对每个多光谱波段进行循环
    for (uword i = 1; i < bandNum2; i++)
    {
        // 取出前一个波段
        fmat band = fused.slice(i - 1);
        // 取出当前分量
        fmat comp = gs.slice(i);
        // 当前波段为前一个波段加上当前分量
        fused.slice(i) = band + comp;
    }

    // 拉伸
    for (uword i = 0; i < fused.n_slices; i++)
    {
        float minVal = fused.slice(i).min();
        float maxVal = fused.slice(i).max();

        fused.slice(i) = (fused.slice(i) - minVal) * (255.0 / (maxVal - minVal));
    }
    
    // 获取多维矩阵的数据裸指针
    pTempData = fused.memptr();

    // 写出影像
    int opbandNum = fused.n_slices;
    WriteImage(gsPath, opbandNum);
}

void RSPractice::ExcuteIHS(const fcube& panFcube, const fcube& mssFcube)
{
    // 创建临时多维矩阵防止改变输入矩阵影响其他函数使用
    fcube tempan = panFcube;
    fcube temmss = mssFcube;

    // Step 1: RGB到IHS变换
    fmat red_band = temmss.slice(0);
    fmat green_band = temmss.slice(1);
    fmat blue_band = temmss.slice(2);

    fmat I = (1.0 / 3.0) * (red_band + green_band + blue_band);
    fmat gamma1 = (-sqrt(2.0) / 6.0) * red_band + (-sqrt(2.0) / 6.0) * green_band + (2.0 * sqrt(2.0) / 6.0) * blue_band;
    fmat gamma2 = (1.0 / sqrt(2.0)) * red_band - (1.0 / sqrt(2.0)) * green_band;

    fmat H = atan2(gamma2, gamma1);
    fmat S = sqrt(gamma1 % gamma1 + gamma2 % gamma2); 

    // Step 2: 矩匹配
    float mean_pan = mean(vectorise(tempan));
    float std_pan = stddev(vectorise(tempan));

    float mean_I = mean(vectorise(I));
    float std_I = stddev(vectorise(I));

    fmat matched_pan = (std_I / std_pan) * (tempan - mean_pan) + mean_I;

    // Step 3: 替换亮度分量
    fmat x1 = matched_pan + (-1.0 / sqrt(2.0)) * gamma1 + (1.0 / sqrt(2.0)) * gamma2;
    fmat x2 = matched_pan + (-1.0 / sqrt(2.0)) * gamma1 + (-1.0 / sqrt(2.0)) * gamma2;
    fmat x3 = matched_pan + sqrt(2.0) * gamma1;

    // 组合三个波段得到融合影像
    fcube fusion_image = join_slices(x1, x2);
    fusion_image = join_slices(fusion_image, x3);

    // 拉伸
    for (uword i = 0; i < fusion_image.n_slices; i++)
    {
        float minVal = fusion_image.slice(i).min();
        float maxVal = fusion_image.slice(i).max();

        fusion_image.slice(i) = (fusion_image.slice(i) - minVal) * (255.0 / (maxVal - minVal));
    }

    // 获取多维矩阵的数据裸指针
    pTempData = fusion_image.memptr();

    // 写出影像
    int opbandNum = fusion_image.n_slices;
    WriteImage(ihsPath, opbandNum);
}

void RSPractice::WriteImage(QString path, int opbandNum)
{
    // **************写出影像************************//
    // 创建数据集
    const char* pszFormat = "GTiff";
    GDALDriver* poDriver;
    char** papszMetadata;
    poDriver = GetGDALDriverManager()->GetDriverByName(pszFormat);
    GDALDataset* poDstDS;
    char** papszOptions = NULL;
    // 更新结果矩阵尺寸信息（op：OutPut）
    int* oppanBandMap = new int[opbandNum];
    for (int i = 0; i < opbandNum; ++i)
        oppanBandMap[i] = i + 1;
    poDstDS = poDriver->Create(path.toStdString().c_str(), \
        colWidthX, rowHeightY, opbandNum, GDT_Float32, papszOptions);
    // 影像像素数组存储列主序--行主序
    float* pOutputData = new float[rowHeightY * colWidthX * opbandNum];
    for (int b = 0; b < opbandNum; ++b)
        for (int i = 0; i < rowHeightY; ++i)
            for (int j = 0; j < colWidthX; ++j)
                pOutputData[b * bandSize + i * colWidthX + j] = \
                pTempData[b * bandSize + j * rowHeightY + i];
    // 写出数据
    if (poDstDS->RasterIO(GF_Write, 0, 0, colWidthX, rowHeightY, pOutputData, \
        colWidthX, rowHeightY, GDT_Float32, opbandNum, \
        oppanBandMap, 0, 0, 0) != CE_None) {
        QMessageBox::warning(this, "Warning", "Write raster failed.");
        iswritingerror = true;
    }
    // 关闭数据集
    GDALClose((GDALDatasetH)poDstDS);
    // 重置pResData
    pTempData = nullptr;
    // 清理内存
    delete[] oppanBandMap;
    delete[] pOutputData;
}

fcube RSPractice::m2presize(fcube& inputImage)// Armadillo中没有较好的插值方法，因此自定义双线性插值方法函数
{
    // 创建缩放后的图像矩阵（大小使用PAN尺寸信息，波段数保持MSS信息
    fcube resizedmss(rowHeightY, colWidthX, bandNum2);
    
    // 计算缩放因子
    float scaleRow = static_cast<float>(rowHeightY2) / (rowHeightY);
    float scaleCol = static_cast<float>(colWidthX2) / (colWidthX);

    // 进行双线性插值
    for (size_t i = 0; i < rowHeightY; i++) {
        float f_h = i * scaleRow;
        int s_h = floor(f_h);// 取整
        f_h -= s_h;// 小数部分
        // 判断超出边界
        if (s_h < 0) {
            f_h = 0, s_h = 0;
        }
        if (s_h >= rowHeightY2 - 1) {
            f_h = 1, s_h = rowHeightY2 - 2;
        }
        for (size_t j = 0; j < colWidthX; j++) {
            float f_w = j * scaleCol;
            int s_w = floor(f_w);// 取整
            f_w -= s_w;// 小数部分
            // 判断超出边界
            if (s_w < 0) {
                f_w = 0, s_w = 0;
            }
            if (s_w >= colWidthX2 - 1) {
                f_w = 1, s_w = colWidthX2 - 2;
            }

            // 插值
            for (size_t band = 0; band < bandNum2; band++) {
                resizedmss(i, j, band) = (1 - f_h) * (1 - f_w) * inputImage(s_h, s_w, band) + \
                    (1 - f_h) * f_w * inputImage(s_h, s_w + 1, band) + \
                    f_h * (1 - f_w) * inputImage(s_h + 1, s_w, band) + \
                    f_h * f_w * inputImage(s_h + 1, s_w + 1, band);
            }
        }
    }

    return resizedmss;
}








