#ifndef RECEPTACLE_APP_H
#define RECEPTACLE_APP_H

#include <QApplication>

#include "log_emitter.h"
#include "util_collection.h"
#include "host_controller.h"
#include "dispatcher.h"

class ReceptacleApp : public QApplication
{
public:
    ReceptacleApp(int &argc, char **argv);
    ~ReceptacleApp();

    void startServer(int port, LogEmitter * logger);

protected:
     UtilCollection* utils;
     HostController* controller;
     Dispatcher* server;
};

#endif // RECEPTACLE_APP_H
