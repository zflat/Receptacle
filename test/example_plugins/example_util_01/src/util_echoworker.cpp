#include <QDebug>
#include "util_echoworker.h"


void UtilEchoWorker::init(){
}

void UtilEchoWorker::start(){
    qDebug() << "Run in plugin UtilEchoWorker <---" ;
    emit complete();
}
