
INCLUDEPATH += $$PWD/src \
    $$PWD/include \
    $$PWD/interfaces \


SOURCES += \
    $$PWD/src/dispatcher.cpp \
    $$PWD/src/client_connection.cpp \
    $$PWD/src/util_collection.cpp \
    $$PWD/src/util_runner.cpp \
    $$PWD/src/host_controller.cpp \
    $$PWD/src/log_emitter.cpp \
    $$PWD/src/widgets/*.cpp

HEADERS += \
    $$PWD/include/dispatcher.h \
    $$PWD/include/client_connection.h \
    $$PWD/interfaces/util_interface.h \
    $$PWD/interfaces/util_worker_interface.h \
    $$PWD/include/util_collection.h \
    $$PWD/include/util_runner.h \
    $$PWD/include/host_controller.h \
    $$PWD/include/log_emitter.h \
    $$PWD/include/widgets/*.h


#FORMS += \
#    $$PWD/forms/*.ui \
