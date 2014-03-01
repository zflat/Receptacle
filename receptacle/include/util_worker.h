// util_worker.h

#ifndef UTIL_WORKER_H
#define UTIL_WORKER_H

#include <QRunnable>
#include <QObject>

class UtilWorker : public QObject, public QRunnable
{
    Q_OBJECT
public:
    UtilWorker();
    virtual void run();

signals:
    // notify when we're done
    void result(int ret_val);
};

#endif // UTIL_WORKER_H
