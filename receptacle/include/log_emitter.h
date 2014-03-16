// log_emitter.h

#ifndef LOG_EMITTER_H
#define LOG_EMITTER_H

#include <QObject>

class LogEmitter : public QObject
{
    Q_OBJECT
public:
    LogEmitter();
    void forward_message(QtMsgType type, const char *msg);
    // bool subscribe(QObject target)

signals:
    void warn_message(QString cmd);
};

#endif // LOG_EMITTER_H
