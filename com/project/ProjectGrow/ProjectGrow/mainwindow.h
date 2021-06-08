#ifndef MAINWINDOW_H
#define MAINWINDOW_H
///-------------------------------------------------------------------------------------
/// \brief ArduinoClient::ArduinoClient
/// MainWindow responsible for handling UI interaction with the client
/// Author: Dylan Ilsley
/// -------------------------------------------------------------------------------------
/// SYSTEM INCLUDE FILES
///-------------------------------------------------------------------------------------
#include <QMainWindow>
#include <QSettings>
#include <QThread>
#include <QTime>
/// -------------------------------------------------------------------------------------
/// LOCAL INCLUDE FILES
///-------------------------------------------------------------------------------------
#include "arduinoclient.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const QSettings& Settings, QWidget *parent = nullptr);
    ~MainWindow();




signals:
    void LightCycleChanged(QTime StartTime, QTime StopTime);

private slots:
    /// This slot is responsible for grabbing the needed time data for the arduino and pushing the cycle to the arduino
    void on_pushCycleButton_clicked();
     void DataReceived(QByteArray readData);


private:
    //TODO: A secondary function should be made for receiving ACKs from the Raspberry pi in order to know that commands were received properly. Requires further investigaiton into QSerialPort first

    /// PushCycleToArduino is reponsible for handling the serial writing to a connected arduino
    /// @param[in] timeStart - the time that the light cycle should start the 'on' state
    /// @param[out] timeStop - the time that the light cycle should stop the 'on' state
    /// @return Returns whether the function was able to push the cycle onto the arduino
    bool PushCycleToArduino(QTime timeStart, QTime timeStop);

    void RequestTimeUpdateThreadFunction();

    void SetLightStatus(bool bStatus);

    //Member variables
    Ui::MainWindow *ui;
    ArduinoClient m_arduino;
    QSettings m_Settings; ///< Local store of the application settings
    QTimer* m_TimeUpdateTracker;
};
#endif // MAINWINDOW_H
