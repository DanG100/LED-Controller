#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&comm,SIGNAL(connected(QString, QString, QString, QString)),this,SLOT(updateUiConnectInfo(QString, QString, QString, QString)));
    connect(&comm,SIGNAL(sentMsg(QByteArray)),this,SLOT(updatUISent(QByteArray)));
    connect(&comm,SIGNAL(receivedMsg(QByteArray)),this,SLOT(updateUIReceived(QByteArray)));
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

void MainWindow::updateUiConnectInfo(QString port, QString baudRate, QString manufacturer, QString description)
{
    this->ui->statusText->setText("Connected");
    this->ui->portText->setText(port);
    this->ui->baudText->setText(baudRate);
    this->ui->manufactText->setText(manufacturer);
    this->ui->descText->setText(description);
}

void MainWindow::on_sendButton_clicked()
{
    this->comm.write(this->ui->sendField->text().toUtf8());
    this->ui->sendField->clear();
}

void MainWindow::on_sendField_returnPressed()
{
    this->on_sendButton_clicked();
}
void MainWindow::updatUISent(QByteArray msg)
{
    QString display = QString(msg);
    this->ui->logView->append("You: " + display);
}
void MainWindow::updateUIReceived(QByteArray msg)
{
    QString display = QString(msg);
    this->ui->logView->append("Arduino: " + display);
}
