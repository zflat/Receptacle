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


#ifndef UTIL_DELAYED_PRINT_WORKER_H
#define UTIL_DELAYED_PRINT_WORKER_H

#include <QRunnable>
#include <QObject>
#include <QDebug>
#include <QThread>
#include "util_worker.h"

class UtilDelayedPrintWorker : public UtilWorker
{
    Q_OBJECT
public:
    void start(){
        qDebug() << "Run in plugin UtilDelayedPrintWorker <---" ;
        for(int i=0; i<1; i++){
            // wait for a bit
            QThread::sleep(1);
            qDebug() << ".";
        }
        Q_EMIT complete();
    }
};

#endif


#ifndef UTIL_DELAYED_PRINT_H
#define UTIL_DELAYED_PRINT_H
#include <QObject>
#include <QString>

#include "util_interface.h"
#include "util_worker.h"

class UtilDelayedPrint : public QObject, public UtilInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "Receptacle.plugins.UtilInterface/0.1.0")
    Q_INTERFACES(UtilInterface)

public:
    QString name() const {return QObject::tr("Util delayed print");}
    QString description() const {return QObject::tr("Example printing text output after a delay");}
    QString command() const {return QObject::tr("DelayedPrint");}
    virtual QString version() const{return QString("0.1.0");}
    UtilWorker* newWorker(){return new UtilDelayedPrintWorker();}
};
#endif


