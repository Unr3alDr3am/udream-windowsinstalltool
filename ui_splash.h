/********************************************************************************
** Form generated from reading UI file 'splash.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPLASH_H
#define UI_SPLASH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_splash
{
public:
    QLabel *label;
    QLabel *label_2;
    QCommandLinkButton *commandLinkButton;
    QToolButton *toolButton;
    QLabel *label_3;
    QComboBox *comboBox;
    QLabel *label_4;
    QComboBox *comboBox_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QProgressBar *progressBar;
    QLabel *label_6;
    QLineEdit *lineEdit;

    void setupUi(QDialog *splash)
    {
        if (splash->objectName().isEmpty())
            splash->setObjectName(QString::fromUtf8("splash"));
        splash->resize(640, 256);
        label = new QLabel(splash);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 20, 621, 16));
        label_2 = new QLabel(splash);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 50, 111, 16));
        commandLinkButton = new QCommandLinkButton(splash);
        commandLinkButton->setObjectName(QString::fromUtf8("commandLinkButton"));
        commandLinkButton->setEnabled(true);
        commandLinkButton->setGeometry(QRect(400, 203, 101, 41));
        commandLinkButton->setStyleSheet(QString::fromUtf8("border-radius:20px;\n"
"background-color:#66ccff;"));
        toolButton = new QToolButton(splash);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        toolButton->setGeometry(QRect(570, 50, 61, 21));
        toolButton->setStyleSheet(QString::fromUtf8("color:#ffffff;\n"
"background-color:#00ff00;\n"
"border-radius:10px;\n"
""));
        label_3 = new QLabel(splash);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 80, 111, 16));
        comboBox = new QComboBox(splash);
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(140, 80, 421, 22));
        label_4 = new QLabel(splash);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 110, 121, 16));
        comboBox_2 = new QComboBox(splash);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(140, 110, 421, 22));
        pushButton = new QPushButton(splash);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(570, 110, 61, 28));
        pushButton->setStyleSheet(QString::fromUtf8("color:#ffffff;\n"
"background-color:#ff0000;\n"
"border-radius:10px;\n"
""));
        pushButton_2 = new QPushButton(splash);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(520, 200, 93, 41));
        pushButton_2->setStyleSheet(QString::fromUtf8("border-radius:20px;\n"
"background-color:#66ccff;\n"
""));
        progressBar = new QProgressBar(splash);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(140, 140, 421, 23));
        progressBar->setStyleSheet(QString::fromUtf8("QProgressBar{\n"
"background-color:#cccccc;\n"
"border-radius:10px;;\n"
"}\n"
"QProgressBar::chunk{\n"
"background-color:#66ccff;\n"
"border-radius:10px;\n"
"}\n"
""));
        progressBar->setMaximum(100);
        progressBar->setValue(-1);
        progressBar->setTextVisible(false);
        label_6 = new QLabel(splash);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 170, 591, 16));
        label_6->setStyleSheet(QString::fromUtf8(""));
        lineEdit = new QLineEdit(splash);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(140, 50, 421, 21));

        retranslateUi(splash);

        QMetaObject::connectSlotsByName(splash);
    } // setupUi

    void retranslateUi(QDialog *splash)
    {
        splash->setWindowTitle(QCoreApplication::translate("splash", "\345\271\273\346\242\246\347\232\204\347\263\273\347\273\237\345\256\211\350\243\205\345\267\245\345\205\267--\346\240\270\345\277\203\347\211\210V1.0\357\274\210\345\237\272\344\272\216WIMGAPI\357\274\214DISMAPI\347\274\226\345\206\231\357\274\211", nullptr));
        label->setText(QCoreApplication::translate("splash", "welcome to use udream windows install tool", nullptr));
        label_2->setText(QCoreApplication::translate("splash", "image file:", nullptr));
        commandLinkButton->setText(QCoreApplication::translate("splash", "install", nullptr));
        toolButton->setText(QCoreApplication::translate("splash", "choose", nullptr));
        label_3->setText(QCoreApplication::translate("splash", "image index:", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("splash", "please choose an image first(support ISO/WIM/VHD)", nullptr));

        label_4->setText(QCoreApplication::translate("splash", "target:", nullptr));
        pushButton->setText(QCoreApplication::translate("splash", "format", nullptr));
        pushButton_2->setText(QCoreApplication::translate("splash", "close", nullptr));
        label_6->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class splash: public Ui_splash {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPLASH_H
