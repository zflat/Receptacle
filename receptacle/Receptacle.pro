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
    $$PWD/src/dispatcher.cpp \
    $$PWD/src/client_connection.cpp \
    $$PWD/src/util_worker.cpp \
    $$PWD/src/util_collection.cpp \
    $$PWD/src/host_controller.cpp \
    $$PWD/src/widgets/*.cpp

HEADERS += \
    $$PWD/include/dispatcher.h \
    $$PWD/include/client_connection.h \
    $$PWD/include/util_worker.h \
    $$PWD/include/util_interface.h \
    $$PWD/include/util_collection.h \
    $$PWD/include/host_controller.h \
    $$PWD/include/widgets/*.h


INCLUDEPATH += $$PWD/src \
    $$PWD/"include" \

#FORMS += \
#    $$PWD/forms/*.ui \

include($$PWD/../QsLog/QsLog.pri)
