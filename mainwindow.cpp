#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial.setPortName("COM6");
    serial.open(QIODevice::ReadWrite);
    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);
    if (serial.isOpen() && serial.isWritable())
    {
        qDebug() << "Serial is open";

        QByteArray output;
        QByteArray input;

        while(true)
        {
            output = "c";
            serial.write(output);
            serial.flush();

            serial.waitForBytesWritten(1000);
            serial.waitForReadyRead(1000);
            char c;
            while(serial.bytesAvailable()>0)
            {
                serial.read(&c,1);
                qDebug() << c;

            }
            QThread::msleep(100);
        }
    }
    else
    {
        qDebug() << "Error openning serial";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
