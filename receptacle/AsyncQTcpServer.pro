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

TARGET = AsyncQTcpServer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    $$PWD/src/main.cpp \
    $$PWD/src/myserver.cpp \
    $$PWD/src/myclient.cpp \
    $$PWD/src/mytask.cpp

HEADERS += \
    $$PWD/include/myserver.h \
    $$PWD/include/myclient.h \
    $$PWD/include/mytask.h


INCLUDEPATH += $$PWD/src \
    $$PWD/"include" \

#FORMS += \
#    $$PWD/forms/*.ui \
