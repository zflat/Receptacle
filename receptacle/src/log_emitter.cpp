#include "log_emitter.h"

LogEmitter::LogEmitter(){
}

LogEmitter::~LogEmitter(){
}

//void LogEmitter::publish_message(QtMsgType type, const char *msg){
void LogEmitter::publish_message(QtMsgType type, const QMessageLogContext &context, const QString &msg){
    Q_EMIT info_message(msg);
}
