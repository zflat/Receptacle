// util_runner.h

#ifndef UTIL_RUNNER_H
#define UTIL_RUNNER_H

#include <QRunnable>
#include <QObject>
#include "util_worker_interface.h"

class UtilRunner : public QObject, public QRunnable
{
    Q_OBJECT
public:
    UtilRunner(UtilWorkerInterface* util_worker):worker(util_worker){}
protected:
    void run();

signals:
    // notify when we're done
    void result(int ret_val);
    void complete();
private:
    UtilWorkerInterface* worker;
};

#endif // UTIL_RUNNER_H
