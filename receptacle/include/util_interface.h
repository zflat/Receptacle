/*
  Plugin interface
  See example at:
  http://qt-project.org/doc/qt-5.1/qtwidgets/tools-plugandpaint.html
http://michael-stengel.com/blog/?p=4
https://qt-project.org/doc/qt-5.0/qtwidgets/tools-plugandpaintplugins-basictools.html
 */

#ifndef UTIL_INTERFACE_H
#define UTIL_INTERFACE_H

#include <QtPlugin>
#include <QString>
#include <QRunnable>

class UtilInterface
{
 public:
    virtual ~UtilInterface(){}
    virtual QString name() const = 0;
    virtual QString description() const = 0;
    virtual QString command() const = 0;
    virtual QRunnable* getRunner() = 0;
    virtual QObject* getWorker() = 0;
    virtual void complete() = 0;
    virtual int run() = 0;
private:
    QRunnable* runner;
    QObject* worker;
};

#define UtilInterface_iid "Receptacle.plugins.UtilInterface-v0.0.1"

Q_DECLARE_INTERFACE(UtilInterface, UtilInterface_iid)

#endif // UTIL_INTERFACE_H
