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
    // ��ѡ���������
    connect(ui.checkBox_pca, &QCheckBox::stateChanged, [=](int state) {
        if (state == Qt::Checked) {
            //qDebug() << "pca��ѡ���ѹ�ѡ��";
            this->enablepca = true;
        }
        else {
            //qDebug() << "pca��ѡ��δ��ѡ��";
            this->enablepca = false;
        }
        });
    connect(ui.checkBox_gs, &QCheckBox::stateChanged, [=](int state) {
        if (state == Qt::Checked) {
            //qDebug() << "gs��ѡ���ѹ�ѡ��";
            this->enablegs = true;
        }
        else {
            //qDebug() << "gs��ѡ��δ��ѡ��";
            this->enablegs = false;
        }
        });
    connect(ui.checkBox_ihs, &QCheckBox::stateChanged, [=](int state) {
        if (state == Qt::Checked) {
            //qDebug() << "ihs��ѡ���ѹ�ѡ��";
            this->enableihs = true;
        }
        else {
            //qDebug() << "ihs��ѡ��δ��ѡ��";
            this->enableihs = false;
        }
        });
    // �źŲ�����
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
    (this, QStringLiteral("ѡ����������ң��Ӱ��"), "",
        tr("TIFF(*.tif *.tiff);;JPEG(*.jpg *.jpeg);;" "All files(*)"));
    ui.lineEdit_mss->setText(this->mssPath);
}

void RSPractice::on_pan_clicked()
{
    this->panPath = QFileDialog::getOpenFileName \
        (this, QStringLiteral("ѡ������ȫɫң��Ӱ��"), "",
            tr("TIFF(*.tif *.tiff);;JPEG(*.jpg *.jpeg);;" "All files(*)"));
    ui.lineEdit_pan->setText(this->panPath);
}

void RSPractice::on_pca_clicked() {
    this->pcaPath = QFileDialog::getSaveFileName \
    (this, QStringLiteral("ѡ�����ң��Ӱ��"), "",
        tr("TIFF(*.tif *.tiff);;JPEG(*.jpg *.jpeg);;" "All files(*)"));
    ui.lineEdit_pca->setText(this->pcaPath);
}

void RSPractice::on_gs_clicked()
{
    this->gsPath = QFileDialog::getSaveFileName \
        (this, QStringLiteral("ѡ�����ң��Ӱ��"), "",
            tr("TIFF(*.tif *.tiff);;JPEG(*.jpg *.jpeg);;" "All files(*)"));
    ui.lineEdit_gs->setText(this->gsPath);
}

void RSPractice::on_ihs_clicked()
{
    this->ihsPath = QFileDialog::getSaveFileName \
        (this, QStringLiteral("ѡ�����ң��Ӱ��"), "",
            tr("TIFF(*.tif *.tiff);;JPEG(*.jpg *.jpeg);;" "All files(*)"));
    ui.lineEdit_ihs->setText(this->ihsPath);
}

