#include <QDebug>
#include "util_echoworker.h"

void UtilEchoWorker::run(){
    qDebug() << "Run in plugin UtilEchoWorker <---" ;
    emit complete();
}
