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
    void on_sendButton_clicked();

    void on_sendField_returnPressed();

    void on_chaseButton_clicked();

    void on_flashButton_clicked();

    void on_strobeButton_clicked();

    void on_wipeButton_clicked();

    void on_testButton_clicked();

    void on_rainbowButton_clicked();

    void on_rColorSlider_valueChanged(int value);

    void on_gColorSlider_valueChanged(int value);

    void on_bColorSlider_valueChanged(int value);

public slots:
    void updateUiConnectInfo(QString port, QString baudRate, QString manufacturer, QString description);
    void updatUISent(QString msg);
    void updateUIReceived(QString msg);
private:
    Ui::MainWindow *ui;
    SerialComm comm;
    void updateColor();
};

#endif // MAINWINDOW_H
