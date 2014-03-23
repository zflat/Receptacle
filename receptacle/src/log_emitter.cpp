/*

Copyright 2014 William Wedler

This file is part of Receptacle

Receptacle is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Receptacle is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Receptacle.  If not, see <http://www.gnu.org/licenses/>.

*/


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
