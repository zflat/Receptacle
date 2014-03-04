#-------------------------------------------------
#
# Project created from http://www.bogotobogo.com/Qt/Qt5_Asynchronous_QTcpServer_QThreadPool.php
# modifications from https://github.com/uglide/RedisDesktopManager as example
#
#-------------------------------------------------

QT       += core
QT       += network
QT       += gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Receptacle
CONFIG   += console gui
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    $$PWD/src/main.cpp \

include($$PWD/Receptacle.pri)
include($$PWD/../QsLog/QsLog.pri)
