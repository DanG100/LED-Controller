#include "serialcomm.h"

SerialComm::SerialComm()
{
    this->serialDelayTimer.setSingleShot(true);
    connect(&serialPort,SIGNAL(readyRead()),this,SLOT(delayRead()));
    connect(&serialDelayTimer,SIGNAL(timeout()),this,SLOT(read()));
}
SerialComm::~SerialComm()
{
  disconnect(&serialPort,SIGNAL(readyRead()),this,SLOT(delayRead()));
  disconnect(&serialDelayTimer,SIGNAL(timeout()),this,SLOT(read()));
}

SerialError SerialComm::connectToArduino()
{
    QSerialPortInfo portToUse;

    foreach (const QSerialPortInfo &port, QSerialPortInfo::availablePorts())
    {
        if(!port.isBusy() && (port.description().contains("Arduino") || port.manufacturer().contains("Arduino")))
                portToUse = port;
    }
    if(portToUse.isNull() || !portToUse.isValid())
    {
        qDebug() << "Invalid Port" << portToUse.portName();
        return SE_NOT_FOUND;
    }
    this->serialPort.setPort(portToUse);

    this->serialPort.setBaudRate(QSerialPort::Baud115200);
    this->serialPort.setDataBits(QSerialPort::Data8);
    this->serialPort.setParity(QSerialPort::NoParity);
    this->serialPort.setStopBits(QSerialPort::OneStop);
    this->serialPort.setFlowControl(QSerialPort::NoFlowControl);


    if (this->serialPort.open(QIODevice::ReadWrite))
    {
        //TODO:add UI elements
        qDebug() << "Connected to: " << portToUse.portName();
    }
    else
    {
        qDebug() << "Open error";
        return SE_ERROR_OPEN;
    }
    emit connected(portToUse.portName(),QString::number(115200),portToUse.manufacturer(),portToUse.description());//TODO: fix static baudrate

    return SE_SUCCESS;
}

SerialError SerialComm::write(QString msg)
{
    QByteArray packet = createPacket(msg);
    int ret = this->serialPort.write(packet);
    if(ret != packet.length() || ret == -1)
        return SE_ERROR_WRITE;
    this->serialPort.flush();
    this->serialPort.waitForBytesWritten(1000);
    emit sentMsg(msg);
    return SE_SUCCESS;
}

SerialError SerialComm::read()
{
    char data[1024] = {0};
    int ret = this->serialPort.readLine(data,1024);
    if(ret == 0 || ret == -1)//TODO: handle partial reads
        return SE_ERROR_READ;
    QString msg;
    getMsgFromPacket(data,msg);
    emit receivedMsg(msg);
    return SE_SUCCESS;
}

void SerialComm::disconnectFromArduino()
{
    this->serialPort.close();
    disconnect(&serialPort,SIGNAL(readyRead()),this,SLOT(read()));
}

QByteArray SerialComm::createPacket(QString msg)
{
    QByteArray packet = msg.toUtf8();
    packet.prepend("!0:");packet.append("\n");
    packet[1] = (char) packet.length();
    return packet;
}

SerialError SerialComm::getMsgFromPacket(QByteArray packet, QString &msg)
{
    if(packet.isEmpty() || packet.isNull())
        return SE_ERROR_INVALID_PACKET;
    msg = QString("Error");
    if(packet.at(0)!='!' || packet.at(packet.length()-1) != '\n')
        return SE_ERROR_INVALID_PACKET;
    if(packet.at(1)!=packet.length())
        return SE_ERROR_INVALID_PACKET;
    msg = QString(packet);
    msg = msg.mid(msg.indexOf(':')+1);
    msg = msg.left(msg.length()-1);
    return SE_SUCCESS;
}

void SerialComm::delayRead()
{
    if(!this->serialDelayTimer.isActive())
    {
        serialDelayTimer.start(2000);
    }
}

