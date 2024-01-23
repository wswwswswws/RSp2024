/********************************************************************************
** Form generated from reading UI file 'RSPractice.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RSPRACTICE_H
#define UI_RSPRACTICE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RSPracticeClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_input_mss;
    QLineEdit *lineEdit_mss;
    QPushButton *pushButton_mss;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_input_pan;
    QLineEdit *lineEdit_pan;
    QPushButton *pushButton_pan;
    QLabel *label_text;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *checkBox_pca;
    QLabel *label_pca;
    QLineEdit *lineEdit_pca;
    QPushButton *pushButton_pca;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *checkBox_gs;
    QLabel *label_gs;
    QLineEdit *lineEdit_gs;
    QPushButton *pushButton_gs;
    QHBoxLayout *horizontalLayout_5;
    QCheckBox *checkBox_ihs;
    QLabel *label_ihs;
    QLineEdit *lineEdit_ihs;
    QPushButton *pushButton_ihs;
    QPushButton *pushButton_process;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *RSPracticeClass)
    {
        if (RSPracticeClass->objectName().isEmpty())
            RSPracticeClass->setObjectName(QString::fromUtf8("RSPracticeClass"));
        RSPracticeClass->resize(876, 586);
        centralWidget = new QWidget(RSPracticeClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_input_mss = new QLabel(centralWidget);
        label_input_mss->setObjectName(QString::fromUtf8("label_input_mss"));

        horizontalLayout->addWidget(label_input_mss);

        lineEdit_mss = new QLineEdit(centralWidget);
        lineEdit_mss->setObjectName(QString::fromUtf8("lineEdit_mss"));

        horizontalLayout->addWidget(lineEdit_mss);

        pushButton_mss = new QPushButton(centralWidget);
        pushButton_mss->setObjectName(QString::fromUtf8("pushButton_mss"));

        horizontalLayout->addWidget(pushButton_mss);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_input_pan = new QLabel(centralWidget);
        label_input_pan->setObjectName(QString::fromUtf8("label_input_pan"));

        horizontalLayout_2->addWidget(label_input_pan);

        lineEdit_pan = new QLineEdit(centralWidget);
        lineEdit_pan->setObjectName(QString::fromUtf8("lineEdit_pan"));

        horizontalLayout_2->addWidget(lineEdit_pan);

        pushButton_pan = new QPushButton(centralWidget);
        pushButton_pan->setObjectName(QString::fromUtf8("pushButton_pan"));

        horizontalLayout_2->addWidget(pushButton_pan);


        verticalLayout->addLayout(horizontalLayout_2);

        label_text = new QLabel(centralWidget);
        label_text->setObjectName(QString::fromUtf8("label_text"));

        verticalLayout->addWidget(label_text);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        checkBox_pca = new QCheckBox(centralWidget);
        checkBox_pca->setObjectName(QString::fromUtf8("checkBox_pca"));

        horizontalLayout_3->addWidget(checkBox_pca);

        label_pca = new QLabel(centralWidget);
        label_pca->setObjectName(QString::fromUtf8("label_pca"));

        horizontalLayout_3->addWidget(label_pca);

        lineEdit_pca = new QLineEdit(centralWidget);
        lineEdit_pca->setObjectName(QString::fromUtf8("lineEdit_pca"));

        horizontalLayout_3->addWidget(lineEdit_pca);

        pushButton_pca = new QPushButton(centralWidget);
        pushButton_pca->setObjectName(QString::fromUtf8("pushButton_pca"));

        horizontalLayout_3->addWidget(pushButton_pca);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        checkBox_gs = new QCheckBox(centralWidget);
        checkBox_gs->setObjectName(QString::fromUtf8("checkBox_gs"));

        horizontalLayout_4->addWidget(checkBox_gs);

        label_gs = new QLabel(centralWidget);
        label_gs->setObjectName(QString::fromUtf8("label_gs"));

        horizontalLayout_4->addWidget(label_gs);

        lineEdit_gs = new QLineEdit(centralWidget);
        lineEdit_gs->setObjectName(QString::fromUtf8("lineEdit_gs"));

        horizontalLayout_4->addWidget(lineEdit_gs);

        pushButton_gs = new QPushButton(centralWidget);
        pushButton_gs->setObjectName(QString::fromUtf8("pushButton_gs"));

        horizontalLayout_4->addWidget(pushButton_gs);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        checkBox_ihs = new QCheckBox(centralWidget);
        checkBox_ihs->setObjectName(QString::fromUtf8("checkBox_ihs"));

        horizontalLayout_5->addWidget(checkBox_ihs);

        label_ihs = new QLabel(centralWidget);
        label_ihs->setObjectName(QString::fromUtf8("label_ihs"));

        horizontalLayout_5->addWidget(label_ihs);

        lineEdit_ihs = new QLineEdit(centralWidget);
        lineEdit_ihs->setObjectName(QString::fromUtf8("lineEdit_ihs"));

        horizontalLayout_5->addWidget(lineEdit_ihs);

        pushButton_ihs = new QPushButton(centralWidget);
        pushButton_ihs->setObjectName(QString::fromUtf8("pushButton_ihs"));

        horizontalLayout_5->addWidget(pushButton_ihs);


        verticalLayout->addLayout(horizontalLayout_5);

        pushButton_process = new QPushButton(centralWidget);
        pushButton_process->setObjectName(QString::fromUtf8("pushButton_process"));

        verticalLayout->addWidget(pushButton_process);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        RSPracticeClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(RSPracticeClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 876, 22));
        RSPracticeClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(RSPracticeClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        RSPracticeClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(RSPracticeClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        RSPracticeClass->setStatusBar(statusBar);

        retranslateUi(RSPracticeClass);

        QMetaObject::connectSlotsByName(RSPracticeClass);
    } // setupUi

    void retranslateUi(QMainWindow *RSPracticeClass)
    {
        RSPracticeClass->setWindowTitle(QCoreApplication::translate("RSPracticeClass", "RSPractice", nullptr));
        label_input_mss->setText(QCoreApplication::translate("RSPracticeClass", "\350\276\223\345\205\245\357\274\210\345\244\232\345\205\211\350\260\261\357\274\211\357\274\232  ", nullptr));
        pushButton_mss->setText(QCoreApplication::translate("RSPracticeClass", "\351\200\211\346\213\251", nullptr));
        label_input_pan->setText(QCoreApplication::translate("RSPracticeClass", "\350\276\223\345\205\245\357\274\210\345\205\250\350\211\262\357\274\211\357\274\232    ", nullptr));
        pushButton_pan->setText(QCoreApplication::translate("RSPracticeClass", "\351\200\211\346\213\251", nullptr));
        label_text->setText(QCoreApplication::translate("RSPracticeClass", "\351\200\211\346\213\251\350\236\215\345\220\210\346\226\271\345\274\217\357\274\232", nullptr));
        checkBox_pca->setText(QCoreApplication::translate("RSPracticeClass", "PCA\357\274\210\344\270\273\346\210\220\345\210\206\345\210\206\346\236\220\357\274\211    ", nullptr));
        label_pca->setText(QCoreApplication::translate("RSPracticeClass", "\350\276\223\345\207\272\350\267\257\345\276\204\357\274\232", nullptr));
        pushButton_pca->setText(QCoreApplication::translate("RSPracticeClass", "\351\200\211\346\213\251", nullptr));
        checkBox_gs->setText(QCoreApplication::translate("RSPracticeClass", "GS\357\274\210Gram-Schmidt\357\274\211   ", nullptr));
        label_gs->setText(QCoreApplication::translate("RSPracticeClass", "\350\276\223\345\207\272\350\267\257\345\276\204\357\274\232", nullptr));
        pushButton_gs->setText(QCoreApplication::translate("RSPracticeClass", "\351\200\211\346\213\251", nullptr));
        checkBox_ihs->setText(QCoreApplication::translate("RSPracticeClass", "IHS                  ", nullptr));
        label_ihs->setText(QCoreApplication::translate("RSPracticeClass", "\350\276\223\345\207\272\350\267\257\345\276\204\357\274\232", nullptr));
        pushButton_ihs->setText(QCoreApplication::translate("RSPracticeClass", "\351\200\211\346\213\251", nullptr));
        pushButton_process->setText(QCoreApplication::translate("RSPracticeClass", "\345\244\204\347\220\206", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RSPracticeClass: public Ui_RSPracticeClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RSPRACTICE_H
