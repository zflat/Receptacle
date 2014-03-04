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

