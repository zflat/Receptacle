// util_worker.h

#ifndef UTIL_WORKER_H
#define UTIL_WORKER_H

#include <QRunnable>
#include <QObject>
#include "util_interface.h"

class UtilWorker : public QObject
{
    Q_OBJECT
public:
    virtual void run() = 0;

signals:
    // notify when we're done
    void result(int ret_val);
    void complete();
};

#endif // UTIL_WORKER_H
