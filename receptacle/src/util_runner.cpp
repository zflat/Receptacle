// util_runner.cpp

#include "util_runner.h"
#include <QDebug>

// When the thread pool kicks up
// it's going to hit this run, and it's going to do this time consuming task.
// After it's done, we're going to send the results back to our main thread.
// This runs in the separate thread, and we do not have any control over this thread,
// but Qt does.
// This may just stay in the queue for several ms depending on how busy the server is.


void UtilRunner::run()
{
    this->worker->init();
    this->worker->start();
    emit result(0);
}

