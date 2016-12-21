/********************************************************************************
** Form generated from reading UI file 'QtZipTool.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTZIPTOOL_H
#define UI_QTZIPTOOL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtZipToolClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QLineEdit *lineEdit_zip;
    QPushButton *pushButton_sel_zip;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *lineEdit_unzip;
    QPushButton *pushButton_sel_unzip;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_4;
    QProgressBar *progressBar;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_zip;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_unzip;
    QSpacerItem *horizontalSpacer_3;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtZipToolClass)
    {
        if (QtZipToolClass->objectName().isEmpty())
            QtZipToolClass->setObjectName(QStringLiteral("QtZipToolClass"));
        QtZipToolClass->resize(438, 280);
        centralWidget = new QWidget(QtZipToolClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_4->addWidget(label);

        lineEdit_zip = new QLineEdit(centralWidget);
        lineEdit_zip->setObjectName(QStringLiteral("lineEdit_zip"));
        lineEdit_zip->setEnabled(true);
        lineEdit_zip->setEchoMode(QLineEdit::Normal);
        lineEdit_zip->setReadOnly(true);

        horizontalLayout_4->addWidget(lineEdit_zip);

        pushButton_sel_zip = new QPushButton(centralWidget);
        pushButton_sel_zip->setObjectName(QStringLiteral("pushButton_sel_zip"));

        horizontalLayout_4->addWidget(pushButton_sel_zip);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_3->addWidget(label_2);

        lineEdit_unzip = new QLineEdit(centralWidget);
        lineEdit_unzip->setObjectName(QStringLiteral("lineEdit_unzip"));
        lineEdit_unzip->setEnabled(true);
        lineEdit_unzip->setReadOnly(true);

        horizontalLayout_3->addWidget(lineEdit_unzip);

        pushButton_sel_unzip = new QPushButton(centralWidget);
        pushButton_sel_unzip->setObjectName(QStringLiteral("pushButton_sel_unzip"));

        horizontalLayout_3->addWidget(pushButton_sel_unzip);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(0);

        horizontalLayout_2->addWidget(progressBar);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pushButton_zip = new QPushButton(centralWidget);
        pushButton_zip->setObjectName(QStringLiteral("pushButton_zip"));

        horizontalLayout->addWidget(pushButton_zip);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_unzip = new QPushButton(centralWidget);
        pushButton_unzip->setObjectName(QStringLiteral("pushButton_unzip"));

        horizontalLayout->addWidget(pushButton_unzip);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        QtZipToolClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QtZipToolClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 438, 23));
        QtZipToolClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtZipToolClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QtZipToolClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QtZipToolClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QtZipToolClass->setStatusBar(statusBar);

        retranslateUi(QtZipToolClass);

        QMetaObject::connectSlotsByName(QtZipToolClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtZipToolClass)
    {
        QtZipToolClass->setWindowTitle(QApplication::translate("QtZipToolClass", "QtZipTool", 0));
        label->setText(QApplication::translate("QtZipToolClass", "\345\216\213\347\274\251\357\274\232", 0));
        pushButton_sel_zip->setText(QApplication::translate("QtZipToolClass", "\351\200\211\346\213\251", 0));
        label_2->setText(QApplication::translate("QtZipToolClass", "\350\247\243\345\216\213\357\274\232", 0));
        pushButton_sel_unzip->setText(QApplication::translate("QtZipToolClass", "\351\200\211\346\213\251", 0));
#ifndef QT_NO_TOOLTIP
        progressBar->setToolTip(QApplication::translate("QtZipToolClass", "\350\277\233\345\272\246", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        pushButton_zip->setToolTip(QApplication::translate("QtZipToolClass", "\346\211\247\350\241\214\345\216\213\347\274\251", 0));
#endif // QT_NO_TOOLTIP
        pushButton_zip->setText(QApplication::translate("QtZipToolClass", "\345\216\213\347\274\251", 0));
#ifndef QT_NO_TOOLTIP
        pushButton_unzip->setToolTip(QApplication::translate("QtZipToolClass", "\346\211\247\350\241\214\350\247\243\345\216\213", 0));
#endif // QT_NO_TOOLTIP
        pushButton_unzip->setText(QApplication::translate("QtZipToolClass", "\350\247\243\345\216\213", 0));
    } // retranslateUi

};

namespace Ui {
    class QtZipToolClass: public Ui_QtZipToolClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTZIPTOOL_H
