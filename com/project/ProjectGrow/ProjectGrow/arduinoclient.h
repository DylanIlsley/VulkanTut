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
#include <QObject>
///-------------------------------------------------------------------------------------
/// LOCAL INCLUDE FILES
///-------------------------------------------------------------------------------------

class ArduinoClient : public QObject
{
    Q_OBJECT
public:
    // Constructor
    explicit ArduinoClient(QObject * parent = 0);
    // Destructor
    ~ArduinoClient();

    /// IsArduinoConnected is used to tell whether there is currently an arduino connected
    /// @return Returns the connection status of the arduino
    bool IsArduinoConnected() {return m_bArduinoConnected;}

    /// SendCommand is used to send a string command to the arduino
    /// @param[in] strCommand - the string command that should be sent to the arduino
    /// @return Returns whether the command was sent to the arduino
    bool SendCommand(QString strCommand);

signals:
    // TODO: Change the byte array to something more user friendly - like a string or byte
    void ArduinoDataReceived(QByteArray readData);
    // TODO: Think about expansion so multiple instances of arduino client can be supported with different port names
    void ErrorOccurred(QSerialPort::SerialPortError SerialPortError);

private:
    // ----------------------
    // Input handling functions
    // ----------------------
    void HandleReadyRead();

    // ----------------------
    // Const variables
    // ----------------------
    static const quint16 u16unoVendorID = 9025; ///< The vendor identifier provided by an arduino uno
    static const quint16 u16unoProductID = 67; ///< The product identifier provided by an arduino uno
    // ----------------------
    // Member variables
    // ----------------------
    QSerialPort *m_portArduino; ///< Stores the connectiong to port for the arduino
    QString m_strArduinoPortName; ///< The port nane of the serial port that the arduino is connected to
    bool m_bArduinoConnected = false; ///< Whether the arduino is connected or not

    QByteArray m_DataBuffer;


};

#endif // ARDUINOCLIENT_H