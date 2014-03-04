// util_echoworker.h

#ifndef UTIL_ECHOWORKER_H
#define UTIL_ECHOWORKER_H

#include <QRunnable>
#include <QObject>
#include "util_worker_interface.h"

class UtilEchoWorker : public UtilWorkerInterface
{
    Q_OBJECT
public:
    void init();
    void start();

signals:
    // notify when we're done
    void result(int ret_val);
    void complete();
};

#endif // UTIL_ECHOWORKER_H
