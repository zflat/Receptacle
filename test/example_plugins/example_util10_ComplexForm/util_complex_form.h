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


#ifndef UTIL_COMPLEX_FORM_WORKER_H
#define UTIL_COMPLEX_FORM_WORKER_H

#include <QRunnable>
#include <QObject>
#include <QDebug>
#include "util_worker.h"
#include "complex_form_widget.h"

class UtilComplexFormWorker : public UtilWorker
{
    Q_OBJECT
public:
    UtilComplexFormWorker(int argc=0, char *argv[]=NULL, QObject* parent=0) : UtilWorker( argc, argv, parent ){
        widget = new ComplexFormWidget();
        meta_hash.insert("widget_type", "complex");
    }
    ~UtilComplexFormWorker(){
        delete widget;
    }

    void start(){
        qDebug() << "Run in plugin UtilComplexFormWorker <---" ;
        emit complete();
    }

    virtual QObject* get_widget(){
        return (QObject *)this->widget;
    }

private:
    ComplexFormWidget* widget;
};

#endif


#ifndef UTIL_COMPLEX_FORM_H
#define UTIL_COMPLEX_FORM_H
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
    QString name() const {return QObject::tr("Util complex form");}
    QString description() const {return QObject::tr("Example with a complex (large) form");}
    QString command() const {return QObject::tr("ComplexForm");}
    virtual QString version() const{return QString("0.1.0");}
    UtilWorker* newWorker(){return new UtilComplexFormWorker();}
};
#endif


