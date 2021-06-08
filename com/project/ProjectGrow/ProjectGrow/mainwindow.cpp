
///-------------------------------------------------------------------------------------
/// \brief ArduinoClient::ArduinoClient
/// MainWindow responsible for handling UI interaction with the client
/// Author: Dylan Ilsley
/// -------------------------------------------------------------------------------------
/// SYSTEM INCLUDE FILES
///-------------------------------------------------------------------------------------
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QDebug>
#include <QtConcurrent/QtConcurrent>
/// -------------------------------------------------------------------------------------
/// LOCAL INCLUDE FILES
///-------------------------------------------------------------------------------------
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(const QSettings& Settings, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    m_arduino()
{
    ui->setupUi(this);

   connect(&m_arduino,&ArduinoClient::ArduinoDataReceived, this, &MainWindow::DataReceived);
   connect(this, &MainWindow::LightCycleChanged, ui->widgetAnalogClock, &AnalogClock::LightCycleChanged);


   m_TimeUpdateTracker = new QTimer(this);
   connect(m_TimeUpdateTracker, &QTimer::timeout, this, &MainWindow::RequestTimeUpdateThreadFunction);
   m_TimeUpdateTracker->start(60000);
   // Call immediately
    RequestTimeUpdateThreadFunction();
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
    qDebug() << "Sending current time: " + timeCurrent.toString();

    QString strArduinoCommand = QString::number(timeCurrent.msecsSinceStartOfDay()) + "," + QString::number(timeStart.msecsSinceStartOfDay()) + "," + QString::number(timeStop.msecsSinceStartOfDay());

    // Send the cycle to the arduino
    bool bCommandSent = m_arduino.SendCommand(strArduinoCommand);
    // Issue a warning if the command could not be sent
    if (!bCommandSent)
        QMessageBox::warning(this, "Port Error", "Failed to send cycle to arduino. The arduino might be disconnected");

    return true;
}

void MainWindow::DataReceived(QByteArray readData){
    // NOTE: Must convert to QString to get rid of null terminators, etc

    QString strReadData = QString(readData);
    // Parse into seperate parts
    QStringList strlTimes = strReadData.split(",");
    // Check that the right number of messages have been received
   if (strlTimes.size() == 3){
       // Translate the times into their relevant values
        QTime currentTime = QTime::fromMSecsSinceStartOfDay(strlTimes[0].toInt());
        QTime startTime = QTime::fromMSecsSinceStartOfDay(strlTimes[1].toInt());
        QTime stopTime = QTime::fromMSecsSinceStartOfDay(strlTimes[2].toInt());

        qDebug() << "MainWindow - Current Time reply: " + currentTime.toString();
        qDebug() << "MainWindow - Start Time reply: " + startTime.toString();
        qDebug() << "MainWindow - Stop Time reply: " + stopTime.toString();
        LightCycleChanged(startTime, stopTime);

        // TODO: This should be done through a signal by the analog clock so as to not set the text prematurely?
        SetLightStatus(currentTime > startTime && currentTime < stopTime);

        ui->StartTime->setTime(startTime);
        ui->StopTime->setTime(stopTime);
    }
    else{
        // Display a message since something has gone wrong
        QMessageBox::warning(this, "Port Error", "Failed to understand message received by arduino");
        qDebug() << strReadData;
    }

}

void MainWindow::RequestTimeUpdateThreadFunction(){
    // Send prompt to arduino to establish connection
    m_arduino.SendCommand("SYN");
}


void MainWindow::SetLightStatus(bool bStatus){
    if (bStatus){
        ui->LightStatus->setText("<html><head/><body><p><span style=\" font-size:22pt; font-weight:600; color:#4fa08b;\">ON</span></p></body></html>");
    }
    else{
          ui->LightStatus->setText("<html><head/><body><p><span style=\" font-size:22pt; font-weight:600; color:#aa0000;\">OFF</span></p></body></html>");
    }




}