void RSPractice::on_process_clicked() {
    // **************1-��GDAL�ж�ȡӰ�����ص�����************************//
    // ��Ӱ�񣬻�ȡ���ݼ�
    GDALDataset *poDataset;
    GDALAllRegister();
    CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");    // ����GDAL֧������·��
    // **********���ȶ�ȡ����ȫɫӰ��PAN
    poDataset = (GDALDataset *)GDALOpen \
    (this->panPath.toStdString().c_str(), GA_ReadOnly);
    if (poDataset == NULL) {
        QMessageBox::warning(this, "Warning", "Invaild input file name.");
        return;
    }
    // ��ȡӰ��ߴ���Ϣ
    rowHeightY = poDataset->GetRasterYSize();
    colWidthX = poDataset->GetRasterXSize();
    bandNum = poDataset->GetRasterCount();
    bandSize = rowHeightY*colWidthX;
    // ��ȡӰ���������ݵ�����
    float *pPanData = new float[rowHeightY * colWidthX * bandNum];
    int* panBandMap = new int[bandNum];
    for (int i = 0; i < bandNum; ++i)
        panBandMap[i] = i + 1;
    if (poDataset->RasterIO(GF_Read, 0, 0, colWidthX, rowHeightY, \
    pPanData, colWidthX, rowHeightY, \
    GDT_Float32, bandNum, panBandMap, 0, 0, 0) != CE_None)
        return;

    // **********�ڶ�����ȡ�����Ӱ��MSS
    poDataset = NULL;
    poDataset = (GDALDataset*)GDALOpen \
        (this->mssPath.toStdString().c_str(), GA_ReadOnly);
    if (poDataset == NULL) {
        QMessageBox::warning(this, "Warning", "Invaild input file name.");
        return;
    }
    // ��ȡӰ��ߴ���Ϣ
    rowHeightY2 = poDataset->GetRasterYSize();
    colWidthX2 = poDataset->GetRasterXSize();
    bandNum2 = poDataset->GetRasterCount();
    bandSize2 = rowHeightY2 * colWidthX2;
    // ��ȡӰ���������ݵ�����
    float* pMssData = new float[rowHeightY2 * colWidthX2 * bandNum2];
    int* panBandMap2 = new int[bandNum2];
    for (int i = 0; i < bandNum2; ++i)
        panBandMap2[i] = i + 1;
    if (poDataset->RasterIO(GF_Read, 0, 0, colWidthX2, rowHeightY2, \
        pMssData, colWidthX2, rowHeightY2, \
        GDT_Float32, bandNum2, panBandMap2, 0, 0, 0) != CE_None)
        return;
    // �ر����ݼ�
    GDALClose((GDALDatasetH)poDataset);

    // PAN:Ӱ����������洢������--������
    float *pPanProcessData = new float[rowHeightY * colWidthX * bandNum];
    for (int b = 0; b < bandNum; ++b)
        for (int i = 0; i < rowHeightY; ++i)
            for (int j = 0; j < colWidthX; ++j)
                pPanProcessData[b*bandSize + j*rowHeightY + i] = \
                    pPanData[b*bandSize + i*colWidthX + j];
    // MSS:Ӱ����������洢������--������
    float* pMssProcessData = new float[rowHeightY2 * colWidthX2 * bandNum2];
    for (int b = 0; b < bandNum2; ++b)
        for (int i = 0; i < rowHeightY2; ++i)
            for (int j = 0; j < colWidthX2; ++j)
                pMssProcessData[b * bandSize2 + j * rowHeightY2 + i] = \
                pMssData[b * bandSize2 + i * colWidthX2 + j];

    // PAN:�����������ʼ��Ϊammadillo�еĶ�ά�������ݽṹ
    fcube panFcube(pPanProcessData, rowHeightY, colWidthX, bandNum);
    // �����������ֵ
    /*for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j)
            qDebug() << panFcube(i, j, 0) << " ";
        qDebug() << "\n";
    }*/
    // MSS:�����������ʼ��Ϊammadillo�еĶ�ά�������ݽṹ
    fcube mssFcube(pMssProcessData, rowHeightY2, colWidthX2, bandNum2);
    // �����������ֵ
    /*for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j)
            qDebug() << mssFcube(i, j, 0) << " ";
        qDebug() << "\n";
    }*/

    // **************2-ͼ�����д����************************//
    // MSS�ϲ���
    mssFcube = m2presize(mssFcube);

    // MSS:��ͼ�����ŵ���Χ [0, 1]
    for (uword i = 0; i < bandNum2; i++)
    {
        fmat band = mssFcube.slice(i);
        float minVal = band.min();
        float maxVal = band.max();

        mssFcube.slice(i) = (band - minVal) / (maxVal - minVal);
    }
    // PAN:��ͼ�����ŵ���Χ [0, 1]
    for (uword i = 0; i < bandNum; i++)
    {
        fmat band = panFcube.slice(i);
        float minVal = band.min();
        float maxVal = band.max();

        panFcube.slice(i) = (band - minVal) / (maxVal - minVal);
    }
 
    // ִ�п����ں�
    if (enablepca) ExcutePCA(panFcube, mssFcube);
    if (enablegs) ExcuteGS(panFcube, mssFcube);
    if (enableihs) ExcuteIHS(panFcube, mssFcube);
    
    // �����ڴ�
    delete[] pPanData;
    delete[] pMssData;
    delete[] panBandMap;
    delete[] panBandMap2;
    delete[] pPanProcessData;
    delete[] pMssProcessData;
    
    // ������ʾ
    if (!iswritingerror) QMessageBox::information(this, "Information", "Successfully!");
}

