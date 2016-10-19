#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QDebug>
#include <QThread>
#include "serialcomm.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionConnect_triggered();
    void on_actionDisconnect_triggered();
public slots:
    void updateConnectInfo(QString port, QString baudRate, QString manufacturer, QString description);
private:
    Ui::MainWindow *ui;
    SerialComm comm;
};

#endif // MAINWINDOW_H
