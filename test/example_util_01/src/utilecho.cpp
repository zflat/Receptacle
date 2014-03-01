#include <QDebug>
#include <QThread>
#include "utilecho.h"

QString UtilEcho::name() const{
  return tr("Util echo");
}


QString UtilEcho::description() const{
 return tr("Example printing text output");
}


QString UtilEcho::command() const{
  return tr("echo01");
}

void UtilEcho::run(){
    qDebug() << "Running echo01...";
    for(int i=0; i<5; i++){
        QThread::msleep(50);
         qDebug()<<i<<endl;
    }
    qDebug() << "Done echo01";
}
