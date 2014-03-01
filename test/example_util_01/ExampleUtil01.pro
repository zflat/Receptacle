TEMPLATE    = lib
CONFIG      += plugin
QT          += core gui

TARGET      = $$qtLibraryTarget(exampleUtil01)
DESTDIR     = ../../build/debug/plugins


SOURCES += \
    $$PWD/src/main.cpp \
    $$PWD/src/utilecho.cpp \
    $$PWD/src/utilechoworker.cpp

HEADERS += \
    $$PWD/include/utilecho.h \
    include/utilechoworker.h


INCLUDEPATH += $$PWD/src \
    $$PWD/"include" \
    $$PWD/../../receptacle/include
