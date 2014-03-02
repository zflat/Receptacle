// util_echoworker.h

#ifndef UTIL_ECHOWORKER_H
#define UTIL_ECHOWORKER_H

#include <QRunnable>
#include <QObject>

class UtilEchoWorker : public QObject
{
    Q_OBJECT
public:
    void initialize();
    void run();

signals:
    // notify when we're done
    void result(int ret_val);
    void complete();
};

#endif // UTIL_ECHOWORKER_H
