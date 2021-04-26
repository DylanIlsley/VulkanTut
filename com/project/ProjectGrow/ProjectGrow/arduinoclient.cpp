///-------------------------------------------------------------------------------------
/// \brief ArduinoClient::ArduinoClient
/// ArduinoClient is responsible for handling the communications to any connected arduino
/// Author: Dylan Ilsley
///-------------------------------------------------------------------------------------
/// SYSTEM INCLUDE FILES
///-------------------------------------------------------------------------------------
#include <QtSerialPort/QtSerialPort>
#include <QtSerialPort/QSerialPortInfo>
/// LOCAL INCLUDE FILES
///-------------------------------------------------------------------------------------
#include "arduinoclient.h"



ArduinoClient::ArduinoClient()
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
    if (m_portArduino->isWritable()){
        m_portArduino->write(strCommand.toStdString().c_str());
    }
    return false;
}

