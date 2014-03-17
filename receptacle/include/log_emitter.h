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
};

#endif // LOG_EMITTER_H
