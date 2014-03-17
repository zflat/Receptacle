// log_emitter.h

#ifndef LOG_EMITTER_H
#define LOG_EMITTER_H

#include <QObject>
#include <QString>

class LogEmitter : public QObject
{
    Q_OBJECT
public:
    LogEmitter();
    void publish_message(QtMsgType type, const char *msg);

signals:
    void info_message(const QString &msg);
    void warn_message(const QString &msg);
    void critical_message(const QString &msg);
    void fatal_message(const QString &msg);
};

#endif // LOG_EMITTER_H
