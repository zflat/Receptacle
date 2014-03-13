#-------------------------------------------------
#
# Project created by QtCreator 2014-03-12T20:37:50
#
#-------------------------------------------------

QT       += widgets
QT       += testlib
QT       += network
QT       += core
QT       += gui

TARGET = tst_integrationtest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app



INCLUDEPATH += $$PWD/src \
    $$PWD/inc \



# HEADERS += $$PWD/inc/*.h

SOURCES += tst_integrationtest.cpp \
       # $$PWD/src/*.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

include($$PWD/../../../receptacle/Receptacle.pri)
include($$PWD/../../../QsLog/QsLog.pri)
