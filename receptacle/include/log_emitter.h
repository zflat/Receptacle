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


// log_emitter.h

#ifndef LOG_EMITTER_H
#define LOG_EMITTER_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QCoreApplication>

class LogEmitter : public QObject
{
    Q_OBJECT
public:
    LogEmitter();
    ~LogEmitter();
    void publish_message(QtMsgType type, const QMessageLogContext &context, const QString &msg);

signals:
    void info_message(const QString &msg);
    void warn_message(const QString &msg);
    void critical_message(const QString &msg);
    void fatal_message(const QString &msg);

protected:
    const QString detailed_msg(const QMessageLogContext &context, const QString &msg);
};

#endif // LOG_EMITTER_H
