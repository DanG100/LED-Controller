#ifndef SERIALCOMM_H
#define SERIALCOMM_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QTimer>

typedef enum SerialError
{
    SE_NOT_FOUND=1,
    SE_ERROR_OPEN=2,
    SE_ERROR_CLOSE=3,
    SE_ERROR_READ =4,
    SE_ERROR_WRITE=5,
    SE_ERROR_INVALID_PACKET=6,
    SE_SUCCESS=0

}SerialError;

class SerialComm : public QObject
{
    Q_OBJECT
public:
    SerialComm();
    ~SerialComm();
    SerialError connectToArduino();
    SerialError write(QString msg);

    void disconnectFromArduino();
private:
    QSerialPort serialPort;
    QByteArray createPacket(QString msg);
    SerialError getMsgFromPacket(QByteArray packet, QString &msg);
    QTimer serialDelayTimer;
private slots:
    SerialError read();
    void delayRead();
signals:
    void connected(QString port, QString baudRate, QString manufacturer, QString description);
    void sentMsg(QString msg);
    void receivedMsg(QString msg);

};

#endif // SERIALCOMM_H