void RSPractice::ExcutePCA(const fcube& panFcube, const fcube& mssFcube)
{
    // ������ʱ��ά�����ֹ�ı��������Ӱ����������ʹ��
    fcube tempan = panFcube;
    fcube temmss = mssFcube;

    // ���¹������
    uword numRows = temmss.n_rows;
    uword nunCols = temmss.n_cols;
    uword numBands = temmss.n_slices;
    fmat data = join_rows(vectorise(temmss.slice(0)), vectorise(temmss.slice(1)));
    for (uword i = 2; i < numBands; i++) {
        data = join_rows(data, vectorise(temmss.slice(i)));
    }
    // �������ɷַ���
    fmat coeff;
    fmat score;
    fmat mu = zeros<fvec>(numBands).t();
    mu = mean(data, 0);
    princomp(coeff, score, data);
    fvec first_component = score.col(0);
    // ����ȫɫӰ��ľ�ֵ�ͷ���
    float PAN_mean = mean(vectorise(tempan));
    float PAN_std = stddev(vectorise(tempan));
    // �����һ���ɷֵľ�ֵ�ͷ���
    float first_component_mean = mean(first_component);
    float first_component_std = stddev(first_component);
    // ��ȫɫӰ�����һ���ɷֽ���ƥ��
    fmat PAN_matched = ((tempan - PAN_mean) * (first_component_std / PAN_std)) + first_component_mean;
    score.col(0) = vectorise(PAN_matched);
    // ���ɷ���任�����о�ƥ��
    fmat MSS_fused_vectorized = score * coeff.t() + repmat(mu, numRows * nunCols, 1);
    fcube MSS_fused(numRows, nunCols, numBands);
    for (uword i = 0; i < numBands; i++)
    {
        MSS_fused.slice(i) = reshape(MSS_fused_vectorized.col(i), numRows, nunCols);
    }

    // ��ʼ��������ͼ��
    fcube MSS_stretched(numRows, nunCols, numBands, fill::zeros);
    
    // ��ÿ�����ν�����������
    for (uword i = 0; i < numBands; i++)
    {
        fmat band = MSS_fused.slice(i);
        float minVal = band.min();
        float maxVal = band.max();

        MSS_stretched.slice(i) = (band - minVal) * (255.0 / (maxVal - minVal));
    }
    fcube MSS_RGB = join_slices(MSS_stretched.slice(2), MSS_stretched.slice(1));
    MSS_RGB = join_slices(MSS_RGB, MSS_stretched.slice(0));

    // ��ȡ��ά�����������ָ��
    pTempData = MSS_RGB.memptr();
    // д��Ӱ��
    int opbandNum = MSS_RGB.n_slices;
    WriteImage(pcaPath, opbandNum);
}

