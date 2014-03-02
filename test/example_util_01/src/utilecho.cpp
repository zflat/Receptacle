#include <QDebug>
#include <QThread>
#include "utilecho.h"

QString UtilEcho::name() const{
  return QObject::tr("Util echo");
}


QString UtilEcho::description() const{
 return QObject::tr("Example printing text output");
}


QString UtilEcho::command() const{
  return QObject::tr("echo01");
}


UtilWorker* UtilEcho::getWorker(){
    return NULL;
}
