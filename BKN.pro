#-------------------------------------------------
#
# Project created by QtCreator 2014-08-22T15:34:58
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BKN
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    PortControl.cpp

HEADERS  += mainwindow.h \
    PortControl.h

FORMS    += mainwindow.ui
