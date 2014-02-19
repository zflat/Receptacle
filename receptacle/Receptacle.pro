#-------------------------------------------------
#
# Project created from http://www.bogotobogo.com/Qt/Qt5_Asynchronous_QTcpServer_QThreadPool.php
# modifications from https://github.com/uglide/RedisDesktopManager as example
#
#-------------------------------------------------

QT       += core
QT       += network
QT       -= gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Receptacle
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    $$PWD/src/main.cpp \
    $$PWD/src/dispatcher.cpp \
    $$PWD/src/client_connection.cpp \
    $$PWD/src/mytask.cpp \
    $$PWD/src/util_collection.cpp

HEADERS += \
    $$PWD/include/dispatcher.h \
    $$PWD/include/client_connection.h \
    $$PWD/include/mytask.h \
    $$PWD/include/util_interface.h \
    $$PWD/include/util_collection.h


INCLUDEPATH += $$PWD/src \
    $$PWD/"include" \

#FORMS += \
#    $$PWD/forms/*.ui \
