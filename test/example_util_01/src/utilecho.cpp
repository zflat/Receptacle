#include <QDebug>
#include <QThread>
#include "utilecho.h"
#include "util_echoworker.h"

QString UtilEcho::name() const{
  return QObject::tr("Util echo");
}

QString UtilEcho::description() const{
 return QObject::tr("Example printing text output");
}

QString UtilEcho::command() const{
  return QObject::tr("echo01");
}

UtilWorkerInterface *UtilEcho::newWorker(){
    return new UtilEchoWorker();
}
