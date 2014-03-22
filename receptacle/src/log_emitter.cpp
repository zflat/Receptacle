#include "log_emitter.h"

LogEmitter::LogEmitter(){
}

LogEmitter::~LogEmitter(){
}

void LogEmitter::publish_message(QtMsgType type, const QMessageLogContext &context, const QString &msg){
    switch(type){
        case QtDebugMsg:
            Q_EMIT info_message(msg);
            break;
        case QtWarningMsg:
            Q_EMIT warn_message(detailed_msg(context, msg));
            break;
        case QtCriticalMsg:
            Q_EMIT critical_message(detailed_msg(context, msg));
            break;
        case QtFatalMsg:
            Q_EMIT fatal_message(detailed_msg(context, msg));
            break;
    }
}

const QString LogEmitter::detailed_msg(const QMessageLogContext &context, const QString &msg){
    QString str = QString(msg);
    QString str_context = QString("");
    if(context.file && context.line && context.function){
        str_context = QString("%1 in %2(%3)\n").arg(context.function, context.file, QString::number(context.line));
    }
    return str_context.append(str);
}
