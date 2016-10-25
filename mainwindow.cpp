#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&comm,SIGNAL(connected(QString, QString, QString, QString)),this,SLOT(updateUiConnectInfo(QString, QString, QString, QString)));
    connect(&comm,SIGNAL(sentMsg(QString)),this,SLOT(updatUISent(QString)));
    connect(&comm,SIGNAL(receivedMsg(QString)),this,SLOT(updateUIReceived(QString)));
    this->ui->actionDisconnect->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionConnect_triggered()
{
    this->comm.connectToArduino();
    this->ui->actionConnect->setDisabled(true);
    this->ui->actionDisconnect->setEnabled(true);
}

void MainWindow::on_actionDisconnect_triggered()
{
    this->comm.disconnectFromArduino();
    this->ui->statusText->setText("Disconnected");
    this->ui->actionConnect->setEnabled(true);
    this->ui->actionDisconnect->setDisabled(true);
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
void MainWindow::updatUISent(QString msg)
{
    this->ui->logView->append("You: " + msg);
}
void MainWindow::updateUIReceived(QString msg)
{
    this->ui->logView->append("Arduino: " + msg);
}
