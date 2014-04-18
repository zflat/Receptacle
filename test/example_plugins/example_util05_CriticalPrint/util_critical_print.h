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


#ifndef UTIL_CRITICAL_PRINT_WORKER_H
#define UTIL_CRITICAL_PRINT_WORKER_H

#include <QRunnable>
#include <QObject>
#include <QDebug>
#include "util_worker.h"

class UtilCriticalPrintWorker : public UtilWorker
{
    Q_OBJECT
public:
    void start(){
        qCritical() << "Run in plugin UtilCriticalPrintWorker <---" ;
        emit complete();
    }
};

#endif


#ifndef UTIL_CRITICAL_PRINT_H
#define UTIL_CRITICAL_PRINT_H
#include <QObject>
#include <QString>

#include "util_interface.h"
#include "util_worker.h"

class UtilWarnPrint : public QObject, public UtilInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "Receptacle.plugins.UtilInterface/0.1.0")
    Q_INTERFACES(UtilInterface)

public:
    QString name() const {return QObject::tr("Util critical print");}
    QString description() const {return QObject::tr("Example error critical in utility");}
    QString command() const {return QObject::tr("CriticalPrint");}
    virtual QString version() const{return QString("0.1.0");}
    UtilWorker* newWorker(){return new UtilCriticalPrintWorker();}
};
#endif


