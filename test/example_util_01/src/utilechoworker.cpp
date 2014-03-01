#include <QDebug>
#include <QThread>
#include "utilechoworker.h"

UtilEchoWorker::UtilEchoWorker()
{
}

void UtilEchoWorker::run(){
    qDebug() << "Running echo01...";
    for(int i=0; i<5; i++){
        QThread::msleep(50);
         qDebug()<<i<<endl;
    }
    qDebug() << "Done echo01";
    emit result(0);
}
