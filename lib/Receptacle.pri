# Copyright 2014 William Wedler
#
# This file is part of Receptacle
#
# Receptacle is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Receptacle is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with Receptacle.  If not, see <http://www.gnu.org/licenses/>.


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
    $$PWD/interfaces/util_worker.h \
    $$PWD/include/util_collection.h \
    $$PWD/include/util_runner.h \
    $$PWD/include/host_controller.h \
    $$PWD/include/log_emitter.h \
    $$PWD/include/signal_counter.h \
    $$PWD/include/widgets/*.h


#FORMS += \
#    $$PWD/forms/*.ui \
