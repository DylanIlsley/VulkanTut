///-------------------------------------------------------------------------------------
/// \brief ArduinoClient::ArduinoClient
/// ArduinoClient is responsible for handling the communications to any connected arduino
/// Author: Dylan Ilsley
///-------------------------------------------------------------------------------------
/// SYSTEM INCLUDE FILES
///-------------------------------------------------------------------------------------
#include <QtSerialPort/QtSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include <QDebug>
/// LOCAL INCLUDE FILES
///-------------------------------------------------------------------------------------
#include "arduinoclient.h"



ArduinoClient::ArduinoClient(QObject* parent):
    QObject(parent)
{
    // Setup port for arduino
     m_portArduino = new QSerialPort;

     // Cycle through the ports and looks for the arduino
     foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
         if (serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()){
             if (serialPortInfo.vendorIdentifier() == u16unoVendorID && serialPortInfo.productIdentifier() == u16unoProductID){
                m_strArduinoPortName =  serialPortInfo.portName();
                m_bArduinoConnected = true;
                break;
             }
         }
     }

     // If the arduino is connected then setup the port
     if (m_bArduinoConnected){
         // Open and configure the port
         m_portArduino->setPortName((m_strArduinoPortName));
         m_portArduino->open(QSerialPort::ReadWrite);
         m_portArduino->setBaudRate(QSerialPort::Baud9600);
         m_portArduino->setDataBits(QSerialPort::Data8);

         m_portArduino->setParity(QSerialPort::NoParity);
         m_portArduino->setStopBits(QSerialPort::OneStop);// One and half stop is only available for windows
         m_portArduino->setFlowControl(QSerialPort::NoFlowControl);



     }
    // TODO: Confirm whether the port has to be set up first for this
    connect(m_portArduino, &QSerialPort::readyRead, this, &ArduinoClient::HandleReadyRead);
    // Send the error directly to the user of the arduino client, currently do not have any need to use it
    // TODO: Use the errors within the class to try repair issues without needing to exclaim it
    connect(m_portArduino, &QSerialPort::errorOccurred, this, &ArduinoClient::ErrorOccurred);
}

ArduinoClient::~ArduinoClient()
{
    // If the port is still open upon destruction, close it
    if (m_portArduino->isOpen())
        m_portArduino->close();
    delete m_portArduino;
}

bool ArduinoClient::SendCommand(QString strCommand)
{

    strCommand += "\n";
    if (m_portArduino->isWritable()){
        m_portArduino->write(strCommand.toStdString().c_str());
        return true;
    }
    return false;
}

void ArduinoClient::HandleReadyRead()
{
    // Append to data buffer until a new line character has been received
     m_DataBuffer +=  m_portArduino->readAll();
     if (m_DataBuffer.contains("\n")){
         // TODO: Look for a function to copy up until the first instance and then remove that section from the array. Eg: 123\n24\n => 24\n in array
         m_DataBuffer.chop(1);
         ArduinoDataReceived(m_DataBuffer);
         // Empty buffer for next command
         m_DataBuffer.clear();
     }

}