void RSPractice::ExcuteGS(const fcube& panFcube, const fcube& mssFcube)
{
    // ������ʱ��ά�����ֹ�ı��������Ӱ����������ʹ��
    fcube tempan = panFcube;
    fcube temmss = mssFcube;
    
    // ���㸨������ I��������ö����Ӱ�񲨶�ֱ��ȡ��ֵ��Ϊ�������Σ�
    fmat I = zeros<fmat>(rowHeightY, colWidthX);
    I = mean(temmss, 2);
    //qDebug() << "I rows: " << I.n_rows;
    //qDebug() << "I cols: " << I.n_cols;
    
    // �Զ����Ӱ���ģ���ȫɫӰ�����Gram-Schmidt�����任
    // ��ʼ��Gram-Schmidt��������
    fcube gs(rowHeightY, colWidthX, bandNum2, fill::zeros);
    // ��һ������Ϊģ���ȫɫӰ��
    gs.slice(0) = I;
    // ��ÿ������ײ��ν���ѭ��
    for (uword i = 1; i < bandNum2; i++)
    {
        // ȡ����ǰ����
        fmat band = temmss.slice(i);
        // ��ʼ��ͶӰ����
        fmat proj(rowHeightY, colWidthX, fill::zeros);
        // ��֮ǰ�ķ�������ѭ��
        for (uword j = 0; j < i; j++) {
            // ȡ����ǰ����
            fmat comp = gs.slice(j);
            //qDebug() << "i,j:" << i << j;
            // ���㵱ǰ�����ڵ�ǰ�����ϵ�ͶӰ
            fmat numerator = vectorise(band).t() * vectorise(comp);
            fmat denominator = vectorise(comp).t() * vectorise(comp);
            float nu = numerator(0, 0);
            float de = denominator(0, 0);
            proj = (nu / de) * comp;
        }
        // ��ǰ���μ�ȥͶӰ�õ������ķ���
        gs.slice(i) = band - proj;
    }
    // �ø߷ֱ��ʵ�ȫɫӰ���滻��һ������
    gs.slice(0) = tempan;

    // ���滻��ķ�������Gram-Schmidt��任
    // ��ʼ���ںϺ�Ķ����Ӱ��
    fcube fused(rowHeightY, colWidthX, bandNum2, fill::zeros);
    // ��һ������Ϊ�滻���ȫɫӰ��
    fused.slice(0) = gs.slice(0);
    // ��ÿ������ײ��ν���ѭ��
    for (uword i = 1; i < bandNum2; i++)
    {
        // ȡ��ǰһ������
        fmat band = fused.slice(i - 1);
        // ȡ����ǰ����
        fmat comp = gs.slice(i);
        // ��ǰ����Ϊǰһ�����μ��ϵ�ǰ����
        fused.slice(i) = band + comp;
    }

    // ����
    for (uword i = 0; i < fused.n_slices; i++)
    {
        float minVal = fused.slice(i).min();
        float maxVal = fused.slice(i).max();

        fused.slice(i) = (fused.slice(i) - minVal) * (255.0 / (maxVal - minVal));
    }
    
    // ��ȡ��ά�����������ָ��
    pTempData = fused.memptr();

    // д��Ӱ��
    int opbandNum = fused.n_slices;
    WriteImage(gsPath, opbandNum);
}

void RSPractice::ExcuteIHS(const fcube& panFcube, const fcube& mssFcube)
{
    // ������ʱ��ά�����ֹ�ı��������Ӱ����������ʹ��
    fcube tempan = panFcube;
    fcube temmss = mssFcube;

    // Step 1: RGB��IHS�任
    fmat red_band = temmss.slice(0);
    fmat green_band = temmss.slice(1);
    fmat blue_band = temmss.slice(2);

    fmat I = (1.0 / 3.0) * (red_band + green_band + blue_band);
    fmat gamma1 = (-sqrt(2.0) / 6.0) * red_band + (-sqrt(2.0) / 6.0) * green_band + (2.0 * sqrt(2.0) / 6.0) * blue_band;
    fmat gamma2 = (1.0 / sqrt(2.0)) * red_band - (1.0 / sqrt(2.0)) * green_band;

    fmat H = atan2(gamma2, gamma1);
    fmat S = sqrt(gamma1 % gamma1 + gamma2 % gamma2); 

    // Step 2: ��ƥ��
    float mean_pan = mean(vectorise(tempan));
    float std_pan = stddev(vectorise(tempan));

    float mean_I = mean(vectorise(I));
    float std_I = stddev(vectorise(I));

    fmat matched_pan = (std_I / std_pan) * (tempan - mean_pan) + mean_I;

    // Step 3: �滻���ȷ���
    fmat x1 = matched_pan + (-1.0 / sqrt(2.0)) * gamma1 + (1.0 / sqrt(2.0)) * gamma2;
    fmat x2 = matched_pan + (-1.0 / sqrt(2.0)) * gamma1 + (-1.0 / sqrt(2.0)) * gamma2;
    fmat x3 = matched_pan + sqrt(2.0) * gamma1;

    // ����������εõ��ں�Ӱ��
    fcube fusion_image = join_slices(x1, x2);
    fusion_image = join_slices(fusion_image, x3);

    // ����
    for (uword i = 0; i < fusion_image.n_slices; i++)
    {
        float minVal = fusion_image.slice(i).min();
        float maxVal = fusion_image.slice(i).max();

        fusion_image.slice(i) = (fusion_image.slice(i) - minVal) * (255.0 / (maxVal - minVal));
    }

    // ��ȡ��ά�����������ָ��
    pTempData = fusion_image.memptr();

    // д��Ӱ��
    int opbandNum = fusion_image.n_slices;
    WriteImage(ihsPath, opbandNum);
}

