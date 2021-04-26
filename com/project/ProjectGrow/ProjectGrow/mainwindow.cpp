
///-------------------------------------------------------------------------------------
/// \brief ArduinoClient::ArduinoClient
/// MainWindow responsible for handling UI interaction with the client
/// Author: Dylan Ilsley
/// -------------------------------------------------------------------------------------
/// SYSTEM INCLUDE FILES
///-------------------------------------------------------------------------------------
#include <QSerialPortInfo>
#include <QMessageBox>
#include<QDebug>
/// -------------------------------------------------------------------------------------
/// LOCAL INCLUDE FILES
///-------------------------------------------------------------------------------------
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushCycleButton_clicked()
{
    // Get the needed time values to be pushed to the arduino
    QTime timeStart = ui->StartTime->time();
    QTime timeStop = ui->StopTime->time();

    PushCycleToArduino(timeStart, timeStop);
}

bool MainWindow::PushCycleToArduino(QTime timeStart, QTime timeStop)
{
    // Get the current time for the arduino
    // NOTE: This is done here instead of by the function caller to keep the arduino time as close as possible to real-time
    QTime timeCurrent = QTime::currentTime();

    QString strArduinoCommand = timeCurrent.toString() + "," + timeStart.toString() + "," + timeStop.toString();
    // Send the cycle to the arduino
    bool bCommandSent = m_arduino.SendCommand(strArduinoCommand);
    // Issue a warning if the command could not be sent
    if (!bCommandSent)
        QMessageBox::warning(this, "Port Error", "Failed to send cycle to arduino. The arduino might be disconnected");

    return bCommandSent;
}


