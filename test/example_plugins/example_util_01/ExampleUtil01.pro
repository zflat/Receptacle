TEMPLATE    = lib
CONFIG      += plugin
QT          += core gui

TARGET      = $$qtLibraryTarget(exampleUtil01)
DESTDIR     = ../../build/debug/plugins


SOURCES += \
    $$PWD/src/utilecho.cpp \
    $$PWD/src/util_echoworker.cpp \

HEADERS += \
    $$PWD/../../receptacle/interfaces/util_interface.h \
    $$PWD/../../receptacle/interfaces/util_worker_interface.h \
    $$PWD/include/utilecho.h \
    $$PWD/include/util_echoworker.h


INCLUDEPATH += $$PWD/src \
    $$PWD/"include" \
    $$PWD/../../receptacle/interfaces
