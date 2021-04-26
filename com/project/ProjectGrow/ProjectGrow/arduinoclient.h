#ifndef ARDUINOCLIENT_H
#define ARDUINOCLIENT_H
///-------------------------------------------------------------------------------------
/// \brief ArduinoClient::ArduinoClient
/// ArduinoClient is responsible for handling the communications to any connected arduino
/// Currently only supports arudino uno
/// Author: Dylan Ilsley
/// -------------------------------------------------------------------------------------
/// SYSTEM INCLUDE FILES
///-------------------------------------------------------------------------------------
#include <QtSerialPort/QSerialPort>
#include <QString>
///-------------------------------------------------------------------------------------
/// LOCAL INCLUDE FILES
///-------------------------------------------------------------------------------------

class ArduinoClient
{
public:
    // Constructor
    ArduinoClient();
    // Destructor
    ~ArduinoClient();

    /// IsArduinoConnected is used to tell whether there is currently an arduino connected
    /// @return Returns the connection status of the arduino
    bool IsArduinoConnected() {return bArduinoConnected;}

    /// SendCommand is used to send a string command to the arduino
    /// @param[in] strCommand - the string command that should be sent to the arduino
    /// @return Returns whether the command was sent to the arduino
    bool SendCommand(QString strCommand);
private:
    // ----------------------
    // Const variables
    // ----------------------
    static const quint16 u16unoVendorID = 9025; ///< The vendor identifier provided by an arduino uno
    static const quint16 u16unoProductID = 67; ///< The product identifier provided by an arduino uno
    // ----------------------
    // Member variables
    // ----------------------
    QSerialPort *portArduino; ///< Stores the connectiong to port for the arduino
    QString strArduinoPortName; ///< The port nane of the serial port that the arduino is connected to
    bool bArduinoConnected = false; ///< Whether the arduino is connected or not



};

#endif // ARDUINOCLIENT_H
