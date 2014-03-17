#-------------------------------------------------
#
# Project created by QtCreator 2014-03-03T21:48:37
#
#-------------------------------------------------

QT       += testlib
QT       += network
QT       += core
QT       += gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tst_unittest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += $$PWD/src \
    $$PWD/inc \


HEADERS += $$PWD/inc/*.h \

SOURCES += tst_unittest.cpp \
        $$PWD/src/*.cpp \

DEFINES += SRCDIR=\\\"$$PWD/\\\"


#
# Using .pri files as example http://bazaar.launchpad.net/~benlau/penpen/trunk/files/head:/tests/unittests/
#
include($$PWD/../../../receptacle/Receptacle.pri)
include($$PWD/../../../QsLog/QsLog.pri)
