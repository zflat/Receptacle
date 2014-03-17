#include "log_emitter.h"
#include <QDebug>

LogEmitter::LogEmitter(){
}

void LogEmitter::publish_message(QtMsgType type, const char *msg){
    QString str = QString(QLatin1String(msg));
    emit info_message(str);
}
