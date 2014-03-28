/*

Copyright 2014 William Wedler

This file is part of Receptacle

Receptacle is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Receptacle is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Receptacle.  If not, see <http://www.gnu.org/licenses/>.

*/


/*
  Plugin interface
  See example at:
  http://qt-project.org/doc/qt-5.1/qtwidgets/tools-plugandpaint.html
http://michael-stengel.com/blog/?p=4
https://qt-project.org/doc/qt-5.0/qtwidgets/tools-plugandpaintplugins-basictools.html

Object Factory with plugins:
http://stackoverflow.com/questions/9070817/qobject-factory-in-qt-pluginnon-creator
 */

#ifndef UTIL_WORKER_INTERFACE_H
#define UTIL_WORKER_INTERFACE_H

#include <QtPlugin>
#include <QString>
#include <QObject>

class UtilWorkerInterface : public QObject
{
    Q_OBJECT
 public:
    UtilWorkerInterface( QObject* parent=0) : QObject( parent ){}
    virtual ~UtilWorkerInterface(){}
    virtual void init() = 0;
    virtual void start() = 0;
 signals:
    void complete();
};

#endif //UTIL_WORKER_INTERFACE_H

