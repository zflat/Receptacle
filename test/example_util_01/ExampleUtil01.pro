TEMPLATE    = lib
CONFIG      += plugin
QT          += core gui

TARGET      = $$qtLibraryTarget(exampleUtil01)
DESTDIR     = ../../build/debug/plugins


SOURCES += \
    $$PWD/src/main.cpp \
    $$PWD/src/utilecho.cpp \

HEADERS += \
    $$PWD/include/utilecho.h \


INCLUDEPATH += $$PWD/src \
    $$PWD/"include" \
    $$PWD/../../receptacle/include
