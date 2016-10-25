#include "serialcomm.h"

SerialComm::SerialComm()
{

}
SerialComm::~SerialComm()
{

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

    this->serialPort.setBaudRate(QSerialPort::Baud9600);
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
    emit connected(portToUse.portName(),QString::number(9600),portToUse.manufacturer(),portToUse.description());//TODO: fix static baudrate
    connect(&serialPort,SIGNAL(readyRead()),this,SLOT(read()));
    return SE_SUCCESS;
}

SerialError SerialComm::write(QByteArray msg)
{
    int ret = this->serialPort.write(msg);
    if(ret != msg.length() || ret == -1)
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
    QByteArray msg = QByteArray(data);
    qDebug() << msg;
    emit receivedMsg(msg);
    return SE_SUCCESS;
}

void SerialComm::disconnectFromArduino()
{
    this->serialPort.close();
}



