#ifndef UTILECHOWORKER_H
#define UTILECHOWORKER_H

#include "util_worker.h"

class UtilEchoWorker : public UtilWorker {
    Q_OBJECT
public:
    UtilEchoWorker();

signals:
    // notify when we're done
    void result(int ret_val);

protected:
    void run();

};

#endif // UTILECHOWORKER_H
