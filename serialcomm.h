#ifndef SERIALCOMM_H
#define SERIALCOMM_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

typedef enum SerialError
{
    SE_NOT_FOUND=1,
    SE_ERROR_OPEN=2,
    SE_ERROR_CLOSE=3,
    SE_ERROR_READ =4,
    SE_ERROR_WRITE=5,
    SE_SUCCESS=0

}SerialError;

class SerialComm
{
public:
    SerialComm();
    ~SerialComm();
    SerialError connectToArduino();
    SerialError write(QByteArray msg);
    SerialError read(QByteArray &msg);
    void disconnectFromArduino();
private:
    QSerialPort serialPort;
};

#endif // SERIALCOMM_H
