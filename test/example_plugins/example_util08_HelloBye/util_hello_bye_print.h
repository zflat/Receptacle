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


#ifndef UTIL_HELLO_BYE_PRINT_WORKER_H
#define UTIL_HELLO_BYE_PRINT_WORKER_H

#include <cstdlib>

#include <QTime>
#include <QRunnable>
#include <QObject>
#include <QDebug>
#include <QLabel>
#include <QtWidgets/QMainWindow>

#include "util_worker.h"

class UtilHelloByePrintWorker : public UtilWorker
{
    Q_OBJECT
public:
    UtilHelloByePrintWorker(int argc=0, char *argv[]=NULL, QObject* parent=0) : UtilWorker( argc, argv, parent ){
        widget = new QLabel("Hello, Goodbye form :)");
        meta_hash.insert("widget_type", "simple");
    }

    void start(){

        QTime time = QTime::currentTime();
        qsrand((uint)time.msec());

        int max_wait = 1;
        int hello_delay = max_wait * qrand()/RAND_MAX;
        int bye_delay = max_wait * qrand()/RAND_MAX;

        qDebug() << ((hello_delay < bye_delay) ? "Hello" : "Bye");

        QMainWindow* launcher = (QMainWindow*)top_widget();
        if(! widget->window()->close()){
            qWarning() <<  launcher->windowTitle().toStdString().c_str()<<  " window not closed";
        }else{
            qDebug() << launcher->windowTitle().toStdString().c_str()<<  " window closed";
        }

        emit complete();
    }

    QObject* get_widget(){
        return widget;
    }

private:
    QObject* top_widget(){
        QObject* p=widget;
        qDebug() << p->metaObject()->className();

        QObject* p_next;
        while(p_next = p->parent()){
            p=p_next;
            qDebug() << p->objectName().toStdString().c_str();
        }
        return p;
        /*
        for(p=widget; p_next=p->parent(); p=p_next);
        return p;
        */
    }
    QLabel* widget;
};

#endif


#ifndef UTIL_HELLO_BYE_PRINT_H
#define UTIL_HELLO_BYE_PRINT_H
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
    QString name() const {return QObject::tr("Util hello-bye");}
    QString description() const {return QObject::tr("Example that randomply closes the window to exit");}
    QString command() const {return QObject::tr("HelloBye");}
    virtual QString version() const{return QString("0.1.0");}
    UtilWorker* newWorker(){return new UtilHelloByePrintWorker();}
};
#endif


