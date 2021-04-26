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
     portArduino = new QSerialPort;

     // Cycle through the ports and looks for the arduino
     foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
         if (serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()){
             if (serialPortInfo.vendorIdentifier() == u16unoVendorID && serialPortInfo.productIdentifier() == u16unoProductID){
                strArduinoPortName =  serialPortInfo.portName();
                bArduinoConnected = true;
                break;
             }
         }
     }

     // If the arduino is connected then setup the port
     if (bArduinoConnected){
         // Open and configure the port
         portArduino->setPortName((strArduinoPortName));
         portArduino->open(QSerialPort::ReadWrite);
         portArduino->setBaudRate(QSerialPort::Baud9600);
         portArduino->setDataBits(QSerialPort::Data8);

         portArduino->setParity(QSerialPort::NoParity);
         portArduino->setStopBits(QSerialPort::OneStop);// One and half stop is only available for windows
         portArduino->setFlowControl(QSerialPort::NoFlowControl);

     }
}

ArduinoClient::~ArduinoClient()
{
    // If the port is still open upon destruction, close it
    if (portArduino->isOpen())
        portArduino->close();
    delete portArduino;
}

bool ArduinoClient::SendCommand(QString strCommand)
{
    if (portArduino->isWritable()){
        portArduino->write(strCommand.toStdString().c_str());
        portArduino->close();
    }
    return false;
}

