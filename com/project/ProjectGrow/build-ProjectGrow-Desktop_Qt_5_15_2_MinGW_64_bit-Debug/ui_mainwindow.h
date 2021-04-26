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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
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
    QTimeEdit *StartTime;
    QTimeEdit *StopTime;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *pushCycleButton;
    QComboBox *comboBox;
    QLabel *label_5;
    AnalogClock *widgetAnalogClock;
    QPushButton *pushButton_2;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(591, 350);
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
        StartTime = new QTimeEdit(centralwidget);
        StartTime->setObjectName(QString::fromUtf8("StartTime"));
        StartTime->setGeometry(QRect(400, 100, 100, 22));
        StartTime->setDate(QDate(2021, 4, 14));
        StartTime->setCalendarPopup(true);
        StartTime->setTime(QTime(6, 30, 0));
        StopTime = new QTimeEdit(centralwidget);
        StopTime->setObjectName(QString::fromUtf8("StopTime"));
        StopTime->setGeometry(QRect(400, 150, 100, 22));
        StopTime->setTime(QTime(11, 30, 0));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(300, 100, 70, 20));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(300, 150, 70, 20));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(80, 250, 80, 50));
        label_4->setAutoFillBackground(true);
        label_4->setAlignment(Qt::AlignCenter);
        pushCycleButton = new QPushButton(centralwidget);
        pushCycleButton->setObjectName(QString::fromUtf8("pushCycleButton"));
        pushCycleButton->setEnabled(true);
        pushCycleButton->setGeometry(QRect(280, 250, 111, 41));
        pushCycleButton->setFlat(false);
        comboBox = new QComboBox(centralwidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(400, 20, 121, 22));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(300, 20, 51, 20));
        widgetAnalogClock = new AnalogClock(centralwidget);
        widgetAnalogClock->setObjectName(QString::fromUtf8("widgetAnalogClock"));
        widgetAnalogClock->setGeometry(QRect(20, 10, 200, 200));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setEnabled(false);
        pushButton_2->setGeometry(QRect(430, 250, 111, 41));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 591, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionExit);
        menuFile->addAction(actionOpen_Cycle);
        menuFile->addAction(actionExit_2);
        menuFile->addAction(actionSave_Cycle_As);
        menuFile->addAction(actionExit_3);

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
        label_2->setText(QCoreApplication::translate("MainWindow", "Start Time", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Stop Time", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:22pt; font-weight:600; color:#aa0000;\">OFF</span></p></body></html>", nullptr));
        pushCycleButton->setText(QCoreApplication::translate("MainWindow", "Push Cycle", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Light Cycle", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Pause", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
