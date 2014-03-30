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


TEMPLATE    = lib
CONFIG      += plugin
QT          += core gui

TARGET      = $$qtLibraryTarget(exampleUtil11)
DESTDIR     = $$PWD/../../integration/build/debug/plugins

HEADERS += $$PWD/util_that_never_ends.h

INCLUDEPATH += $$PWD/

include($$PWD/../common/common.pri)
