/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>
#include "analogclock.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QAction *actionOpen_Cycle;
    QAction *actionExit_2;
    QAction *actionSave_Cycle_As;
    QAction *actionExit_3;
    QWidget *centralwidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushCycleButton;
    QPushButton *pushButton_2;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_2;
    AnalogClock *widgetAnalogClock;
    QLabel *LightStatus;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QTimeEdit *StopTime;
    QLabel *label_2;
    QTimeEdit *StartTime;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 420);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionOpen_Cycle = new QAction(MainWindow);
        actionOpen_Cycle->setObjectName(QString::fromUtf8("actionOpen_Cycle"));
        actionExit_2 = new QAction(MainWindow);
        actionExit_2->setObjectName(QString::fromUtf8("actionExit_2"));
        actionSave_Cycle_As = new QAction(MainWindow);
        actionSave_Cycle_As->setObjectName(QString::fromUtf8("actionSave_Cycle_As"));
        actionExit_3 = new QAction(MainWindow);
        actionExit_3->setObjectName(QString::fromUtf8("actionExit_3"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(390, 310, 361, 71));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushCycleButton = new QPushButton(horizontalLayoutWidget);
        pushCycleButton->setObjectName(QString::fromUtf8("pushCycleButton"));
        pushCycleButton->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(5);
        sizePolicy.setHeightForWidth(pushCycleButton->sizePolicy().hasHeightForWidth());
        pushCycleButton->setSizePolicy(sizePolicy);
        pushCycleButton->setFlat(false);

        horizontalLayout->addWidget(pushCycleButton);

        pushButton_2 = new QPushButton(horizontalLayoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setEnabled(false);
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(pushButton_2);

        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(20, 20, 321, 361));
        gridLayout_2 = new QGridLayout(gridLayoutWidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setHorizontalSpacing(0);
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        widgetAnalogClock = new AnalogClock(gridLayoutWidget);
        widgetAnalogClock->setObjectName(QString::fromUtf8("widgetAnalogClock"));
        widgetAnalogClock->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(5);
        sizePolicy2.setHeightForWidth(widgetAnalogClock->sizePolicy().hasHeightForWidth());
        widgetAnalogClock->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(widgetAnalogClock, 0, 0, 1, 1);

        LightStatus = new QLabel(gridLayoutWidget);
        LightStatus->setObjectName(QString::fromUtf8("LightStatus"));
        LightStatus->setAutoFillBackground(false);
        LightStatus->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(LightStatus, 1, 0, 1, 1);

        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(390, 20, 361, 271));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setVerticalSpacing(48);
        gridLayout->setContentsMargins(0, 48, 0, 48);
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        StopTime = new QTimeEdit(layoutWidget);
        StopTime->setObjectName(QString::fromUtf8("StopTime"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(StopTime->sizePolicy().hasHeightForWidth());
        StopTime->setSizePolicy(sizePolicy3);
        StopTime->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        StopTime->setTime(QTime(11, 30, 0));

        gridLayout->addWidget(StopTime, 1, 1, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        StartTime = new QTimeEdit(layoutWidget);
        StartTime->setObjectName(QString::fromUtf8("StartTime"));
        sizePolicy3.setHeightForWidth(StartTime->sizePolicy().hasHeightForWidth());
        StartTime->setSizePolicy(sizePolicy3);
        StartTime->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        StartTime->setDate(QDate(2021, 4, 14));
        StartTime->setCalendarPopup(true);
        StartTime->setTime(QTime(6, 30, 0));

        gridLayout->addWidget(StartTime, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "New Cycle", nullptr));
        actionOpen_Cycle->setText(QCoreApplication::translate("MainWindow", "Open Cycle", nullptr));
        actionExit_2->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        actionSave_Cycle_As->setText(QCoreApplication::translate("MainWindow", "Save As", nullptr));
        actionExit_3->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        pushCycleButton->setText(QCoreApplication::translate("MainWindow", "Push Cycle", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Pause", nullptr));
        LightStatus->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:22pt; font-weight:600; color:#aa0000;\">OFF</span></p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt;\">Stop Time</span></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt;\">Start Time</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
