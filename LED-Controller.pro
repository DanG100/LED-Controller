#-------------------------------------------------
#
# Project created by QtCreator 2016-10-11T14:43:04
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LED-Controller
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    serialcomm.cpp

HEADERS  += mainwindow.h \
    serialcomm.h

FORMS    += mainwindow.ui
