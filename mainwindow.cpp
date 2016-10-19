#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&comm,SIGNAL(connected(QString, QString, QString, QString)),this,SLOT(updateConnectInfo(QString, QString, QString, QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionConnect_triggered()
{
    this->comm.connectToArduino();
}

void MainWindow::on_actionDisconnect_triggered()
{
    this->comm.disconnectFromArduino();
    this->ui->statusText->setText("Disconnected");
}

void MainWindow::updateConnectInfo(QString port, QString baudRate, QString manufacturer, QString description)
{
    this->ui->statusText->setText("Connected");
    this->ui->portText->setText(port);
    this->ui->baudText->setText(baudRate);
    this->ui->manufactText->setText(manufacturer);
    this->ui->descText->setText(description);
}
