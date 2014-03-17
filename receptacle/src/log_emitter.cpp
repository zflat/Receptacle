#include "log_emitter.h"

LogEmitter::LogEmitter(){
}

LogEmitter::~LogEmitter(){
}

//void LogEmitter::publish_message(QtMsgType type, const char *msg){
void LogEmitter::publish_message(QtMsgType type, const QMessageLogContext &context, const QString &msg){
    emit info_message(msg);
}