void RSPractice::WriteImage(QString path, int opbandNum)
{
    // **************д��Ӱ��************************//
    // �������ݼ�
    const char* pszFormat = "GTiff";
    GDALDriver* poDriver;
    char** papszMetadata;
    poDriver = GetGDALDriverManager()->GetDriverByName(pszFormat);
    GDALDataset* poDstDS;
    char** papszOptions = NULL;
    // ���½������ߴ���Ϣ��op��OutPut��
    int* oppanBandMap = new int[opbandNum];
    for (int i = 0; i < opbandNum; ++i)
        oppanBandMap[i] = i + 1;
    poDstDS = poDriver->Create(path.toStdString().c_str(), \
        colWidthX, rowHeightY, opbandNum, GDT_Float32, papszOptions);
    // Ӱ����������洢������--������
    float* pOutputData = new float[rowHeightY * colWidthX * opbandNum];
    for (int b = 0; b < opbandNum; ++b)
        for (int i = 0; i < rowHeightY; ++i)
            for (int j = 0; j < colWidthX; ++j)
                pOutputData[b * bandSize + i * colWidthX + j] = \
                pTempData[b * bandSize + j * rowHeightY + i];
    // д������
    if (poDstDS->RasterIO(GF_Write, 0, 0, colWidthX, rowHeightY, pOutputData, \
        colWidthX, rowHeightY, GDT_Float32, opbandNum, \
        oppanBandMap, 0, 0, 0) != CE_None) {
        QMessageBox::warning(this, "Warning", "Write raster failed.");
        iswritingerror = true;
    }
    // �ر����ݼ�
    GDALClose((GDALDatasetH)poDstDS);
    // ����pResData
    pTempData = nullptr;
    // �����ڴ�
    delete[] oppanBandMap;
    delete[] pOutputData;
}

fcube RSPractice::m2presize(fcube& inputImage)// Armadillo��û�нϺõĲ�ֵ����������Զ���˫���Բ�ֵ��������
{
    // �������ź��ͼ����󣨴�Сʹ��PAN�ߴ���Ϣ������������MSS��Ϣ
    fcube resizedmss(rowHeightY, colWidthX, bandNum2);
    
    // ������������
    float scaleRow = static_cast<float>(rowHeightY2) / (rowHeightY);
    float scaleCol = static_cast<float>(colWidthX2) / (colWidthX);

    // ����˫���Բ�ֵ
    for (size_t i = 0; i < rowHeightY; i++) {
        float f_h = i * scaleRow;
        int s_h = floor(f_h);// ȡ��
        f_h -= s_h;// С������
        // �жϳ����߽�
        if (s_h < 0) {
            f_h = 0, s_h = 0;
        }
        if (s_h >= rowHeightY2 - 1) {
            f_h = 1, s_h = rowHeightY2 - 2;
        }
        for (size_t j = 0; j < colWidthX; j++) {
            float f_w = j * scaleCol;
            int s_w = floor(f_w);// ȡ��
            f_w -= s_w;// С������
            // �жϳ����߽�
            if (s_w < 0) {
                f_w = 0, s_w = 0;
            }
            if (s_w >= colWidthX2 - 1) {
                f_w = 1, s_w = colWidthX2 - 2;
            }

            // ��ֵ
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








